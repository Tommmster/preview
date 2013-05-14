/*	$NetBSD: mach_fasttraps_thread.c,v 1.12 2008/04/28 20:23:45 martin Exp $ */

/*-
 * Copyright (c) 2002 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Emmanuel Dreyfus.
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

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD: mach_fasttraps_thread.c,v 1.12 2008/04/28 20:23:45 martin Exp $");

#include <sys/types.h>
#include <sys/systm.h>
#include <sys/param.h>
#include <sys/signal.h>
#include <sys/proc.h>
#include <sys/exec.h>

#include <compat/mach/mach_types.h>
#include <compat/mach/mach_exec.h>

#include <compat/mach/arch/powerpc/fasttraps/mach_fasttraps_syscall.h>
#include <compat/mach/arch/powerpc/fasttraps/mach_fasttraps_syscallargs.h>

int
mach_sys_cthread_set_self(struct lwp *l, const struct mach_sys_cthread_set_self_args *uap, register_t *retval)
{
	/* {
		syscallarg(mach_cproc_t) p;
	} */
	struct mach_emuldata *med;

	l->l_private = (void *)SCARG(uap, p);

	med = l->l_proc->p_emuldata;
	med->med_dirty_thid = 0;

	return 0;
}

int
mach_sys_cthread_self(struct lwp *l, const void *v, register_t *retval)
{
	struct mach_emuldata *med;

	/*
	 * After a fork or exec, l_private is not initialized.
	 * We have no way of setting it before, so we keep track
	 * of it being uninitialized with med_dirty_thid.
	 * XXX This is probably not the most efficient way
	 */
	med = l->l_proc->p_emuldata;
	if (med->med_dirty_thid != 0) {
		l->l_private = NULL;
		med->med_dirty_thid = 0;
	}

	*retval = (register_t)l->l_private;
	return 0;
}