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

#ifndef IM_COMPAT_H
#define IM_COMPAT_H

#define Uses_SCIM_UTILITY
#define Uses_SCIM_IMENGINE
#define Uses_SCIM_LOOKUP_TABLE
#define Uses_SCIM_CONFIG_BASE

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <scim.h>
using namespace scim;
#include "parser.h"

/* Keycodes */
#define SI_KEYCODE_SEMICOLON        SCIM_KEY_semicolon
#define SI_KEYCODE_EQUALS           SCIM_KEY_equals
#define SI_KEYCODE_A                SCIM_KEY_a
#define SI_KEYCODE_B                SCIM_KEY_b
#define SI_KEYCODE_C                SCIM_KEY_c
#define SI_KEYCODE_D                SCIM_KEY_d
#define SI_KEYCODE_E                SCIM_KEY_e
#define SI_KEYCODE_F                SCIM_KEY_f
#define SI_KEYCODE_G                SCIM_KEY_g
#define SI_KEYCODE_H                SCIM_KEY_h
#define SI_KEYCODE_I                SCIM_KEY_i
#define SI_KEYCODE_J                SCIM_KEY_j
#define SI_KEYCODE_K                SCIM_KEY_k
#define SI_KEYCODE_L                SCIM_KEY_l
#define SI_KEYCODE_M                SCIM_KEY_m
#define SI_KEYCODE_N                SCIM_KEY_n
#define SI_KEYCODE_O                SCIM_KEY_o
#define SI_KEYCODE_P                SCIM_KEY_p
#define SI_KEYCODE_Q                SCIM_KEY_q
#define SI_KEYCODE_R                SCIM_KEY_r
#define SI_KEYCODE_S                SCIM_KEY_s
#define SI_KEYCODE_T                SCIM_KEY_t
#define SI_KEYCODE_U                SCIM_KEY_u
#define SI_KEYCODE_V                SCIM_KEY_v
#define SI_KEYCODE_W                SCIM_KEY_w
#define SI_KEYCODE_X                SCIM_KEY_x
#define SI_KEYCODE_Y                SCIM_KEY_y
#define SI_KEYCODE_Z                SCIM_KEY_z
#define SI_KEYCODE_OPEN_BRACKET     SCIM_KEY_bracketleft
#define SI_KEYCODE_CLOSE_BRACKET    SCIM_KEY_bracketright
#define SI_KEYCODE_QUOTE            SCIM_KEY_apostrophe
#define SI_KEYCODE_BACKQUOTE        SCIM_KEY_grave
#define SI_KEYCODE_COMMA            SCIM_KEY_comma
#define SI_KEYCODE_PERIOD           SCIM_KEY_period
#define SI_KEYCODE_BACKSLASH        SCIM_KEY_backslash

#define SI_KEYCODE_SH_SEMICOLON		SCIM_KEY_colon
#define SI_KEYCODE_SH_EQUALS		SCIM_KEY_plus
#define SI_KEYCODE_SH_A                SCIM_KEY_A
#define SI_KEYCODE_SH_B                SCIM_KEY_B
#define SI_KEYCODE_SH_C                SCIM_KEY_C
#define SI_KEYCODE_SH_D                SCIM_KEY_D
#define SI_KEYCODE_SH_E                SCIM_KEY_E
#define SI_KEYCODE_SH_F                SCIM_KEY_F
#define SI_KEYCODE_SH_G                SCIM_KEY_G
#define SI_KEYCODE_SH_H                SCIM_KEY_H
#define SI_KEYCODE_SH_I                SCIM_KEY_I
#define SI_KEYCODE_SH_J                SCIM_KEY_J
#define SI_KEYCODE_SH_K                SCIM_KEY_K
#define SI_KEYCODE_SH_L                SCIM_KEY_L
#define SI_KEYCODE_SH_M                SCIM_KEY_M
#define SI_KEYCODE_SH_N                SCIM_KEY_N
#define SI_KEYCODE_SH_O                SCIM_KEY_O
#define SI_KEYCODE_SH_P                SCIM_KEY_P
#define SI_KEYCODE_SH_Q                SCIM_KEY_Q
#define SI_KEYCODE_SH_R                SCIM_KEY_R
#define SI_KEYCODE_SH_S                SCIM_KEY_S
#define SI_KEYCODE_SH_T                SCIM_KEY_T
#define SI_KEYCODE_SH_U                SCIM_KEY_U
#define SI_KEYCODE_SH_V                SCIM_KEY_V
#define SI_KEYCODE_SH_W                SCIM_KEY_W
#define SI_KEYCODE_SH_X                SCIM_KEY_X
#define SI_KEYCODE_SH_Y                SCIM_KEY_Y
#define SI_KEYCODE_SH_Z                SCIM_KEY_Z
#define SI_KEYCODE_SH_OPEN_BRACKET     SCIM_KEY_braceleft
#define SI_KEYCODE_SH_CLOSE_BRACKET    SCIM_KEY_braceright
#define SI_KEYCODE_SH_QUOTE            SCIM_KEY_quotedbl
#define SI_KEYCODE_SH_BACKQUOTE        SCIM_KEY_asciitilde
#define SI_KEYCODE_SH_COMMA            SCIM_KEY_less
#define SI_KEYCODE_SH_PERIOD           SCIM_KEY_greater
#define SI_KEYCODE_SH_BACKSLASH        SCIM_KEY_bar
#define SI_KEYCODE_SH_SPACE		SCIM_KEY_space

#define SI_KEYCODE_SHIFT            SCIM_KEY_Shift_L
#define SI_KEYCODE_ALT              SCIM_KEY_Alt_L
#define SI_KEYCODE_CONTROL          SCIM_KEY_Control_L

#define SI_SHIFT_MASK               SCIM_KEY_ShiftMask
#define SI_ALTGR_MASK               ( SCIM_KEY_AltMask | SCIM_KEY_ControlMask )
#define SI_MOD_KEEP_MASK		( SCIM_KEY_ShiftMask | SCIM_KEY_CapsLockMask | \
					 SCIM_KEY_ControlMask | SCIM_KEY_AltMask | SCIM_KEY_MetaMask | \
					 SCIM_KEY_SuperMask | SCIM_KEY_HyperMask )

parser_data_t *get_parser_data (void *context);
void commit_utf16 (void *context, const u_int16_t * buf, int len);
void write_status (void *context, const u_int16_t * buf, int len);
void close_status (void *context);
void write_preedit (void *context, const u_int16_t * buf, int len);
void close_preedit (void *context);
void commit_clearing_preedit (void *context, const u_int16_t * buf, int len);

#endif
