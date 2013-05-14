/*-                                                                                                                                                                                   
 * Copyright (c) 2008 The NetBSD Foundation, Inc.
 * All rights reserved.
 * 
 * This code is derived from software contributed to The NetBSD Foundation
 * by 
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
#include <sys/types.h>
#include <sys/systm.h>
#include <sys/time.h>
#include <sys/timetc.h>
#include <sys/cpu.h>

#include <avr32/avr32_clock.h>
#include <avr32/sysconf.h>
#include <avr32/locore.h>

void avr32_clockintr(struct clockframe *cf);

u_int32_t next_clock_intr;

/* 
 * platform_clock_attach:
 *
 *      Register hardware-dependent clock routine to system.
 */
void
platform_clock_attach(void *ctx, struct platform_clock *clock)
{
	clock->self = ctx;
	platform.clock = clock;
}

void
cpu_initclocks()
{
	//Disable interrupts setting the compare register to its highest value.
	avr32_compare_write(~0u);
	avr32_count_write(0u);

	avr32_tc_init();

	_splnone();
}


void
avr32_clockintr(struct clockframe *cf)
{
	u_int32_t new_cnt;

	next_clock_intr += curcpu()->ci_cycles_per_hz;

	avr32_compare_write(next_clock_intr);

	/* Check for lost interrupts */
	new_cnt = avr32_count_read();

	/*
	 * Missed one or more clock interrupts, so lets
	 * start counting again from the current value.
	 */
	if ((next_clock_intr - new_cnt) & 0x80000000) {

		next_clock_intr = new_cnt + curcpu()->ci_cycles_per_hz;
		avr32_compare_write(next_clock_intr);

	}

	hardclock(cf);

	/* caller should re-enable interrupts */
}

void
setstatclockrate(int newhz)
{
	panic("setstatclockrate");	
}

void
avr32_tc_init(void)
{
	static struct timecounter tc = {
		.tc_get_timecount = (timecounter_get_t *)avr32_count_read,
		.tc_poll_pps = 0,
		.tc_counter_mask = ~0u, 
		.tc_frequency = 0,
		.tc_name = "name",
		.tc_quality = 100,
	};

	tc.tc_frequency = curcpu()->ci_cpu_freq;
	tc_init (&tc);
}
