/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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

#ifndef PARSER_H
#define PARSER_H

#include "compat_data.h"

#define PRS_STATE(name) ePrs##name,

typedef enum {
#include "states.h"
    ePrsCount
} parser_state_t;

typedef struct {
    parser_state_t state;
    u_int16_t preedit[16];
    int pe_count;
    u_int32_t flags;
    int status_on;
    compat_data_t   compat;     // compatibility layer specific data
} parser_data_t;

int parse_key(int keyCode, int modifier, int AltGr, void *context);

#endif
