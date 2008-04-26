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

#ifndef LAYOUT_H
#define LAYOUT_H

#define COMPOUND_MASK           0x100
#define SINHALA_PAGE            0x0d00
#define SINHALA_MASK            0x80

// simple characters
#define SCH_ANUSWARA	0x82
#define SCH_VISARGA	0x83
#define SCH_AYANNA      0x85
#define SCH_AAYANNA	0x86
#define SCH_AEYANNA	0x87
#define SCH_AEEYANNA	0x88
#define SCH_IYANNA		0x89
#define SCH_IIYANNA		0x8a
#define SCH_UYANNA		0x8b
#define SCH_UUYANNA		0x8c
#define SCH_IRUYANNA	0x8d
#define SCH_IRUUYANNA	0x8e
#define SCH_ILUYANNA	0x8f
#define SCH_ILUUYANNA	0x90
#define SCH_EYANNA		0x91
#define SCH_EEYANNA		0x92
#define SCH_AIYANNA		0x93
#define SCH_OYANNA		0x94
#define SCH_OOYANNA		0x95
#define SCH_AUYANNA		0x96
#define SCH_KAYANNA		0x9A
#define SCH__KAYANNA	0x9B
#define SCH_GAYANNA		0x9C
#define SCH__GAYANNA	0x9D
#define SCH_NAASIKAYA	0x9E
#define SCH_NGAYANNA	0x9F
#define SCH_CAYANNA     0xA0
#define SCH__CAYANNA	0xA1
#define SCH_JAYANNA		0xA2
#define SCH__JAYANNA	0xA3
#define SCH_NYAYANNA	0xA4
#define SCH_GNYAYANNA	0xA5
#define SCH_NJAYANNA	0xA6
#define SCH_TTAYANNA	0xA7
#define SCH__TTAYANNA	0xA8
#define SCH_DDAYANNA	0xA9
#define SCH__DDAYANNA	0xAA
#define SCH__NAYANNA	0xAB
#define SCH_NDDAYANNA	0xAC
#define SCH_TAYANNA		0xAD
#define SCH__TAYANNA	0xAE
#define SCH_DAYANNA     0xAF
#define SCH__DAYANNA	0xB0
#define SCH_NAYANNA		0xB1
#define SCH_NDAYANNA	0xB3
#define SCH_PAYANNA		0xB4
#define SCH__PAYANNA	0xB5
#define SCH_BAYANNA		0xB6
#define SCH__BAYANNA	0xB7
#define SCH_MAYANNA		0xB8
#define SCH_MBAYANNA	0xB9
#define SCH_YAYANNA		0xBA
#define SCH_RAYANNA		0xBB
#define SCH_LAYANNA		0xBD
#define SCH_VAYANNA		0xC0
#define SCH_SHAYANNA	0xC1
#define SCH__SAYANNA	0xC2
#define SCH_SAYANNA		0xC3
#define SCH_HAYANNA		0xC4
#define SCH__LAYANNA	0xC5
#define SCH_FAYANNA		0xC6
#define SCH_AL			0xCA
#define SCH_AELA		0xCF
#define SCH_AEDA		0xD0
#define SCH_DAEDA		0xD1
#define SCH_IS		0xD2
#define SCH_DIS			0xD3
#define SCH_PAA			0xD4
#define SCH_DPAA		0xD6
#define SCH_GAETA		0xD8
#define SCH_KOMBUWA		0xD9
#define SCH_DKOMBUWA	0xDA
#define SCH_KOMBUDEKA	0xDB
#define SCH_KOMBUAELA	0xDC
#define SCH_DKOMBUAELA	0xDD
#define SCH_KOMBUGAYANU	0xDE
#define SCH_GAYANU		0xDF
#define SCH_DGAETA		0xF2
#define SCH_DGAYANU		0xF3
#define SCH_PUNCT		0xF4

#define COMPLEX_DEF(name)	eCmplx_##name,
enum SchCompound {
#include "complex_def.h"
	eCmplx_Count
};


typedef struct
{
    int key;
    u_int16_t translated;
}
keypair_t;

typedef struct
{
    int plain_count;
    int shift_count;
    int altgr_count;
    int replace_count;
    int shreplace_count;

    const keypair_t *plain;
    const keypair_t *shift;
    const keypair_t *altgr;
    const keypair_t *replace;
    const keypair_t *shreplace;
}
layout_t;

extern const layout_t wijesekera;

#endif
