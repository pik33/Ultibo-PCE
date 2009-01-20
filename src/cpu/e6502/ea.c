/*****************************************************************************
 * pce                                                                       *
 *****************************************************************************/

/*****************************************************************************
 * File name:   src/cpu/e6502/ea.c                                           *
 * Created:     2004-05-25 by Hampa Hug <hampa@hampa.ch>                     *
 * Copyright:   (C) 2004-2009 Hampa Hug <hampa@hampa.ch>                     *
 *****************************************************************************/

/*****************************************************************************
 * This program is free software. You can redistribute it and / or modify it *
 * under the terms of the GNU General Public License version 2 as  published *
 * by the Free Software Foundation.                                          *
 *                                                                           *
 * This program is distributed in the hope  that  it  will  be  useful,  but *
 * WITHOUT  ANY   WARRANTY,   without   even   the   implied   warranty   of *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU  General *
 * Public License for more details.                                          *
 *****************************************************************************/


#include "e6502.h"
#include "internal.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


unsigned char e6502_get_imm (e6502_t *c)
{
	e6502_get_inst1 (c);

	c->ea_page = 0;

	return (c->inst[1]);
}

unsigned short e6502_get_ea_idx_ind_x (e6502_t *c)
{
	e6502_get_inst1 (c);

	c->ea = (e6502_get_x (c) + e6502_get_mem8 (c, c->inst[1])) & 0xff;
	c->ea_page = 0;

	return (c->ea);
}

unsigned short e6502_get_ea_zpg (e6502_t *c)
{
	e6502_get_inst1 (c);

	c->ea = c->inst[1];
	c->ea_page = 0;

	return (c->ea);
}

unsigned short e6502_get_ea_abs (e6502_t *c)
{
	e6502_get_inst2 (c);

	c->ea = ((unsigned short) c->inst[2] << 8) + c->inst[1];
	c->ea_page = 0;

	return (c->ea);
}

unsigned short e6502_get_ea_ind_idx_y (e6502_t *c)
{
	unsigned short tmp;

	e6502_get_inst1 (c);

	tmp = e6502_get_mem16 (c, c->inst[1]);
	c->ea = (tmp + e6502_get_y (c)) & 0xffffU;

	if ((tmp ^ c->ea) & 0xff00U) {
		c->ea_page = 1;
	}
	else {
		c->ea_page = 0;
	}

	return (c->ea);
}

unsigned short e6502_get_ea_zpg_x (e6502_t *c)
{
	e6502_get_inst1 (c);

	c->ea = (c->inst[1] + e6502_get_x (c)) & 0xff;

	return (c->ea);
}

unsigned short e6502_get_ea_zpg_y (e6502_t *c)
{
	e6502_get_inst1 (c);

	c->ea = (c->inst[1] + e6502_get_y (c)) & 0xff;

	return (c->ea);
}

unsigned short e6502_get_ea_abs_y (e6502_t *c)
{
	unsigned short tmp;

	e6502_get_inst2 (c);

	tmp = e6502_mk_uint16 (c->inst[1], c->inst[2]);
	c->ea = (tmp + e6502_get_y (c)) & 0xffffU;

	if ((tmp ^ c->ea) & 0xff00U) {
		c->ea_page = 1;
	}
	else {
		c->ea_page = 0;
	}

	return (c->ea);
}

unsigned short e6502_get_ea_abs_x (e6502_t *c)
{
	unsigned short tmp;

	e6502_get_inst2 (c);

	tmp = e6502_mk_uint16 (c->inst[1], c->inst[2]);
	c->ea = (tmp + e6502_get_x (c)) & 0xffffU;

	if ((tmp ^ c->ea) & 0xff00U) {
		c->ea_page = 1;
	}
	else {
		c->ea_page = 0;
	}

	return (c->ea);
}
