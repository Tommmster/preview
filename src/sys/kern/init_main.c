/*	$NetBSD: init_main.c,v 1.371.2.4 2010/02/14 13:35:43 bouyer Exp $	*/

/*-
 * Copyright (c) 2008, 2009 The NetBSD Foundation, Inc.
 * All rights reserved.
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
 * Copyright (c) 1982, 1986, 1989, 1991, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)init_main.c	8.16 (Berkeley) 5/14/95
 */

/*
 * Copyright (c) 1995 Christopher G. Demetriou.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)init_main.c	8.16 (Berkeley) 5/14/95
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD: init_main.c,v 1.371.2.4 2010/02/14 13:35:43 bouyer Exp $");

#include "opt_ddb.h"
#include "opt_ipsec.h"
#include "opt_ntp.h"
#include "opt_pipe.h"
#include "opt_posix.h"
#include "opt_syscall_debug.h"
#include "opt_sysv.h"
#include "opt_fileassoc.h"
#include "opt_ktrace.h"
#include "opt_pax.h"
#include "opt_wapbl.h"

#include "rnd.h"
#include "ksyms.h"
#include "sysmon_envsys.h"
#include "sysmon_power.h"
#include "sysmon_taskq.h"
#include "sysmon_wdog.h"
#include "veriexec.h"

#include <sys/param.h>
#include <sys/acct.h>
#include <sys/filedesc.h>
#include <sys/file.h>
#include <sys/errno.h>
#include <sys/callout.h>
#include <sys/cpu.h>
#include <sys/kernel.h>
#include <sys/mount.h>
#include <sys/proc.h>
#include <sys/kthread.h>
#include <sys/resourcevar.h>
#include <sys/signalvar.h>
#include <sys/systm.h>
#include <sys/vnode.h>
#include <sys/fstrans.h>
#include <sys/tty.h>
#include <sys/conf.h>
#include <sys/disklabel.h>
#include <sys/buf.h>
#include <sys/device.h>
#include <sys/exec.h>
#include <sys/socketvar.h>
#include <sys/protosw.h>
#include <sys/percpu.h>
#include <sys/pset.h>
#include <sys/sysctl.h>
#include <sys/reboot.h>
#include <sys/user.h>
#include <sys/sysctl.h>
#include <sys/event.h>
#include <sys/mbuf.h>
#include <sys/sched.h>
#include <sys/sleepq.h>
#include <sys/iostat.h>
#include <sys/vmem.h>
#include <sys/uuid.h>
#include <sys/extent.h>
#include <sys/disk.h>
#include <sys/mqueue.h>
#include <sys/msgbuf.h>
#include <sys/module.h>
#include <sys/event.h>
#include <sys/lockf.h>
#include <sys/once.h>
#include <sys/ksyms.h>
#include <sys/uidinfo.h>
#ifdef FAST_IPSEC
#include <netipsec/ipsec.h>
#endif
#ifdef SYSVSHM
#include <sys/shm.h>
#endif
#ifdef SYSVSEM
#include <sys/sem.h>
#endif
#ifdef SYSVMSG
#include <sys/msg.h>
#endif
#ifdef P1003_1B_SEMAPHORE
#include <sys/ksem.h>
#endif
#include <sys/domain.h>
#include <sys/namei.h>
#if NRND > 0
#include <sys/rnd.h>
#endif
#include <sys/pipe.h>
#ifdef LKM
#include <sys/lkm.h>
#endif
#if NVERIEXEC > 0
#include <sys/verified_exec.h>
#endif /* NVERIEXEC > 0 */
#ifdef KTRACE
#include <sys/ktrace.h>
#endif
#include <sys/kauth.h>
#ifdef WAPBL
#include <sys/wapbl.h>
#endif
#include <net80211/ieee80211_netbsd.h>

#include <sys/syscall.h>
#include <sys/syscallargs.h>

#if defined(PAX_MPROTECT) || defined(PAX_SEGVGUARD) || defined(PAX_ASLR)
#include <sys/pax.h>
#endif /* PAX_MPROTECT || PAX_SEGVGUARD || PAX_ASLR */

#include <ufs/ufs/quota.h>

#include <miscfs/genfs/genfs.h>
#include <miscfs/syncfs/syncfs.h>

#include <sys/cpu.h>

#include <uvm/uvm.h>

#if NSYSMON_TASKQ > 0
#include <dev/sysmon/sysmon_taskq.h>
#endif

#include <dev/cons.h>

#if NSYSMON_ENVSYS > 0 || NSYSMON_POWER > 0 || NSYSMON_WDOG > 0
#include <dev/sysmon/sysmonvar.h>
#endif

#include <net/if.h>
#include <net/raw_cb.h>

#include <secmodel/secmodel.h>

extern struct proc proc0;
extern struct lwp lwp0;
extern struct cwdinfo cwdi0;
extern time_t rootfstime;

#ifndef curlwp
struct	lwp *curlwp = &lwp0;
#endif
struct	proc *initproc;

struct	vnode *rootvp, *swapdev_vp;
int	boothowto;
int	cold = 1;			/* still working on startup */
struct timeval boottime;	        /* time at system startup - will only follow settime deltas */

int	start_init_exec;		/* semaphore for start_init() */

static void check_console(struct lwp *l);
static void start_init(void *);
void main(void);

void __secmodel_none(void);
__weak_alias(secmodel_start,__secmodel_none);
void
__secmodel_none(void)
{
	return;
}

/*
 * System startup; initialize the world, create process 0, mount root
 * filesystem, and fork to create init and pagedaemon.  Most of the
 * hard work is done in the lower-level initialization routines including
 * startup(), which does memory initialization and autoconfiguration.
 */
#define main_logger(s)	printf("XXXAVR32 %s %s %d : %s\n", __FILE__,__FUNCTION__ ,__LINE__,(s))
void
main(void)
{
	struct timeval time;
	struct lwp *l;
	struct proc *p;
	int s, error;
#ifdef NVNODE_IMPLICIT
	int usevnodes;
#endif
	CPU_INFO_ITERATOR cii;
	struct cpu_info *ci;

	printf("L_ADDR %d\n", offsetof(struct lwp, l_addr));
	printf("U_PCB_ONFAULT %d\n", offsetof(struct pcb, pcb_onfault));
	printf("U_PCB_CONTEXT %d\n", offsetof(struct pcb, pcb_context));
	printf("L_MD_UPTE0 %d\n",offsetof(struct lwp, l_md.md_upte[0]));
	printf("L_MD_UPTE1 %d\n",offsetof(struct lwp, l_md.md_upte[1]));

	l = &lwp0;
#ifndef LWP0_CPU_INFO
	l->l_cpu = curcpu();
#endif
	/*
	 * Attempt to find console and initialize
	 * in case of early panic or other messages.
	 */
	consinit();

	kernel_lock_init();
	once_init();
	mutex_init(&cpu_lock, MUTEX_DEFAULT, IPL_NONE);

	uvm_init();

	percpu_init();

	/* Initialize lock caches. */
	mutex_obj_init();

#if NKSYMS > 0
	ksyms_init_finalize();
#endif

	/* Initialize the extent manager. */
	extent_init();

	main_logger("cpu_startup()");
	/* Do machine-dependent initialization. */
	cpu_startup();

	main_logger("callout_startup()");
	/* Initialize callouts, part 1. */
	callout_startup();

	/*
	 * Initialize the kernel authorization subsystem and start the
	 * default security model, if any. We need to do this early
	 * enough so that subsystems relying on any of the aforementioned
	 * can work properly. Since the security model may dictate the
	 * credential inheritance policy, it is needed at least before
	 * any process is created, specifically proc0.
	 */
	kauth_init();
	secmodel_start();

	main_logger("bufinit()");
	/* Initialize the buffer cache */
	bufinit();

	/* Initialize sockets. */
	main_logger("soinit()");
	soinit();

	/*
	 * The following things must be done before autoconfiguration.
	 */
	main_logger("evcnt_init()");
	evcnt_init();		/* initialize event counters */
#if NRND > 0
	main_logger("rnd_init()");
	rnd_init();		/* initialize random number generator */
#endif

	/* Initialize process and pgrp structures. */
	main_logger("procinit()");
	procinit();
	main_logger("lwpinit()");
	lwpinit();

	/* Initialize signal-related data structures. */
	main_logger("signal_init()");
	signal_init();

	/* Initialize resource management. */
	main_logger("resource_init()");
	resource_init();

	/* Create process 0 (the swapper). */
	main_logger("proc0_init()");
	proc0_init();

	/* Initialize the UID hash table. */
	main_logger("uid_init()");
	uid_init();

	/* Charge root for one process. */
	(void)chgproccnt(0, 1);

	/* Initialize timekeeping. */
	main_logger("time_init()");
	time_init();

	/* Initialize the run queues, turnstiles and sleep queues. */
	main_logger("sched_rqinit()");
	sched_rqinit();
	turnstile_init();
	sleeptab_init(&sleeptab);

	/* Initialize processor-sets */
	main_logger("psets_init");
	psets_init();

	/* MI initialization of the boot cpu */
	main_logger("mi_cpu_attach");
	error = mi_cpu_attach(curcpu());
	KASSERT(error == 0);

	/* Initialize timekeeping, part 2. */
	main_logger("time_init2");
	time_init2();

	/*
	 * Initialize mbuf's.  Do this now because we might attempt to
	 * allocate mbufs or mbuf clusters during autoconfiguration.
	 */
	main_logger("mbinit");
	mbinit();

	/* Initialize the sysctl subsystem. */
	main_logger("sysctl_init");
	sysctl_init();

	/* Initialize I/O statistics. */
	main_logger("iostat_init");
	iostat_init();

	/* Initialize the log device. */
	main_logger("loginit");
	loginit();

	/* Start module system. */
	main_logger("module_init");
	module_init();

	/* Initialize the file systems. */
#ifdef NVNODE_IMPLICIT
	/*
	 * If maximum number of vnodes in namei vnode cache is not explicitly
	 * defined in kernel config, adjust the number such as we use roughly
	 * 10% of memory for vnodes and associated data structures in the
	 * assumed worst case.  Do not provide fewer than NVNODE vnodes.
	 */
	usevnodes =
	    calc_cache_size(kernel_map, 10, VNODE_VA_MAXPCT) / VNODE_COST;
	if (usevnodes > desiredvnodes)
		desiredvnodes = usevnodes;
#endif
	main_logger("vfs_init");
	vfsinit();
	main_logger("lf_init");
	lf_init();

	/* Initialize fstrans. */
	main_logger("fstans_init");
	fstrans_init();

	/* Initialize the file descriptor system. */
	main_logger("fd_sys_init");
	fd_sys_init();

	/* Initialize kqueue. */
	main_logger("kqueue_init");
	kqueue_init();

	/* Initialize asynchronous I/O. */
	main_logger("aio_init");
	aio_sysinit();

	/* Initialize message queues. */
	main_logger("mqueue_sysinit");
	mqueue_sysinit();

	/* Initialize the system monitor subsystems. */
#if NSYSMON_TASKQ > 0
	sysmon_task_queue_preinit();
#endif

#if NSYSMON_ENVSYS > 0
	sysmon_envsys_init();
#endif

#if NSYSMON_POWER > 0
	sysmon_power_init();
#endif

#if NSYSMON_WDOG > 0
	sysmon_wdog_init();
#endif

	main_logger("inittimecounter");
	inittimecounter();
	main_logger("ntp_init");
	ntp_init();

	/* Initialize the device switch tables. */
	main_logger("devsw_init");
	devsw_init();

	/* Initialize tty subsystem. */
	main_logger("tty_init");
	tty_init();
	main_logger("ttyldisc_init");
	ttyldisc_init();

	/* Initialize the buffer cache, part 2. */
	main_logger("bufinit");
	bufinit2();

	/* Initialize the disk wedge subsystem. */
	main_logger("dkwedge_init");
	dkwedge_init();

	/* Initialize interfaces. */
	main_logger("ifinit1");
	ifinit1();

	/* Configure the system hardware.  This will enable interrupts. */
	main_logger("configure");
	configure();

	main_logger("ssp_init");
	ssp_init();

	main_logger("configure2");
	configure2();

	main_logger("ubc_init");
	ubc_init();		/* must be after autoconfig */

#ifdef SYSVSHM
	/* Initialize System V style shared memory. */
	main_logger("shminit");
	shminit();
#endif

#ifdef SYSVSEM
	/* Initialize System V style semaphores. */
	main_logger("seminit");
	seminit();
#endif

#ifdef SYSVMSG
	/* Initialize System V style message queues. */
	main_logger("msginit");
	msginit();
#endif

#ifdef P1003_1B_SEMAPHORE
	/* Initialize posix semaphores */
	main_logger("ksem_init");
	ksem_init();
#endif

#if NVERIEXEC > 0
	/*
	 * Initialise the Veriexec subsystem.
	 */
	main_logger("veriexec_init");
	veriexec_init();
#endif /* NVERIEXEC > 0 */

#if defined(PAX_MPROTECT) || defined(PAX_SEGVGUARD) || defined(PAX_ASLR)
	pax_init();
#endif /* PAX_MPROTECT || PAX_SEGVGUARD || PAX_ASLR */

#ifdef	FAST_IPSEC
	/* Attach network crypto subsystem */
	ipsec_attach();
#endif

	/*
	 * Initialize protocols.  Block reception of incoming packets
	 * until everything is ready.
	 */
	main_logger("Initialize protocols: splnet()");
	s = splnet();
	main_logger("ifinit()");
	ifinit();
	main_logger("domaininit()");
	domaininit();
	main_logger("if_attachdomain()");
	if_attachdomain();
	splx(s);

#ifdef GPROF
	/* Initialize kernel profiling. */
	kmstartup();
#endif

	/* Initialize system accounting. */
	acct_init();

#ifndef PIPE_SOCKETPAIR
	/* Initialize pipes. */
	pipe_init();
#endif

#ifdef KTRACE
	/* Initialize ktrace. */
	ktrinit();
#endif

	/* Initialize the UUID system calls. */
	uuid_init();

#ifdef WAPBL
	/* Initialize write-ahead physical block logging. */
	wapbl_init();
#endif

	main_logger("create process 1");
	/*
	 * Create process 1 (init(8)).  We do this now, as Unix has
	 * historically had init be process 1, and changing this would
	 * probably upset a lot of people.
	 *
	 * Note that process 1 won't immediately exec init(8), but will
	 * wait for us to inform it that the root file system has been
	 * mounted.
	 */
	if (fork1(l, 0, SIGCHLD, NULL, 0, start_init, NULL, NULL, &initproc))
		panic("fork init");

	/*
	 * Load any remaining builtin modules, and hand back temporary
	 * storage to the VM system.
	 */
	module_init_class(MODULE_CLASS_ANY);

	/*
	 * Finalize configuration now that all real devices have been
	 * found.  This needs to be done before the root device is
	 * selected, since finalization may create the root device.
	 */
	config_finalize();

	/*
	 * Now that autoconfiguration has completed, we can determine
	 * the root and dump devices.
	 */
	main_logger("cpu_rootconf");
	cpu_rootconf();
	main_logger("cpu_dumpconf");
	cpu_dumpconf();

	/* Mount the root file system. */
	main_logger("Mount the root file system");
	do {
		domountroothook();
		main_logger("vfs_mountroot()");
		if ((error = vfs_mountroot())) {
			printf("cannot mount root, error = %d\n", error);
			boothowto |= RB_ASKNAME;
			setroot(root_device,
			    (rootdev != NODEV) ? DISKPART(rootdev) : 0);
		}
	} while (error != 0);
	main_logger("mountroothook_destroy");
	mountroothook_destroy();

	main_logger("inittodr");
	/*
	 * Initialise the time-of-day clock, passing the time recorded
	 * in the root filesystem (if any) for use by systems that
	 * don't have a non-volatile time-of-day device.
	 */
	inittodr(rootfstime);

	CIRCLEQ_FIRST(&mountlist)->mnt_flag |= MNT_ROOTFS;
	CIRCLEQ_FIRST(&mountlist)->mnt_op->vfs_refcount++;

	/*
	 * Get the vnode for '/'.  Set filedesc0.fd_fd.fd_cdir to
	 * reference it.
	 */
	main_logger("Get the vnode for /");
	error = VFS_ROOT(CIRCLEQ_FIRST(&mountlist), &rootvnode);
	if (error)
		panic("cannot find root vnode, error=%d", error);
	cwdi0.cwdi_cdir = rootvnode;
	VREF(cwdi0.cwdi_cdir);
	VOP_UNLOCK(rootvnode, 0);
	cwdi0.cwdi_rdir = NULL;

	/*
	 * Now that root is mounted, we can fixup initproc's CWD
	 * info.  All other processes are kthreads, which merely
	 * share proc0's CWD info.
	 */
	initproc->p_cwdi->cwdi_cdir = rootvnode;
	VREF(initproc->p_cwdi->cwdi_cdir);
	initproc->p_cwdi->cwdi_rdir = NULL;

	/*
	 * Now can look at time, having had a chance to verify the time
	 * from the file system.  Reset l->l_rtime as it may have been
	 * munched in mi_switch() after the time got set.
	 */
	main_logger("getmicrotime");
	getmicrotime(&time);
	boottime = time;
	mutex_enter(proc_lock);
	LIST_FOREACH(p, &allproc, p_list) {
		KASSERT((p->p_flag & PK_MARKER) == 0);
		mutex_enter(p->p_lock);
		p->p_stats->p_start = time;
		LIST_FOREACH(l, &p->p_lwps, l_sibling) {
			lwp_lock(l);
			memset(&l->l_rtime, 0, sizeof(l->l_rtime));
			lwp_unlock(l);
		}
		mutex_exit(p->p_lock);
	}
	mutex_exit(proc_lock);
	main_logger("binuptime");
	binuptime(&curlwp->l_stime);

	for (CPU_INFO_FOREACH(cii, ci)) {
		ci->ci_schedstate.spc_lastmod = time_second;
	}

	/* Create the pageout daemon kernel thread. */
	main_logger("uvm_swap_init");
	uvm_swap_init();
	if (kthread_create(PRI_PGDAEMON, KTHREAD_MPSAFE, NULL, uvm_pageout,
	    NULL, NULL, "pgdaemon"))
		panic("fork pagedaemon");

	/* Create the filesystem syncer kernel thread. */
	if (kthread_create(PRI_IOFLUSH, KTHREAD_MPSAFE, NULL, sched_sync,
	    NULL, NULL, "ioflush"))
		panic("fork syncer");

	/* Create the aiodone daemon kernel thread. */
	if (workqueue_create(&uvm.aiodone_queue, "aiodoned",
	    uvm_aiodone_worker, NULL, PRI_VM, IPL_NONE, WQ_MPSAFE))
		panic("fork aiodoned");

	main_logger("vmem_rehash_start");
	vmem_rehash_start();

	/* Initialize exec structures */
	main_logger("exec_init");
	exec_init(1);

	/*
	 * Okay, now we can let init(8) exec!  It's off to userland!
	 */
	main_logger("It's off to userland");
	mutex_enter(proc_lock);
	start_init_exec = 1;
	main_logger("cv_broadcast");
	cv_broadcast(&lbolt);
	mutex_exit(proc_lock);

	/* The scheduler is an infinite loop. */
	main_logger("uvm_scheduler");
	uvm_scheduler();
	/* NOTREACHED */
}

static void
check_console(struct lwp *l)
{
	struct nameidata nd;
	int error;

	NDINIT(&nd, LOOKUP, FOLLOW, UIO_SYSSPACE, "/dev/console");
	error = namei(&nd);
	if (error == 0)
		vrele(nd.ni_vp);
	else if (error == ENOENT)
		printf("warning: no /dev/console\n");
	else
		printf("warning: lookup /dev/console: error %d\n", error);
}

/*
 * List of paths to try when searching for "init".
 */
static const char * const initpaths[] = {
	"/sbin/init",
	"/sbin/oinit",
	"/sbin/init.bak",
	NULL,
};

/*
 * Start the initial user process; try exec'ing each pathname in "initpaths".
 * The program is invoked with one argument containing the boot flags.
 */
static void
start_init(void *arg)
{
	struct lwp *l = arg;
	struct proc *p = l->l_proc;
	vaddr_t addr;
	struct sys_execve_args /* {
		syscallarg(const char *) path;
		syscallarg(char * const *) argp;
		syscallarg(char * const *) envp;
	} */ args;
	int options, i, error;
	register_t retval[2];
	char flags[4], *flagsp;
	const char *path, *slash;
	char *ucp, **uap, *arg0, *arg1 = NULL;
	char ipath[129];
	int ipx, len;

	/*
	 * Now in process 1.
	 */
	strncpy(p->p_comm, "init", MAXCOMLEN);

	/*
	 * Wait for main() to tell us that it's safe to exec.
	 */
	mutex_enter(proc_lock);
	while (start_init_exec == 0)
		cv_wait(&lbolt, proc_lock);
	mutex_exit(proc_lock);

	/*
	 * This is not the right way to do this.  We really should
	 * hand-craft a descriptor onto /dev/console to hand to init,
	 * but that's a _lot_ more work, and the benefit from this easy
	 * hack makes up for the "good is the enemy of the best" effect.
	 */
	check_console(l);

	/*
	 * Need just enough stack to hold the faked-up "execve()" arguments.
	 */
	addr = (vaddr_t)STACK_ALLOC(USRSTACK, PAGE_SIZE);
	if (uvm_map(&p->p_vmspace->vm_map, &addr, PAGE_SIZE,
                    NULL, UVM_UNKNOWN_OFFSET, 0,
                    UVM_MAPFLAG(UVM_PROT_ALL, UVM_PROT_ALL, UVM_INH_COPY,
		    UVM_ADV_NORMAL,
                    UVM_FLAG_FIXED|UVM_FLAG_OVERLAY|UVM_FLAG_COPYONW)) != 0)
		panic("init: couldn't allocate argument space");
	p->p_vmspace->vm_maxsaddr = (void *)STACK_MAX(addr, PAGE_SIZE);

	ipx = 0;
	while (1) {
		if (boothowto & RB_ASKNAME) {
			printf("init path");
			if (initpaths[ipx])
				printf(" (default %s)", initpaths[ipx]);
			printf(": ");
			len = cngetsn(ipath, sizeof(ipath)-1);
			if (len == 4 && strcmp(ipath, "halt") == 0) {
				cpu_reboot(RB_HALT, NULL);
			} else if (len == 6 && strcmp(ipath, "reboot") == 0) {
				cpu_reboot(0, NULL);
#if defined(DDB)
			} else if (len == 3 && strcmp(ipath, "ddb") == 0) {
				console_debugger();
				continue;
#endif
			} else if (len > 0 && ipath[0] == '/') {
				ipath[len] = '\0';
				path = ipath;
			} else if (len == 0 && initpaths[ipx] != NULL) {
				path = initpaths[ipx++];
			} else {
				printf("use absolute path, ");
#if defined(DDB)
				printf("\"ddb\", ");
#endif
				printf("\"halt\", or \"reboot\"\n");
				continue;
			}
		} else {
			if ((path = initpaths[ipx++]) == NULL) {
				ipx = 0;
				boothowto |= RB_ASKNAME;
				continue;
			}
		}

		ucp = (char *)USRSTACK;

		/*
		 * Construct the boot flag argument.
		 */
		flagsp = flags;
		*flagsp++ = '-';
		options = 0;

		if (boothowto & RB_SINGLE) {
			*flagsp++ = 's';
			options = 1;
		}
#ifdef notyet
		if (boothowto & RB_FASTBOOT) {
			*flagsp++ = 'f';
			options = 1;
		}
#endif

		/*
		 * Move out the flags (arg 1), if necessary.
		 */
		if (options != 0) {
			*flagsp++ = '\0';
			i = flagsp - flags;
#ifdef DEBUG
			aprint_normal("init: copying out flags `%s' %d\n", flags, i);
#endif
			arg1 = STACK_ALLOC(ucp, i);
			ucp = STACK_MAX(arg1, i);
			(void)copyout((void *)flags, arg1, i);
		}

		/*
		 * Move out the file name (also arg 0).
		 */
		i = strlen(path) + 1;
#ifdef DEBUG
		aprint_normal("init: copying out path `%s' %d\n", path, i);
#else
		if (boothowto & RB_ASKNAME || path != initpaths[0])
			printf("init: trying %s\n", path);
#endif
		arg0 = STACK_ALLOC(ucp, i);
		printf("[XXXAVR32]%s %s %d arg0 %x\n", __FILE__, __FUNCTION__, __LINE__, arg0);
		ucp = STACK_MAX(arg0, i);
		(void)copyout(path, arg0, i);

		main_logger("try to exec the user program");
		/*
		 * Move out the arg pointers.
		 */
		ucp = (void *)STACK_ALIGN(ucp, ALIGNBYTES);
		uap = (char **)STACK_ALLOC(ucp, sizeof(char *) * 3);
		SCARG(&args, path) = arg0;
		SCARG(&args, argp) = uap;
		SCARG(&args, envp) = NULL;
		slash = strrchr(path, '/');
		main_logger("try to exec the user program");
		if (slash) {
			main_logger("try to exec the user program");
			printf("slash %s \n",slash);
			printf("path %s \n",path);
			printf("&arg0 %x, arg0: %x, uap %x \n",&arg0, arg0, uap);
			
			(void)suword((void *)uap++,
			    (long)arg0 + (slash + 1 - path));
		}
		else
			(void)suword((void *)uap++, (long)arg0);
		main_logger("try to exec the user program");
		if (options != 0)
			(void)suword((void *)uap++, (long)arg1);
		(void)suword((void *)uap++, 0);	/* terminator */

		/*
		 * Now try to exec the program.  If can't for any reason
		 * other than it doesn't exist, complain.
		 */
		error = sys_execve(l, &args, retval);
		if (error == 0 || error == EJUSTRETURN) {
			KERNEL_UNLOCK_LAST(l);
			return;
		}
		printf("exec %s: error %d\n", path, error);
	}
	printf("init: not found\n");
	panic("no init");
}

/*
 * calculate cache size from physmem and vm_map size.
 */
vaddr_t
calc_cache_size(struct vm_map *map, int pct, int va_pct)
{
	paddr_t t;

	/* XXX should consider competing cache if any */
	/* XXX should consider submaps */
	t = (uintmax_t)physmem * pct / 100 * PAGE_SIZE;
	if (map != NULL) {
		vsize_t vsize;

		vsize = vm_map_max(map) - vm_map_min(map);
		vsize = (uintmax_t)vsize * va_pct / 100;
		if (t > vsize) {
			t = vsize;
		}
	}
	return t;
}
