/*	$NetBSD: amdpmvar.h,v 1.6 2008/04/28 20:23:54 martin Exp $	*/

/*-
 * Copyright (c) 2002 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Enami Tsugutomo.
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

#ifndef _DEV_PCI_AMDPMVAR_H_
#define _DEV_PCI_AMDPMVAR_H_

#include <sys/rwlock.h>

struct amdpm_softc {
	struct device sc_dev;

	pci_chipset_tag_t sc_pc;
	pcitag_t sc_tag;
	struct pci_attach_args *sc_pa;

	bus_space_tag_t sc_iot;
	bus_space_handle_t sc_ioh;		/* PMxx space */
	bus_space_handle_t sc_sm_ioh;		/* SM space */

	i2c_addr_t sc_smbus_slaveaddr;		/* address of smbus slave */
	struct i2c_controller sc_i2c;		/* i2c controller info */
	krwlock_t sc_rwlock;

	void *sc_ih;

	struct callout sc_rnd_ch;
	rndsource_element_t sc_rnd_source;
#ifdef AMDPM_RND_COUNTERS
	struct evcnt sc_rnd_hits;
	struct evcnt sc_rnd_miss;
	struct evcnt sc_rnd_data[256];
#endif

	char sc_nforce;
};

#endif /* _DEV_PCI_AMDPMVAR_H_ */
