/*	$NetBSD: uhub.c,v 1.103 2008/08/18 18:03:21 kent Exp $	*/
/*	$FreeBSD: src/sys/dev/usb/uhub.c,v 1.18 1999/11/17 22:33:43 n_hibma Exp $	*/

/*
 * Copyright (c) 1998, 2004 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Lennart Augustsson (lennart@augustsson.net) at
 * Carlstedt Research & Technology.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * USB spec: http://www.usb.org/developers/docs/usbspec.zip
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD: uhub.c,v 1.103 2008/08/18 18:03:21 kent Exp $");

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/malloc.h>
#include <sys/device.h>
#include <sys/proc.h>

#include <sys/bus.h>

#include <dev/usb/usb.h>
#include <dev/usb/usbdi.h>
#include <dev/usb/usbdi_util.h>
#include <dev/usb/usbdivar.h>

#ifdef UHUB_DEBUG
#define DPRINTF(x)	if (uhubdebug) logprintf x
#define DPRINTFN(n,x)	if (uhubdebug>(n)) logprintf x
int	uhubdebug = 0;
#else
#define DPRINTF(x)
#define DPRINTFN(n,x)
#endif

struct uhub_softc {
	USBBASEDEVICE		sc_dev;		/* base device */
	usbd_device_handle	sc_hub;		/* USB device */
	int			sc_proto;	/* device protocol */
	usbd_pipe_handle	sc_ipipe;	/* interrupt pipe */

	/* XXX second buffer needed because we can't suspend pipes yet */
	u_int8_t		*sc_statusbuf;
	u_int8_t		*sc_status;
	size_t			sc_statuslen;
	int			sc_explorepending;
	int		sc_isehciroothub; /* see comment in uhub_intr() */

	u_char			sc_running;
};

#define UHUB_IS_HIGH_SPEED(sc) ((sc)->sc_proto != UDPROTO_FSHUB)
#define UHUB_IS_SINGLE_TT(sc) ((sc)->sc_proto == UDPROTO_HSHUBSTT)

#define PORTSTAT_ISSET(sc, port) \
	((sc)->sc_status[(port) / 8] & (1 << ((port) % 8)))

Static usbd_status uhub_explore(usbd_device_handle hub);
Static void uhub_intr(usbd_xfer_handle, usbd_private_handle,usbd_status);


/*
 * We need two attachment points:
 * hub to usb and hub to hub
 * Every other driver only connects to hubs
 */

int uhub_match(device_t, cfdata_t, void *);
void uhub_attach(device_t, device_t, void *);
int uhub_rescan(device_t, const char *, const int *);
void uhub_childdet(device_t, device_t);
int uhub_detach(device_t, int);
int uhub_activate(device_t, enum devact);
extern struct cfdriver uhub_cd;
CFATTACH_DECL2_NEW(uhub, sizeof(struct uhub_softc), uhub_match,
    uhub_attach, uhub_detach, uhub_activate, uhub_rescan, uhub_childdet);
CFATTACH_DECL2_NEW(uroothub, sizeof(struct uhub_softc), uhub_match,
    uhub_attach, uhub_detach, uhub_activate, uhub_rescan, uhub_childdet);

USB_MATCH(uhub)
{
	USB_MATCH_START(uhub, uaa);

	DPRINTFN(5,("uhub_match, uaa=%p\n", uaa));
	/*
	 * The subclass for hubs seems to be 0 for some and 1 for others,
	 * so we just ignore the subclass.
	 */
	if (uaa->class == UDCLASS_HUB)
		return (UMATCH_DEVCLASS_DEVSUBCLASS);
	return (UMATCH_NONE);
}

USB_ATTACH(uhub)
{
	USB_ATTACH_START(uhub, sc, uaa);
	usbd_device_handle dev = uaa->device;
	char *devinfop;
	usbd_status err;
	struct usbd_hub *hub = NULL;
	usb_device_request_t req;
	usb_hub_descriptor_t hubdesc;
	int p, port, nports, nremov, pwrdly;
	usbd_interface_handle iface;
	usb_endpoint_descriptor_t *ed;
#if 0 /* notyet */
	struct usbd_tt *tts = NULL;
#endif

	DPRINTFN(1,("uhub_attach\n"));
	sc->sc_dev = self;
	sc->sc_hub = dev;
	sc->sc_proto = uaa->proto;

	devinfop = usbd_devinfo_alloc(dev, 1);
	aprint_naive("\n");
	aprint_normal(": %s\n", devinfop);
	usbd_devinfo_free(devinfop);

	if (dev->depth > 0 && UHUB_IS_HIGH_SPEED(sc)) {
		aprint_normal_dev(self, "%s transaction translator%s\n",
		       UHUB_IS_SINGLE_TT(sc) ? "single" : "multiple",
		       UHUB_IS_SINGLE_TT(sc) ? "" : "s");
	}

	err = usbd_set_config_index(dev, 0, 1);
	if (err) {
		DPRINTF(("%s: configuration failed, error=%s\n",
			 USBDEVNAME(sc->sc_dev), usbd_errstr(err)));
		USB_ATTACH_ERROR_RETURN;
	}

	if (dev->depth > USB_HUB_MAX_DEPTH) {
		aprint_error_dev(self,
		    "hub depth (%d) exceeded, hub ignored\n",
		    USB_HUB_MAX_DEPTH);
		USB_ATTACH_ERROR_RETURN;
	}

	/* Get hub descriptor. */
	req.bmRequestType = UT_READ_CLASS_DEVICE;
	req.bRequest = UR_GET_DESCRIPTOR;
	USETW2(req.wValue, UDESC_HUB, 0);
	USETW(req.wIndex, 0);
	USETW(req.wLength, USB_HUB_DESCRIPTOR_SIZE);
	DPRINTFN(1,("usb_init_hub: getting hub descriptor\n"));
	err = usbd_do_request(dev, &req, &hubdesc);
	nports = hubdesc.bNbrPorts;
	if (!err && nports > 7) {
		USETW(req.wLength, USB_HUB_DESCRIPTOR_SIZE + (nports+1) / 8);
		err = usbd_do_request(dev, &req, &hubdesc);
	}
	if (err) {
		DPRINTF(("%s: getting hub descriptor failed, error=%s\n",
			 USBDEVNAME(sc->sc_dev), usbd_errstr(err)));
		USB_ATTACH_ERROR_RETURN;
	}

	for (nremov = 0, port = 1; port <= nports; port++)
		if (!UHD_NOT_REMOV(&hubdesc, port))
			nremov++;
	aprint_verbose_dev(self, "%d port%s with %d removable, %s powered\n",
	    nports, nports != 1 ? "s" : "", nremov,
	    dev->self_powered ? "self" : "bus");

	if (nports == 0) {
		aprint_debug_dev(self, "no ports, hub ignored\n");
		goto bad;
	}

	hub = malloc(sizeof(*hub) + (nports-1) * sizeof(struct usbd_port),
		     M_USBDEV, M_NOWAIT);
	if (hub == NULL)
		USB_ATTACH_ERROR_RETURN;
	dev->hub = hub;
	dev->hub->hubsoftc = sc;
	hub->explore = uhub_explore;
	hub->hubdesc = hubdesc;

	/* Set up interrupt pipe. */
	err = usbd_device2interface_handle(dev, 0, &iface);
	if (err) {
		aprint_error_dev(self, "no interface handle\n");
		goto bad;
	}

	if (UHUB_IS_HIGH_SPEED(sc) && !UHUB_IS_SINGLE_TT(sc)) {
		err = usbd_set_interface(iface, 1);
		if (err)
			aprint_error_dev(self, "can't enable multiple TTs\n");
	}

	ed = usbd_interface2endpoint_descriptor(iface, 0);
	if (ed == NULL) {
		aprint_error_dev(self, "no endpoint descriptor\n");
		goto bad;
	}
	if ((ed->bmAttributes & UE_XFERTYPE) != UE_INTERRUPT) {
		aprint_error_dev(self, "bad interrupt endpoint\n");
		goto bad;
	}

	sc->sc_statuslen = (nports + 1 + 7) / 8;
	sc->sc_statusbuf = malloc(sc->sc_statuslen, M_USBDEV, M_NOWAIT);
	if (!sc->sc_statusbuf)
		goto bad;
	sc->sc_status = malloc(sc->sc_statuslen, M_USBDEV, M_NOWAIT);
	if (!sc->sc_status)
		goto bad;
	if (device_is_a(device_parent(device_parent(sc->sc_dev)), "ehci"))
		sc->sc_isehciroothub = 1;

	/* force initial scan */
	memset(sc->sc_status, 0xff, sc->sc_statuslen);
	sc->sc_explorepending = 1;

	err = usbd_open_pipe_intr(iface, ed->bEndpointAddress,
		  USBD_SHORT_XFER_OK, &sc->sc_ipipe, sc, sc->sc_statusbuf,
		  sc->sc_statuslen, uhub_intr, USBD_DEFAULT_INTERVAL);
	if (err) {
		aprint_error_dev(self, "cannot open interrupt pipe\n");
		goto bad;
	}

	/* Wait with power off for a while. */
	usbd_delay_ms(dev, USB_POWER_DOWN_TIME);

	usbd_add_drv_event(USB_EVENT_DRIVER_ATTACH, dev, USBDEV(sc->sc_dev));

	/*
	 * To have the best chance of success we do things in the exact same
	 * order as Windoze98.  This should not be necessary, but some
	 * devices do not follow the USB specs to the letter.
	 *
	 * These are the events on the bus when a hub is attached:
	 *  Get device and config descriptors (see attach code)
	 *  Get hub descriptor (see above)
	 *  For all ports
	 *     turn on power
	 *     wait for power to become stable
	 * (all below happens in explore code)
	 *  For all ports
	 *     clear C_PORT_CONNECTION
	 *  For all ports
	 *     get port status
	 *     if device connected
	 *        wait 100 ms
	 *        turn on reset
	 *        wait
	 *        clear C_PORT_RESET
	 *        get port status
	 *        proceed with device attachment
	 */

#if 0
	if (UHUB_IS_HIGH_SPEED(sc) && nports > 0) {
		tts = malloc((UHUB_IS_SINGLE_TT(sc) ? 1 : nports) *
			     sizeof (struct usbd_tt), M_USBDEV, M_NOWAIT);
		if (!tts)
			goto bad;
	}
#endif
	/* Set up data structures */
	for (p = 0; p < nports; p++) {
		struct usbd_port *up = &hub->ports[p];
		up->device = NULL;
		up->parent = dev;
		up->portno = p+1;
		if (dev->self_powered)
			/* Self powered hub, give ports maximum current. */
			up->power = USB_MAX_POWER;
		else
			up->power = USB_MIN_POWER;
		up->restartcnt = 0;
		up->reattach = 0;
#if 0
		if (UHUB_IS_HIGH_SPEED(sc)) {
			up->tt = &tts[UHUB_IS_SINGLE_TT(sc) ? 0 : p];
			up->tt->hub = hub;
		} else {
			up->tt = NULL;
		}
#endif
	}

	/* XXX should check for none, individual, or ganged power? */

	pwrdly = dev->hub->hubdesc.bPwrOn2PwrGood * UHD_PWRON_FACTOR
	    + USB_EXTRA_POWER_UP_TIME;
	for (port = 1; port <= nports; port++) {
		/* Turn the power on. */
		err = usbd_set_port_feature(dev, port, UHF_PORT_POWER);
		if (err)
			aprint_error_dev(self, "port %d power on failed, %s\n",
			    port, usbd_errstr(err));
		DPRINTF(("usb_init_port: turn on port %d power\n", port));
	}

	/* Wait for stable power if we are not a root hub */
	if (dev->powersrc->parent != NULL)
		usbd_delay_ms(dev, pwrdly);

	/* The usual exploration will finish the setup. */

	sc->sc_running = 1;

	if (!pmf_device_register(self, NULL, NULL))
		aprint_error_dev(self, "couldn't establish power handler\n");

	USB_ATTACH_SUCCESS_RETURN;

 bad:
	if (sc->sc_status)
		free(sc->sc_status, M_USBDEV);
	if (sc->sc_statusbuf)
		free(sc->sc_statusbuf, M_USBDEV);
	if (hub)
		free(hub, M_USBDEV);
	dev->hub = NULL;
	USB_ATTACH_ERROR_RETURN;
}

usbd_status
uhub_explore(usbd_device_handle dev)
{
	usb_hub_descriptor_t *hd = &dev->hub->hubdesc;
	struct uhub_softc *sc = dev->hub->hubsoftc;
	struct usbd_port *up;
	usbd_status err;
	int speed;
	int port;
	int change, status, reconnect;

	DPRINTFN(10, ("uhub_explore dev=%p addr=%d\n", dev, dev->address));

	if (!sc->sc_running)
		return (USBD_NOT_STARTED);

	/* Ignore hubs that are too deep. */
	if (dev->depth > USB_HUB_MAX_DEPTH)
		return (USBD_TOO_DEEP);

	if (PORTSTAT_ISSET(sc, 0)) { /* hub status change */
		usb_hub_status_t hs;

		err = usbd_get_hub_status(dev, &hs);
		if (err) {
			DPRINTF(("%s: get hub status failed, err=%d\n",
				 device_xname(sc->sc_dev), err));
		} else {
			/* just acknowledge */
			status = UGETW(hs.wHubStatus);
			change = UGETW(hs.wHubChange);
			if (change & UHS_LOCAL_POWER)
				usbd_clear_hub_feature(dev,
						       UHF_C_HUB_LOCAL_POWER);
			if (change & UHS_OVER_CURRENT)
				usbd_clear_hub_feature(dev,
						       UHF_C_HUB_OVER_CURRENT);
		}
	}

	for (port = 1; port <= hd->bNbrPorts; port++) {
		up = &dev->hub->ports[port-1];

		/* reattach is needed after firmware upload */
		reconnect = up->reattach;
		up->reattach = 0;

		status = change = 0;

		/* don't check if no change summary notification */
		if (PORTSTAT_ISSET(sc, port) || reconnect) {
			err = usbd_get_port_status(dev, port, &up->status);
			if (err) {
				DPRINTF(("uhub_explore: get port stat failed, "
					 "error=%s\n", usbd_errstr(err)));
				continue;
			}
			status = UGETW(up->status.wPortStatus);
			change = UGETW(up->status.wPortChange);
#if 0
			printf("%s port %d: s/c=%x/%x\n",
			       device_xname(sc->sc_dev), port, status, change);
#endif
		}
		if (!change && !reconnect) {
			/* No status change, just do recursive explore. */
			if (up->device != NULL && up->device->hub != NULL)
				up->device->hub->explore(up->device);
			continue;
		}

		if (change & UPS_C_PORT_ENABLED) {
			DPRINTF(("uhub_explore: C_PORT_ENABLED\n"));
			usbd_clear_port_feature(dev, port, UHF_C_PORT_ENABLE);
			if (change & UPS_C_CONNECT_STATUS) {
				/* Ignore the port error if the device
				   vanished. */
			} else if (status & UPS_PORT_ENABLED) {
				aprint_error_dev(sc->sc_dev,
				    "illegal enable change, port %d\n", port);
			} else {
				/* Port error condition. */
				if (up->restartcnt) /* no message first time */
					aprint_error_dev(sc->sc_dev,
					    "port error, restarting port %d\n",
					    port);

				if (up->restartcnt++ < USBD_RESTART_MAX)
					goto disco;
				else
					aprint_error_dev(sc->sc_dev,
					    "port error, giving up port %d\n",
					    port);
			}
		}

		/* XXX handle overcurrent and resume events! */

		if (!(change & UPS_C_CONNECT_STATUS))
			continue;

		/* We have a connect status change, handle it. */

		DPRINTF(("uhub_explore: status change hub=%d port=%d\n",
			 dev->address, port));
		usbd_clear_port_feature(dev, port, UHF_C_PORT_CONNECTION);
		/*
		 * If there is already a device on the port the change status
		 * must mean that is has disconnected.  Looking at the
		 * current connect status is not enough to figure this out
		 * since a new unit may have been connected before we handle
		 * the disconnect.
		 */
	disco:
		if (up->device != NULL) {
			/* Disconnected */
			DPRINTF(("uhub_explore: device addr=%d disappeared "
				 "on port %d\n", up->device->address, port));
			usb_disconnect_port(up, USBDEV(sc->sc_dev));
			usbd_clear_port_feature(dev, port,
						UHF_C_PORT_CONNECTION);
		}
		if (!(status & UPS_CURRENT_CONNECT_STATUS)) {
			/* Nothing connected, just ignore it. */
			DPRINTFN(3,("uhub_explore: port=%d !CURRENT_CONNECT"
				    "_STATUS\n", port));
			continue;
		}

		/* Connected */

		if (!(status & UPS_PORT_POWER))
			aprint_normal_dev(sc->sc_dev,
			    "strange, connected port %d has no power\n", port);

		/* Wait for maximum device power up time. */
		usbd_delay_ms(dev, USB_PORT_POWERUP_DELAY);

		/* Reset port, which implies enabling it. */
		if (usbd_reset_port(dev, port, &up->status)) {
			aprint_error_dev(sc->sc_dev,
			    "port %d reset failed\n", port);
			continue;
		}
		/* Get port status again, it might have changed during reset */
		err = usbd_get_port_status(dev, port, &up->status);
		if (err) {
			DPRINTF(("uhub_explore: get port status failed, "
				 "error=%s\n", usbd_errstr(err)));
			continue;
		}
		status = UGETW(up->status.wPortStatus);
		change = UGETW(up->status.wPortChange);
		if (!(status & UPS_CURRENT_CONNECT_STATUS)) {
			/* Nothing connected, just ignore it. */
#ifdef DIAGNOSTIC
			aprint_debug_dev(sc->sc_dev,
			    "port %d, device disappeared after reset\n", port);
#endif
			continue;
		}

		/* Figure out device speed */
		if (status & UPS_HIGH_SPEED)
			speed = USB_SPEED_HIGH;
		else if (status & UPS_LOW_SPEED)
			speed = USB_SPEED_LOW;
		else
			speed = USB_SPEED_FULL;
		/* Get device info and set its address. */
		err = usbd_new_device(USBDEV(sc->sc_dev), dev->bus,
			  dev->depth + 1, speed, port, up);
		/* XXX retry a few times? */
		if (err) {
			DPRINTFN(-1,("uhub_explore: usb_new_device failed, "
				     "error=%s\n", usbd_errstr(err)));
			/* Avoid addressing problems by disabling. */
			/* usbd_reset_port(dev, port, &up->status); */

			/*
			 * The unit refused to accept a new address, or had
			 * some other serious problem.  Since we cannot leave
			 * at 0 we have to disable the port instead.
			 */
			aprint_error_dev(sc->sc_dev,
			    "device problem, disabling port %d\n", port);
			usbd_clear_port_feature(dev, port, UHF_PORT_ENABLE);
		} else {
			/* The port set up succeeded, reset error count. */
			up->restartcnt = 0;

			if (up->device->hub)
				up->device->hub->explore(up->device);
		}
	}
	/* enable status change notifications again */
	if (!sc->sc_isehciroothub)
		memset(sc->sc_status, 0, sc->sc_statuslen);
	sc->sc_explorepending = 0;
	return (USBD_NORMAL_COMPLETION);
}

int
uhub_activate(device_t self, enum devact act)
{
	struct uhub_softc *sc = device_private(self);
	struct usbd_hub *hub = sc->sc_hub->hub;
	usbd_device_handle dev;
	int nports, port, i;

	switch (act) {
	case DVACT_ACTIVATE:
		return (EOPNOTSUPP);

	case DVACT_DEACTIVATE:
		if (hub == NULL) /* malfunctioning hub */
			break;
		nports = hub->hubdesc.bNbrPorts;
		for(port = 0; port < nports; port++) {
			dev = hub->ports[port].device;
			if (!dev)
				continue;
			for (i = 0; i < dev->subdevlen; i++)
				if (dev->subdevs[i])
					config_deactivate(dev->subdevs[i]);
		}
		break;
	}
	return (0);
}

/*
 * Called from process context when the hub is gone.
 * Detach all devices on active ports.
 */
USB_DETACH(uhub)
{
	USB_DETACH_START(uhub, sc);
	struct usbd_hub *hub = sc->sc_hub->hub;
	struct usbd_port *rup;
	int port, nports;

	DPRINTF(("uhub_detach: sc=%p flags=%d\n", sc, flags));

	if (hub == NULL)		/* Must be partially working */
		return (0);

	pmf_device_deregister(self);
	usbd_abort_pipe(sc->sc_ipipe);
	usbd_close_pipe(sc->sc_ipipe);

	nports = hub->hubdesc.bNbrPorts;
	for(port = 0; port < nports; port++) {
		rup = &hub->ports[port];
		if (rup->device)
			usb_disconnect_port(rup, self);
	}

	usbd_add_drv_event(USB_EVENT_DRIVER_DETACH, sc->sc_hub,
			   USBDEV(sc->sc_dev));

#if 0
	if (hub->ports[0].tt)
		free(hub->ports[0].tt, M_USBDEV);
#endif
	free(hub, M_USBDEV);
	sc->sc_hub->hub = NULL;
	if (sc->sc_status)
		free(sc->sc_status, M_USBDEV);
	if (sc->sc_statusbuf)
		free(sc->sc_statusbuf, M_USBDEV);

	return (0);
}

int
uhub_rescan(device_t self, const char *ifattr, const int *locators)
{
	struct uhub_softc *sc = device_private(self);
	struct usbd_hub *hub = sc->sc_hub->hub;
	usbd_device_handle dev;
	int port, err;

	for (port = 0; port < hub->hubdesc.bNbrPorts; port++) {
		dev = hub->ports[port].device;
		if (dev == NULL)
			continue;
		err = usbd_reattach_device(USBDEV(sc->sc_dev), dev,
					   port, locators);
	}
	return 0;
}

/* Called when a device has been detached from it */
void
uhub_childdet(device_t self, device_t child)
{
	struct uhub_softc *sc = device_private(self);
	usbd_device_handle devhub = sc->sc_hub;
	usbd_device_handle dev;
	int nports;
	int port;
	int i;

	if (!devhub->hub)
		/* should never happen; children are only created after init */
		panic("hub not fully initialised, but child deleted?");

	nports = devhub->hub->hubdesc.bNbrPorts;
	for (port = 0; port < nports; port++) {
		dev = devhub->hub->ports[port].device;
		if (!dev)
			continue;
		for (i = 0; i < dev->subdevlen; i++) {
			if (dev->subdevs[i] == child) {
				dev->subdevs[i] = NULL;
				dev->nifaces_claimed--;
			}
		}
	}
}


/*
 * Hub interrupt.
 * This an indication that some port has changed status.
 * Notify the bus event handler thread that we need
 * to be explored again.
 */
void
uhub_intr(usbd_xfer_handle xfer, usbd_private_handle addr,
    usbd_status status)
{
	struct uhub_softc *sc = addr;

	DPRINTFN(5,("uhub_intr: sc=%p\n", sc));

	if (status == USBD_STALLED)
		usbd_clear_endpoint_stall_async(sc->sc_ipipe);
	else if (status == USBD_NORMAL_COMPLETION &&
		 !sc->sc_explorepending) {
		/*
		 * Make sure the status is not overwritten in between.
		 * XXX we should suspend the pipe instead
		 */
		memcpy(sc->sc_status, sc->sc_statusbuf, sc->sc_statuslen);
		sc->sc_explorepending = 1;
		usb_needs_explore(sc->sc_hub);
	}
	/*
	 * XXX workaround for broken implementation of the interrupt
	 * pipe in EHCI root hub emulation which doesn't resend
	 * status change notifications until handled: force a rescan
	 * of the ports we touched in the last run
	 */
	if (status == USBD_NORMAL_COMPLETION && sc->sc_explorepending &&
	    sc->sc_isehciroothub)
		usb_needs_explore(sc->sc_hub);
}
