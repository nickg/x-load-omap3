/*
 * (C) Copyright 2004-2009 Texas Insturments
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002
 * Gary Jennejohn, DENX Software Engineering, <gj@denx.de>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * CPU specific code
 */

#include <common.h>
#include <asm/io.h>

/* See also ARM Ref. Man. */
#define C1_MMU		(1<<0)		/* mmu off/on */
#define C1_ALIGN	(1<<1)		/* alignment faults off/on */
#define C1_DC		(1<<2)		/* dcache off/on */
#define C1_WB		(1<<3)		/* merging write buffer on/off */
#define C1_BIG_ENDIAN	(1<<7)		/* big endian off/on */
#define C1_SYS_PROT	(1<<8)		/* system protection */
#define C1_ROM_PROT	(1<<9)		/* ROM protection */
#define C1_IC		(1<<12)		/* icache off/on */
#define C1_HIGH_VECTORS	(1<<13) /* location of vectors: low/high addresses */
#define RESERVED_1	(0xf << 3)	/* must be 111b for R/W */

int cpu_init (void)
{
	return 0;
}

unsigned int cortex_a9_rev(void)
{

	unsigned int i;

	/* turn off I/D-cache */
	asm ("mrc p15, 0, %0, c0, c0, 0" : "=r" (i));

	return i;
}

unsigned int omap_revision(void)
{
	unsigned int rev = cortex_a9_rev();

	switch(rev) {
	case 0x410FC091:
		return OMAP4430_ES1_0;
	case 0x411FC092:
		if (__raw_readl(0x4a002204) == 0x3b95c02f)
			return OMAP4430_ES2_1;
		else
			return OMAP4430_ES2_0;
	default:
		return OMAP4430_SILICON_ID_INVALID;
	}
}
