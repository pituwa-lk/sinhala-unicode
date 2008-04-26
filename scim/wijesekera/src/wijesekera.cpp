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
#include "imcompat.h"
#include "layout.h"

static const keypair_t plain[] = 
{
	{SI_KEYCODE_BACKQUOTE,       (COMPOUND_MASK  | eCmplx_rak)},
	{SI_KEYCODE_Q,               SCH_PAA},
	{SI_KEYCODE_W,               SCH_AYANNA},
	{SI_KEYCODE_E,               SCH_AEDA},
	{SI_KEYCODE_R,               SCH_RAYANNA},
	{SI_KEYCODE_T,               SCH_EYANNA},
	{SI_KEYCODE_Y,               SCH_HAYANNA},
	{SI_KEYCODE_U,               SCH_MAYANNA},
	{SI_KEYCODE_I,               SCH_SAYANNA},
	{SI_KEYCODE_O,               SCH_DAYANNA},
	{SI_KEYCODE_P,               SCH_CAYANNA},
	{SI_KEYCODE_OPEN_BRACKET,    SCH_NYAYANNA},
	
	{SI_KEYCODE_A,               SCH_AL},
	{SI_KEYCODE_S,               SCH_IS},
	{SI_KEYCODE_D,               SCH_AELA},
	{SI_KEYCODE_F,               SCH_KOMBUWA},
	{SI_KEYCODE_G,               SCH_TTAYANNA},
	{SI_KEYCODE_H,               SCH_YAYANNA},
	{SI_KEYCODE_J,               SCH_VAYANNA},
	{SI_KEYCODE_K,               SCH_NAYANNA},
	{SI_KEYCODE_L,               SCH_KAYANNA},
	{SI_KEYCODE_SEMICOLON,       SCH_TAYANNA},
	
	{SI_KEYCODE_X,               SCH_ANUSWARA},
	{SI_KEYCODE_C,               SCH_JAYANNA},
	{SI_KEYCODE_V,               SCH_DDAYANNA},
	{SI_KEYCODE_B,               SCH_IYANNA},
	{SI_KEYCODE_N,               SCH_BAYANNA},
	{SI_KEYCODE_M,               SCH_PAYANNA},
	{SI_KEYCODE_COMMA,           SCH_LAYANNA},
	{SI_KEYCODE_PERIOD,          SCH_GAYANNA},
	{SI_KEYCODE_BACKSLASH,       (COMPOUND_MASK  | eCmplx_baendi)},
};

static const keypair_t shift[] = 
{
	{SI_KEYCODE_SH_BACKQUOTE,       (COMPOUND_MASK  | eCmplx_rep)},
	{SI_KEYCODE_SH_Q,               SCH_DPAA},
	{SI_KEYCODE_SH_W,               SCH_UYANNA},
	{SI_KEYCODE_SH_E,               SCH_DAEDA},
	{SI_KEYCODE_SH_R,               SCH_IRUYANNA},
	{SI_KEYCODE_SH_T,               SCH_OYANNA},
	{SI_KEYCODE_SH_Y,               SCH_SHAYANNA},
	{SI_KEYCODE_SH_U,               SCH_MBAYANNA},
	{SI_KEYCODE_SH_I,               SCH__SAYANNA},
	{SI_KEYCODE_SH_O,               SCH__DAYANNA},
	{SI_KEYCODE_SH_P,               SCH__CAYANNA},
	{SI_KEYCODE_SH_OPEN_BRACKET,    SCH_GNYAYANNA},
	
	{SI_KEYCODE_SH_A,               SCH_GAYANU},
	{SI_KEYCODE_SH_S,               SCH_DIS},
	{SI_KEYCODE_SH_D,               SCH_GAETA},
	{SI_KEYCODE_SH_F,               SCH_FAYANNA},
	{SI_KEYCODE_SH_G,               SCH__TTAYANNA},
	{SI_KEYCODE_SH_H,               (COMPOUND_MASK  | eCmplx_yans)},
	{SI_KEYCODE_SH_J,               (COMPOUND_MASK  | eCmplx_mlu)},
	{SI_KEYCODE_SH_K,               SCH__NAYANNA},
	{SI_KEYCODE_SH_L,               SCH__KAYANNA},
	{SI_KEYCODE_SH_SEMICOLON,       SCH__TAYANNA},
	
	{SI_KEYCODE_SH_X,               SCH_NAASIKAYA},
	{SI_KEYCODE_SH_C,               SCH__JAYANNA},
	{SI_KEYCODE_SH_V,               SCH__DDAYANNA},
	{SI_KEYCODE_SH_B,               SCH_IIYANNA},
	{SI_KEYCODE_SH_N,               SCH__BAYANNA},
	{SI_KEYCODE_SH_M,               SCH__PAYANNA},
	{SI_KEYCODE_SH_COMMA,           SCH__LAYANNA},
	{SI_KEYCODE_SH_PERIOD,          SCH__GAYANNA},
	{SI_KEYCODE_SH_BACKSLASH,       (COMPOUND_MASK  | eCmplx_touch)},
};

static const keypair_t altgr[] = 
{
	{SI_KEYCODE_O,               SCH_NDAYANNA},
	{SI_KEYCODE_A,               SCH_DGAYANU},
	{SI_KEYCODE_QUOTE,           SCH_PUNCT},
	{SI_KEYCODE_X,               SCH_VISARGA},
	{SI_KEYCODE_C,               SCH_NJAYANNA},
	{SI_KEYCODE_V,               SCH_NDDAYANNA},
	{SI_KEYCODE_COMMA,           SCH_ILUYANNA},
	{SI_KEYCODE_PERIOD,          SCH_NGAYANNA},
};

static const keypair_t replace[] = 
{
	{SI_KEYCODE_CLOSE_BRACKET,   ';'},
	{SI_KEYCODE_Z,               '\''},
	{SI_KEYCODE_QUOTE,           '.'},
};

static const keypair_t shreplace[] = 
{
	{SI_KEYCODE_SH_CLOSE_BRACKET,   ':'},
	{SI_KEYCODE_SH_Z,               '\"'},
	{SI_KEYCODE_SH_QUOTE,           ','},
	{SI_KEYCODE_SH_SPACE,		0x00a0},
};

const layout_t wijesekera = {
	sizeof(plain)/sizeof(plain[0]),
	sizeof(shift)/sizeof(shift[0]),
	sizeof(altgr)/sizeof(altgr[0]),
	sizeof(replace)/sizeof(replace[0]),
	sizeof(shreplace)/sizeof(shreplace[0]),
	
	plain,
	shift,
	altgr,
	replace,
	shreplace,
};

