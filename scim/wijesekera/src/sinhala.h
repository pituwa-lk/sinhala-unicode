/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 *  Copyright (C) 2004 
 *  Copyright (C) 2004 - 2005 
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


#ifndef _STATES_H
#define _STATES_H

#define ZWNJ 0x0c
#define ZWJ  0x0d

#define SCH_ANUSWARA	0x82
#define SCH_VISARGA		0x83
#define SCH_AYANNA		0x85
#define SCH_AAYANNA		0x86
#define SCH_AEYANNA		0x87
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
#define SCH_CAYANNA		0xA0
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
#define SCH_DAYANNA		0xAF
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
#define SCH_IS			0xD2
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

// Complex definitions
#define SCH_YANSAYA		0
#define SCH_RAKRAANSAYA	1
#define SCH_REPAYA		2
#define SCH__LUYANNA	3

#define BV(x)	(1<<x)

// Keytranslation definitions
typedef struct {
	const uint8_t CharIdx;	// Unicode/Punctuation Character or Index to a 
							// complex unicode character. Selection based on
							// next field (flags)
	uint8_t Flags;			// See Below
	// Values of the following have meaning based on Flags	
	uint8_t CmplxId;	// Complex key identifier (if complex)
	uint8_t AltKeyId;	// Id to AltKey mapping (if available)
	uint8_t ModListId;	// Id of Modlist (if modifier)
	uint32	Key;
}KeyTrans_t;

// KeyTranslation related flags
enum {
	eKxf_ChType0,	// ChType=0 simple Unicode, 1=Punctuation, 2=Complex unicode
	eKxf_ChType1,
	eKxf_Commit,	// Iyanna, IIyanna etc can't be modified
	eKxf_Modifier,		// Modifier such as SCH_AL
	eKxf_AltAlso,		// Also has a 3rd shift
};

// names of complex characters
#define COMPLEX_DEF(name)	Cmplx_##name,
enum {
#include "complex_def.h"
	Cmplx_Max
};

// modifier list names
#define MODLIST_DEF(name)	ModId_##name,
enum {
#include "modlist_def.h"
	ModId_Max
};

// AltShift Key names
#define ALTKEY_DEF(name,flags)	AltIdx_##name,
enum {
#include "altkey_def.h"	
	AltIdx_Max
};

typedef struct {
	const int Count;
	const uint8_t *Data;
}Complex_t;

#define CHTYPE_SIMPLE	0
#define CHTYPE_PUNCT	BV(eKxf_ChType0)
#define CHTYPE_COMPLEX	BV(eKxf_ChType1)
#define CHTYPE____		0
#define CHTYPE___C		BV(eKxf_Commit)
#define CHTYPE__M_		BV(eKxf_Modifier)
#define CHTYPE__MC		BV(eKxf_Modifier)|BV(eKxf_Commit)
#define CHTYPE_A__		BV(eKxf_AltAlso)
#define CHTYPE_A_C		BV(eKxf_AltAlso)|BV(eKxf_Commit)
#define CHTYPE_AM_		BV(eKxf_Modifier)|BV(eKxf_Modifier)
#define CHTYPE_AMC		BV(eKxf_AltAlso)|BV(eKxf_Modifier)|BV(eKxf_Commit)

#define CHTYPE_MASK		(BV(eKxf_ChType0)|BV(eKxf_ChType1))

// Mod lists indicate for a given modifier (e.g. SCH_AL) which characters will
// get modified (e.g. SCH_EYANNA + SCH_AL = SCH_EEYANNA).

// Modifer info
typedef struct {
	const uint8_t Source;
	const uint8_t Result;
	const bool Commit;	// Character can not be modified anymore (commit)
}ModInfo_t;

// Pointer list of ModInfo_t
typedef struct {
	const uint8_t Size;	// Size list
	const ModInfo_t *List;
}ModListPtr_t;

#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif

#endif /* _STATES_H */
