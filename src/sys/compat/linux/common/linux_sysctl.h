/*	$NetBSD: linux_sysctl.h,v 1.4 2008/04/28 20:23:44 martin Exp $	*/

/*-
 * Copyright (c) 2002 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Christos Zoulas.
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

#ifndef _LINUX_SYSCTL_H
#define _LINUX_SYSCTL_H

#define LINUX_CTL_MAXNAME					10

#define	LINUX_CTL_NONE						0
#define	LINUX_CTL_KERN						1
#define	LINUX_CTL_VM						2
#define	LINUX_CTL_NET						3
#define	LINUX_CTL_PROC						4
#define	LINUX_CTL_FS						5
#define	LINUX_CTL_DEBUG						6
#define	LINUX_CTL_DEV						7
#define	LINUX_CTL_BUS						8


#define	LINUX_KERN_OSTYPE					1
#define	LINUX_KERN_OSRELEASE					2
#define	LINUX_KERN_OSREV					3
#define	LINUX_KERN_VERSION					4
#define	LINUX_KERN_SECUREMASK					5
#define	LINUX_KERN_PROF						6
#define	LINUX_KERN_NODENAME					7
#define	LINUX_KERN_DOMAINNAME					8
#define	LINUX_KERN_CAP_BSET					14
#define	LINUX_KERN_PANIC					15
#define	LINUX_KERN_REALROOTDEV					16
#define	LINUX_KERN_SPARC_REBOOT					21
#define	LINUX_KERN_CTLALTDEL					22
#define	LINUX_KERN_PRINTK					23
#define	LINUX_KERN_NAMETRANS					24
#define	LINUX_KERN_PPC_HTABRECLAIM				25
#define	LINUX_KERN_PPC_ZEROPAGED				26
#define	LINUX_KERN_PPC_POWERSAVE_NAP				27
#define	LINUX_KERN_MODPROBE					28
#define	LINUX_KERN_SG_BIG_BUFF					29
#define	LINUX_KERN_ACCT						30
#define	LINUX_KERN_PPC_L2CR					31
#define	LINUX_KERN_RTSIGNR					32
#define	LINUX_KERN_RTSIGMAX					33
#define	LINUX_KERN_SHMMAX					34
#define	LINUX_KERN_MSGMAX					35
#define	LINUX_KERN_MSGMNB					36
#define	LINUX_KERN_MSGPOOL					37
#define	LINUX_KERN_SYSRQ					38
#define	LINUX_KERN_MAX_THREADS					39
#define	LINUX_KERN_RANDOM					40
#define	LINUX_KERN_SHMALL					41
#define	LINUX_KERN_MSGMNI					42
#define	LINUX_KERN_SEM						43
#define	LINUX_KERN_SPARC_STOP_A					44
#define	LINUX_KERN_SHMMNI					45
#define	LINUX_KERN_OVERFLOWUID					46
#define	LINUX_KERN_OVERFLOWGID					47
#define	LINUX_KERN_SHMPATH					48
#define	LINUX_KERN_HOTPLUG					49
#define	LINUX_KERN_IEEE_EMULATION_WARNINGS			50
#define	LINUX_KERN_S390_USER_DEBUG_LOGGING			51
#define	LINUX_KERN_PROF_PID					52

#define	LINUX_VM_SWAPCTL					1
#define	LINUX_VM_SWAPOUT					2
#define	LINUX_VM_FREEPG						3
#define	LINUX_VM_BDFLUSH					4
#define	LINUX_VM_OVERCOMMIT_MEMORY				5
#define	LINUX_VM_BUFFERMEM					6
#define	LINUX_VM_PAGECACHE					7
#define	LINUX_VM_PAGERDAEMON					8
#define	LINUX_VM_PGT_CACHE					9
#define	LINUX_VM_PAGE_CLUSTER					10
#define	LINUX_VM_MAX_MAP_COUNT					11

#define	LINUX_NET_CORE						1
#define	LINUX_NET_ETHER						2
#define	LINUX_NET_802						3
#define	LINUX_NET_UNIX						4
#define	LINUX_NET_IPV4						5
#define	LINUX_NET_IPX						6
#define	LINUX_NET_ATALK						7
#define	LINUX_NET_NETROM					8
#define	LINUX_NET_AX25						9
#define	LINUX_NET_BRIDGE					10
#define	LINUX_NET_ROSE						11
#define	LINUX_NET_IPV6						12
#define	LINUX_NET_X25						13
#define	LINUX_NET_TR						14
#define	LINUX_NET_DECNET					15
#define	LINUX_NET_ECONET					16
#define	LINUX_NET_KHTTPD					17
#define	LINUX_NET_TUX						18

#define	LINUX_NET_CORE_RMEM_MAX					2
#define	LINUX_NET_CORE_WMEM_DEFAULT				3
#define	LINUX_NET_CORE_RMEM_DEFAULT				4
#define	LINUX_NET_CORE_MAX_BACKLOG				6
#define	LINUX_NET_CORE_FASTROUTE				7
#define	LINUX_NET_CORE_MSG_COST					8
#define	LINUX_NET_CORE_MSG_BURST				9
#define	LINUX_NET_CORE_OPTMEM_MAX				10
#define	LINUX_NET_CORE_HOT_LIST_LENGTH				11
#define	LINUX_NET_CORE_DIVERT_VERSION				12
#define	LINUX_NET_CORE_NO_CONG_THRESH				13
#define	LINUX_NET_CORE_NO_CONG					14
#define	LINUX_NET_CORE_LO_CONG					15
#define	LINUX_NET_CORE_MOD_CONG					16

#define	LINUX_NET_UNIX_DESTROY_DELAY				1
#define	LINUX_NET_UNIX_DELETE_DELAY				2
#define	LINUX_NET_UNIX_MAX_DGRAM_QLEN				3

#define	LINUX_NET_IPV4_FORWARD					8
#define	LINUX_NET_IPV4_DYNADDR					9
#define	LINUX_NET_IPV4_CONF					16
#define	LINUX_NET_IPV4_NEIGH					17
#define	LINUX_NET_IPV4_ROUTE					18
#define	LINUX_NET_IPV4_FIB_HASH					19
#define	LINUX_NET_IPV4_TCP_TIMESTAMPS				33
#define	LINUX_NET_IPV4_TCP_WINDOW_SCALING			34
#define	LINUX_NET_IPV4_TCP_SACK					35
#define	LINUX_NET_IPV4_TCP_RETRANS_COLLAPSE			36
#define	LINUX_NET_IPV4_DEFAULT_TTL				37
#define	LINUX_NET_IPV4_AUTOCONFIG				38
#define	LINUX_NET_IPV4_NO_PMTU_DISC				39
#define	LINUX_NET_IPV4_TCP_SYN_RETRIES				40
#define	LINUX_NET_IPV4_IPFRAG_HIGH_THRESH			41
#define	LINUX_NET_IPV4_IPFRAG_LOW_THRESH			42
#define	LINUX_NET_IPV4_IPFRAG_TIME				43
#define	LINUX_NET_IPV4_TCP_MAX_KA_PROBES			44
#define	LINUX_NET_IPV4_TCP_KEEPALIVE_TIME			45
#define	LINUX_NET_IPV4_TCP_KEEPALIVE_PROBES			46
#define	LINUX_NET_IPV4_TCP_RETRIES1				47
#define	LINUX_NET_IPV4_TCP_RETRIES2				48
#define	LINUX_NET_IPV4_TCP_FIN_TIMEOUT				49
#define	LINUX_NET_IPV4_IP_MASQ_DEBUG				50
#define	LINUX_NET_TCP_SYNCOOKIES				51
#define	LINUX_NET_TCP_STDURG					52
#define	LINUX_NET_TCP_RFC1337					53
#define	LINUX_NET_TCP_SYN_TAILDROP				54
#define	LINUX_NET_TCP_MAX_SYN_BACKLOG				55
#define	LINUX_NET_IPV4_LOCAL_PORT_RANGE				56
#define	LINUX_NET_IPV4_ICMP_ECHO_IGNORE_ALL			57
#define	LINUX_NET_IPV4_ICMP_ECHO_IGNORE_BROADCASTS		58
#define	LINUX_NET_IPV4_ICMP_SOURCEQUENCH_RATE			59
#define	LINUX_NET_IPV4_ICMP_DESTUNREACH_RATE			60
#define	LINUX_NET_IPV4_ICMP_TIMEEXCEED_RATE			61
#define	LINUX_NET_IPV4_ICMP_PARAMPROB_RATE			62
#define	LINUX_NET_IPV4_ICMP_ECHOREPLY_RATE			63
#define	LINUX_NET_IPV4_ICMP_IGNORE_BOGUS_ERROR_RESPONSES	64
#define	LINUX_NET_IPV4_IGMP_MAX_MEMBERSHIPS			65
#define	LINUX_NET_TCP_TW_RECYCLE				66
#define	LINUX_NET_IPV4_ALWAYS_DEFRAG				67
#define	LINUX_NET_IPV4_TCP_KEEPALIVE_INTVL			68
#define	LINUX_NET_IPV4_INET_PEER_THRESHOLD			69
#define	LINUX_NET_IPV4_INET_PEER_MINTTL				70
#define	LINUX_NET_IPV4_INET_PEER_MAXTTL				71
#define	LINUX_NET_IPV4_INET_PEER_GC_MINTIME			72
#define	LINUX_NET_IPV4_INET_PEER_GC_MAXTIME			73
#define	LINUX_NET_TCP_ORPHAN_RETRIES				74
#define	LINUX_NET_TCP_ABORT_ON_OVERFLOW				75
#define	LINUX_NET_TCP_SYNACK_RETRIES				76
#define	LINUX_NET_TCP_MAX_ORPHANS				77
#define	LINUX_NET_TCP_MAX_TW_BUCKETS				78
#define	LINUX_NET_TCP_FACK					79
#define	LINUX_NET_TCP_REORDERING				80
#define	LINUX_NET_TCP_ECN					81
#define	LINUX_NET_TCP_DSACK					82
#define	LINUX_NET_TCP_MEM					83
#define	LINUX_NET_TCP_WMEM					84
#define	LINUX_NET_TCP_RMEM					85
#define	LINUX_NET_TCP_APP_WIN					86
#define	LINUX_NET_TCP_ADV_WIN_SCALE				87
#define	LINUX_NET_IPV4_NONLOCAL_BIND				88

#define	LINUX_NET_IPV4_ROUTE_FLUSH				1
#define	LINUX_NET_IPV4_ROUTE_MIN_DELAY				2
#define	LINUX_NET_IPV4_ROUTE_MAX_DELAY				3
#define	LINUX_NET_IPV4_ROUTE_GC_THRESH				4
#define	LINUX_NET_IPV4_ROUTE_MAX_SIZE				5
#define	LINUX_NET_IPV4_ROUTE_GC_MIN_INTERVAL			6
#define	LINUX_NET_IPV4_ROUTE_GC_TIMEOUT				7
#define	LINUX_NET_IPV4_ROUTE_GC_INTERVAL			8
#define	LINUX_NET_IPV4_ROUTE_REDIRECT_LOAD			9
#define	LINUX_NET_IPV4_ROUTE_REDIRECT_NUMBER			10
#define	LINUX_NET_IPV4_ROUTE_REDIRECT_SILENCE			11
#define	LINUX_NET_IPV4_ROUTE_ERROR_COST				12
#define	LINUX_NET_IPV4_ROUTE_ERROR_BURST			13
#define	LINUX_NET_IPV4_ROUTE_GC_ELASTICITY			14
#define	LINUX_NET_IPV4_ROUTE_MTU_EXPIRES			15
#define	LINUX_NET_IPV4_ROUTE_MIN_PMTU				16
#define	LINUX_NET_IPV4_ROUTE_MIN_ADVMSS				17

#define	LINUX_NET_PROTO_CONF_ALL				-2
#define	LINUX_NET_PROTO_CONF_DEFAULT				-3

#define	LINUX_NET_IPV4_CONF_FORWARDING				1
#define	LINUX_NET_IPV4_CONF_MC_FORWARDING			2
#define	LINUX_NET_IPV4_CONF_PROXY_ARP				3
#define	LINUX_NET_IPV4_CONF_ACCEPT_REDIRECTS			4
#define	LINUX_NET_IPV4_CONF_SECURE_REDIRECTS			5
#define	LINUX_NET_IPV4_CONF_SEND_REDIRECTS			6
#define	LINUX_NET_IPV4_CONF_SHARED_MEDIA			7
#define	LINUX_NET_IPV4_CONF_RP_FILTER				8
#define	LINUX_NET_IPV4_CONF_ACCEPT_SOURCE_ROUTE			9
#define	LINUX_NET_IPV4_CONF_BOOTP_RELAY				10
#define	LINUX_NET_IPV4_CONF_LOG_MARTIANS			11
#define	LINUX_NET_IPV4_CONF_TAG					12

#define	LINUX_NET_IPV6_ROUTE_FLUSH				1
#define	LINUX_NET_IPV6_ROUTE_GC_THRESH				2
#define	LINUX_NET_IPV6_ROUTE_MAX_SIZE				3
#define	LINUX_NET_IPV6_ROUTE_GC_MIN_INTERVAL			4
#define	LINUX_NET_IPV6_ROUTE_GC_TIMEOUT				5
#define	LINUX_NET_IPV6_ROUTE_GC_INTERVAL			6
#define	LINUX_NET_IPV6_ROUTE_GC_ELASTICITY			7
#define	LINUX_NET_IPV6_ROUTE_MTU_EXPIRES			8
#define	LINUX_NET_IPV6_ROUTE_MIN_ADVMSS				9

#define	LINUX_NET_IPV6_FORWARDING				1
#define	LINUX_NET_IPV6_HOP_LIMIT				2
#define	LINUX_NET_IPV6_MTU					3
#define	LINUX_NET_IPV6_ACCEPT_RA				4
#define	LINUX_NET_IPV6_ACCEPT_REDIRECTS				5
#define	LINUX_NET_IPV6_AUTOCONF					6
#define	LINUX_NET_IPV6_DAD_TRANSMITS				7
#define	LINUX_NET_IPV6_RTR_SOLICITS				8
#define	LINUX_NET_IPV6_RTR_SOLICIT_INTERVAL			9
#define	LINUX_NET_IPV6_RTR_SOLICIT_DELAY			10

#define	LINUX_NET_NEIGH_MCAST_SOLICIT				1
#define	LINUX_NET_NEIGH_UCAST_SOLICIT				2
#define	LINUX_NET_NEIGH_APP_SOLICIT				3
#define	LINUX_NET_NEIGH_RETRANS_TIME				4
#define	LINUX_NET_NEIGH_REACHABLE_TIME				5
#define	LINUX_NET_NEIGH_DELAY_PROBE_TIME			6
#define	LINUX_NET_NEIGH_GC_STALE_TIME				7
#define	LINUX_NET_NEIGH_UNRES_QLEN				8
#define	LINUX_NET_NEIGH_PROXY_QLEN				9
#define	LINUX_NET_NEIGH_ANYCAST_DELAY				10
#define	LINUX_NET_NEIGH_PROXY_DELAY				11
#define	LINUX_NET_NEIGH_LOCKTIME				12
#define	LINUX_NET_NEIGH_GC_INTERVAL				13
#define	LINUX_NET_NEIGH_GC_THRESH1				14
#define	LINUX_NET_NEIGH_GC_THRESH2				15
#define	LINUX_NET_NEIGH_GC_THRESH3				16

#define	LINUX_NET_IPX_PPROP_BROADCASTING			1
#define	LINUX_NET_IPX_FORWARDING				2

#define	LINUX_NET_ATALK_AARP_EXPIRY_TIME			1
#define	LINUX_NET_ATALK_AARP_TICK_TIME				2
#define	LINUX_NET_ATALK_AARP_RETRANSMIT_LIMIT			3
#define	LINUX_NET_ATALK_AARP_RESOLVE_TIME			4

#define	LINUX_NET_NETROM_DEFAULT_PATH_QUALITY			1
#define	LINUX_NET_NETROM_OBSOLESCENCE_COUNT_INITIALISER		2
#define	LINUX_NET_NETROM_NETWORK_TTL_INITIALISER		3
#define	LINUX_NET_NETROM_TRANSPORT_TIMEOUT			4
#define	LINUX_NET_NETROM_TRANSPORT_MAXIMUM_TRIES		5
#define	LINUX_NET_NETROM_TRANSPORT_ACKNOWLEDGE_DELAY		6
#define	LINUX_NET_NETROM_TRANSPORT_BUSY_DELAY			7
#define	LINUX_NET_NETROM_TRANSPORT_REQUESTED_WINDOW_SIZE	8
#define	LINUX_NET_NETROM_TRANSPORT_NO_ACTIVITY_TIMEOUT		9
#define	LINUX_NET_NETROM_ROUTING_CONTROL			10
#define	LINUX_NET_NETROM_LINK_FAILS_COUNT			11

#define	LINUX_NET_AX25_IP_DEFAULT_MODE				1
#define	LINUX_NET_AX25_DEFAULT_MODE				2
#define	LINUX_NET_AX25_BACKOFF_TYPE				3
#define	LINUX_NET_AX25_CONNECT_MODE				4
#define	LINUX_NET_AX25_STANDARD_WINDOW				5
#define	LINUX_NET_AX25_EXTENDED_WINDOW				6
#define	LINUX_NET_AX25_T1_TIMEOUT				7
#define	LINUX_NET_AX25_T2_TIMEOUT				8
#define	LINUX_NET_AX25_T3_TIMEOUT				9
#define	LINUX_NET_AX25_IDLE_TIMEOUT				10
#define	LINUX_NET_AX25_N2					11
#define	LINUX_NET_AX25_PACLEN					12
#define	LINUX_NET_AX25_PROTOCOL					13
#define	LINUX_NET_AX25_DAMA_SLAVE_TIMEOUT			14

#define	LINUX_NET_ROSE_RESTART_REQUEST_TIMEOUT			1
#define	LINUX_NET_ROSE_CALL_REQUEST_TIMEOUT			2
#define	LINUX_NET_ROSE_RESET_REQUEST_TIMEOUT			3
#define	LINUX_NET_ROSE_CLEAR_REQUEST_TIMEOUT			4
#define	LINUX_NET_ROSE_ACK_HOLD_BACK_TIMEOUT			5
#define	LINUX_NET_ROSE_ROUTING_CONTROL				6
#define	LINUX_NET_ROSE_LINK_FAIL_TIMEOUT			7
#define	LINUX_NET_ROSE_MAX_VCS					8
#define	LINUX_NET_ROSE_WINDOW_SIZE				9
#define	LINUX_NET_ROSE_NO_ACTIVITY_TIMEOUT			10

#define	LINUX_NET_X25_RESTART_REQUEST_TIMEOUT			1
#define	LINUX_NET_X25_CALL_REQUEST_TIMEOUT			2
#define	LINUX_NET_X25_RESET_REQUEST_TIMEOUT			3
#define	LINUX_NET_X25_CLEAR_REQUEST_TIMEOUT			4
#define	LINUX_NET_X25_ACK_HOLD_BACK_TIMEOUT			5

#define	LINUX_NET_TR_RIF_TIMEOUT				1

#define	LINUX_NET_DECNET_NODE_TYPE 	 			1
#define	LINUX_NET_DECNET_NODE_ADDRESS 				2
#define	LINUX_NET_DECNET_NODE_NAME 				3
#define	LINUX_NET_DECNET_DEFAULT_DEVICE 			4
#define	LINUX_NET_DECNET_TIME_WAIT 	 			5
#define	LINUX_NET_DECNET_DN_COUNT 	 			6
#define	LINUX_NET_DECNET_DI_COUNT 	 			7
#define	LINUX_NET_DECNET_DR_COUNT 	 			8
#define	LINUX_NET_DECNET_DST_GC_INTERVAL 			9
#define	LINUX_NET_DECNET_CONF 					10
#define	LINUX_NET_DECNET_DEBUG_LEVEL 	 			255

#define	LINUX_NET_TUX_DOCROOT					1
#define	LINUX_NET_TUX_LOGFILE					2
#define	LINUX_NET_TUX_EXTCGI					3
#define	LINUX_NET_TUX_STOP					4
#define	LINUX_NET_TUX_CLIENTPORT				5
#define	LINUX_NET_TUX_LOGGING					6
#define	LINUX_NET_TUX_SERVERPORT				7
#define	LINUX_NET_TUX_THREADS					8
#define	LINUX_NET_TUX_KEEPALIVE_TIMEOUT				9
#define	LINUX_NET_TUX_MAX_KEEPALIVE_BW				10
#define	LINUX_NET_TUX_DEFER_ACCEPT				11
#define	LINUX_NET_TUX_MAX_FREE_REQUESTS				12
#define	LINUX_NET_TUX_MAX_CONNECT				13
#define	LINUX_NET_TUX_MAX_BACKLOG				14
#define	LINUX_NET_TUX_MODE_FORBIDDEN				15
#define	LINUX_NET_TUX_MODE_ALLOWED				16
#define	LINUX_NET_TUX_MODE_USERSPACE				17
#define	LINUX_NET_TUX_MODE_CGI					18
#define	LINUX_NET_TUX_CGI_UID					19
#define	LINUX_NET_TUX_CGI_GID					20
#define	LINUX_NET_TUX_CGIROOT					21
#define	LINUX_NET_TUX_LOGENTRY_ALIGN_ORDER			22
#define	LINUX_NET_TUX_NONAGLE					23
#define	LINUX_NET_TUX_ACK_PINGPONG				24
#define	LINUX_NET_TUX_PUSH_ALL					25
#define	LINUX_NET_TUX_ZEROCOPY_PARSE				26
#define	LINUX_NET_CONFIG_TUX_DEBUG_BLOCKING			27
#define	LINUX_NET_TUX_PAGE_AGE_START				28

#define	LINUX_NET_KHTTPD_DOCROOT      	 			1
#define	LINUX_NET_KHTTPD_START        	 			2
#define	LINUX_NET_KHTTPD_STOP         	 			3
#define	LINUX_NET_KHTTPD_UNLOAD       	 			4
#define	LINUX_NET_KHTTPD_CLIENTPORT   	 			5
#define	LINUX_NET_KHTTPD_PERMREQ      	 			6
#define	LINUX_NET_KHTTPD_PERMFORBID   	 			7
#define	LINUX_NET_KHTTPD_LOGGING      	 			8
#define	LINUX_NET_KHTTPD_SERVERPORT   	 			9
#define	LINUX_NET_KHTTPD_DYNAMICSTRING	 			10
#define	LINUX_NET_KHTTPD_SLOPPYMIME   	 			11
#define	LINUX_NET_KHTTPD_THREADS      	 			12
#define	LINUX_NET_KHTTPD_MAXCONNECT   	 			13

#define	LINUX_NET_DECNET_CONF_LOOPBACK 				-2
#define	LINUX_NET_DECNET_CONF_DDCMP 	 			-3
#define	LINUX_NET_DECNET_CONF_PPP 	 			-4
#define	LINUX_NET_DECNET_CONF_X25 	 			-5
#define	LINUX_NET_DECNET_CONF_GRE 	 			-6
#define	LINUX_NET_DECNET_CONF_ETHER 				-7

#define	LINUX_NET_DECNET_CONF_DEV_PRIORITY 	 		1
#define	LINUX_NET_DECNET_CONF_DEV_T1 		 		2
#define	LINUX_NET_DECNET_CONF_DEV_T2 		 		3
#define	LINUX_NET_DECNET_CONF_DEV_T3 		 		4
#define	LINUX_NET_DECNET_CONF_DEV_FORWARDING 	 		5
#define	LINUX_NET_DECNET_CONF_DEV_BLKSIZE 	 		6
#define	LINUX_NET_DECNET_CONF_DEV_STATE 			7

#define	LINUX_FS_NRINODE					1
#define	LINUX_FS_STATINODE					2
#define	LINUX_FS_MAXINODE					3
#define	LINUX_FS_NRDQUOT					4
#define	LINUX_FS_MAXDQUOT					5
#define	LINUX_FS_NRFILE						6
#define	LINUX_FS_MAXFILE					7
#define	LINUX_FS_DENTRY						8
#define	LINUX_FS_NRSUPER					9
#define	LINUX_FS_MAXSUPER					10
#define	LINUX_FS_OVERFLOWUID					11
#define	LINUX_FS_OVERFLOWGID					12
#define	LINUX_FS_LEASES						13
#define	LINUX_FS_DIR_NOTIFY					14
#define	LINUX_FS_LEASE_TIME					15

#define	LINUX_DEV_CDROM						1
#define	LINUX_DEV_HWMON						2
#define	LINUX_DEV_PARPORT					3
#define	LINUX_DEV_RAID						4
#define	LINUX_DEV_MAC_HID					5

#define	LINUX_DEV_CDROM_INFO					1
#define	LINUX_DEV_CDROM_AUTOCLOSE				2
#define	LINUX_DEV_CDROM_AUTOEJECT				3
#define	LINUX_DEV_CDROM_DEBUG					4
#define	LINUX_DEV_CDROM_LOCK					5
#define	LINUX_DEV_CDROM_CHECK_MEDIA				6

#define	LINUX_DEV_PARPORT_DEFAULT				-3

#define	LINUX_DEV_RAID_SPEED_LIMIT_MIN				1
#define	LINUX_DEV_RAID_SPEED_LIMIT_MAX				2

#define	LINUX_DEV_PARPORT_DEFAULT_TIMESLICE			1
#define	LINUX_DEV_PARPORT_DEFAULT_SPINTIME			2

#define	LINUX_DEV_PARPORT_SPINTIME				1
#define	LINUX_DEV_PARPORT_BASE_ADDR				2
#define	LINUX_DEV_PARPORT_IRQ					3
#define	LINUX_DEV_PARPORT_DMA					4
#define	LINUX_DEV_PARPORT_MODES					5
#define	LINUX_DEV_PARPORT_DEVICES				6
#define	LINUX_DEV_PARPORT_AUTOPROBE				16

#define	LINUX_DEV_PARPORT_DEVICES_ACTIVE			-3
#define	LINUX_DEV_PARPORT_DEVICE_TIMESLICE			1

#define	LINUX_DEV_MAC_HID_KEYBOARD_SENDS_LINUX_KEYCODES		1
#define	LINUX_DEV_MAC_HID_KEYBOARD_LOCK_KEYCODES		2
#define	LINUX_DEV_MAC_HID_MOUSE_BUTTON_EMULATION		3
#define	LINUX_DEV_MAC_HID_MOUSE_BUTTON2_KEYCODE			4
#define	LINUX_DEV_MAC_HID_MOUSE_BUTTON3_KEYCODE			5
#define	LINUX_DEV_MAC_HID_ADB_MOUSE_SENDS_KEYCODES		6

#define	LINUX_RANDOM_POOLSIZE					1
#define	LINUX_RANDOM_ENTROPY_COUNT				2
#define	LINUX_RANDOM_READ_THRESH				3
#define	LINUX_RANDOM_WRITE_THRESH				4
#define	LINUX_RANDOM_BOOT_ID					5
#define	LINUX_RANDOM_UUID					6

#define	LINUX_BUS_ISA						1

#define	LINUX_BUS_ISA_MEM_BASE					1
#define	LINUX_BUS_ISA_PORT_BASE					2
#define	LINUX_BUS_ISA_PORT_SHIFT				3

#ifdef SYSCTL_SETUP_PROTO
SYSCTL_SETUP_PROTO(linux_sysctl_setup);
SYSCTL_SETUP_PROTO(sysctl_emul_linux_setup);
#endif /* SYSCTL_SETUP_PROTO */
#endif /* !_LINUX_SYSCTL_H */
