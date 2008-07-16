/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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

#ifndef COMPAT_DATA_H
#define COMPAT_DATA_H

#define Uses_SCIM_UTILITY
#define Uses_SCIM_IMENGINE
#define Uses_SCIM_LOOKUP_TABLE
#define Uses_SCIM_CONFIG_BASE

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

class WijesekeraInstance;

// session data specific to abstraction layer (SCIM)
typedef struct {
	WijesekeraInstance *inst_base;
	int alt_gr;		// state of simulated AltGr
	unsigned int cap;	// client capabilities
	wchar_t buf[32];
} compat_data_t;

#endif
