/*
 *  Copyright (C) Dushara Jayasinghe
 *  Copyright (C) 2004 - 2008 
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

/*
 * header files for SunIM library
 */
#include "imcompat.h"
#include "scim_wijesekera_imengine_factory.h"
#include "scim_wijesekera_imengine.h"

void build_unicode_char(unsigned char lsb, unsigned char *u)
{
	if (lsb >= 128) {
		u[0] = 0xe0;
		if (lsb < 192) {
			u[1] = 0xb6;
			u[2] = lsb;
		} else {
			u[1] = 0xb7;
			u[2] = (lsb & 0x3f) | 0x80;
		}
		u[3] = 0;
	} else if ((lsb == 0x0c) || (lsb == 0x0d)) {
		u[0] = 0xe2;
		u[1] = 0x80;
		u[2] = 0x80 | lsb;
		u[3] = 0;
	} else {
		u[0] = 0;
	}
}

static void build_out_buf(compat_data_t *cd, const u_int16_t *buf, int len)
{
	wchar_t *dst = cd->buf;
	
	while(len--)
		*dst++ = *buf++;
	
	*dst = 0;
}

void commit_utf16(void *context, const u_int16_t *buf, int len)
{
	compat_data_t *cd = &((parser_data_t *)context)->compat;
	build_out_buf(cd, buf, len);
	
	cd->inst_base->commit_string(cd->buf);
}

void write_status(void *context, const u_int16_t *buf, int len)
{
	compat_data_t *cd = &((parser_data_t *)context)->compat;
	build_out_buf(cd, buf, len);
	
	cd->inst_base->update_aux_string (cd->buf);
	cd->inst_base->show_aux_string ();
}

void close_status(void *context)
{
	((parser_data_t *)context)->compat.inst_base->hide_aux_string ();
}

void write_preedit(void *context, const u_int16_t *buf, int len)
{
	compat_data_t *cd = &((parser_data_t *)context)->compat;
	
	if(cd->cap & SCIM_CLIENT_CAP_ONTHESPOT_PREEDIT) {
		build_out_buf(cd, buf, len);
		
		cd->inst_base->update_preedit_string (cd->buf);
		cd->inst_base->show_preedit_string ();
	} else {
		write_status(context, buf, len);
	}
}

void close_preedit(void *context)
{
	compat_data_t *cd = &((parser_data_t *)context)->compat;
	
	if(cd->cap & SCIM_CLIENT_CAP_ONTHESPOT_PREEDIT) {
		cd->inst_base->hide_preedit_string ();
	} else {
		close_status(context);
	}
}

void commit_clearing_preedit(void *context, const u_int16_t *buf, int len)
{
	close_preedit(context);
	commit_utf16(context, buf, len);
}

parser_data_t *get_parser_data(void *context)
{
	return ((parser_data_t *)context);
}
