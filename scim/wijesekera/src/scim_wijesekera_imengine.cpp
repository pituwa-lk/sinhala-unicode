/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 *  Copyright (C) 
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

/*
 * The original code is scim_uim_imengine.cpp in scim-uim-0.1.3. 
 * Copyright (C) 2004 James Su <suzhe@tsinghua.org.cn>
 */

#define Uses_SCIM_UTILITY
#define Uses_SCIM_IMENGINE
#define Uses_SCIM_LOOKUP_TABLE
#define Uses_SCIM_CONFIG_BASE

#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <scim.h>
#include "scim_wijesekera_imengine_factory.h"
#include "scim_wijesekera_imengine.h"
#include "scim_wijesekera_prefs.h"
#include "intl.h"

// Keyboard map
KeyTrans_t KeyTrans[]={
	{SCH_REPAYA, 		CHTYPE_COMPLEX|CHTYPE____,	Cmplx_repaya,		0,					0, 				SCIM_KEY_grave},
	{SCH_RAKRAANSAYA,	CHTYPE_COMPLEX|CHTYPE__M_,	Cmplx_rakaransaya,	0,					0,				SCIM_KEY_asciitilde},
	{SCH_PAA,			CHTYPE_SIMPLE|CHTYPE__MC,	0,					0,					ModId_Max, 		SCIM_KEY_q},
	{SCH_DPAA,			CHTYPE_SIMPLE|CHTYPE__MC,	0,					0,					ModId_Max, 		SCIM_KEY_Q},
	{SCH_AYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_w},
	{SCH_UYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_W},
	{SCH_AEDA,			CHTYPE_SIMPLE|CHTYPE__MC,	0, 					0,					ModId_Aeda,		SCIM_KEY_e},
	{SCH_DAEDA,			CHTYPE_SIMPLE|CHTYPE__MC,	0, 					0,					ModId_DAeda,	SCIM_KEY_E},
	{SCH_RAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_r},
	{SCH_IRUYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_R},
	{SCH_EYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_t},
	{SCH_OYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_T},
	{SCH_HAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_y},
	{SCH_SHAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_Y},
	{SCH_MAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_u},
	{SCH_MBAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_U},
	{SCH_SAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_i},
	{SCH__SAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_I},
	{SCH_DAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_o},
	{SCH__DAYANNA,		CHTYPE_SIMPLE|CHTYPE_A__,	0,					AltIdx_NDAYANNA,	0, 				SCIM_KEY_O},
	{SCH_CAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_p},
	{SCH__CAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_P},
	{SCH_NYAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_bracketleft},
	{SCH_GNYAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_braceleft},
	{';',				CHTYPE_PUNCT|CHTYPE____,	0,					0,					0,				SCIM_KEY_bracketright },
	{':',				CHTYPE_PUNCT|CHTYPE____,	0,					0,					0,				SCIM_KEY_braceright},
	{SCH_AL,			CHTYPE_SIMPLE|CHTYPE__M_,	0,					0,					ModId_Al,		SCIM_KEY_a},
	{SCH_GAYANU,		CHTYPE_SIMPLE|CHTYPE_AM_,	0,					AltIdx_DGAYANU,		ModId_Gayanu, 	SCIM_KEY_A},
	{SCH_IS,			CHTYPE_SIMPLE|CHTYPE__MC,	0,					0,					ModId_Max, 		SCIM_KEY_s},
	{SCH_DIS,			CHTYPE_SIMPLE|CHTYPE__MC,	0,					0,					ModId_Max, 		SCIM_KEY_S},
	{SCH_AELA,			CHTYPE_SIMPLE|CHTYPE__M_,	0,					0,					ModId_Aela,		SCIM_KEY_d},
	{SCH_GAETA,			CHTYPE_SIMPLE|CHTYPE__M_,	0,					0,					ModId_Gaeta,	SCIM_KEY_D},
	{SCH_KOMBUWA,		CHTYPE_SIMPLE|CHTYPE__M_,	0,					0,					ModId_Kombu,	SCIM_KEY_f},
	{SCH_FAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_F},
	{SCH_TTAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_g},
	{SCH_GAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_G},
	{SCH_YAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_h},
	{SCH_YANSAYA,		CHTYPE_COMPLEX|CHTYPE__M_,	Cmplx_yansaya,		0,					ModId_Max,		SCIM_KEY_H},
	{SCH_VAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_j},
	{SCH__LUYANNA,		CHTYPE_COMPLEX|CHTYPE___C,	Cmplx_mluyanna,		0,					0, 				SCIM_KEY_J},
	{SCH_NAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_k},
	{SCH__NAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_K},
	{SCH_KAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_l},
	{SCH__KAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_L},
	{SCH_TAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_semicolon},
	{SCH__TAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_colon},
	{'.',				CHTYPE_PUNCT|CHTYPE____,	0,					0,					0,				SCIM_KEY_quoteright},
	{',',				CHTYPE_PUNCT|CHTYPE____,	0,					0,					0,				SCIM_KEY_quotedbl},
	{'\'',				CHTYPE_PUNCT|CHTYPE____,	0,					0,					0,				SCIM_KEY_z},
	{'\"',				CHTYPE_PUNCT|CHTYPE____,	0,					0,					0,				SCIM_KEY_Z},
	{SCH_ANUSWARA,		CHTYPE_SIMPLE|CHTYPE___C,	0,					0,					0, 				SCIM_KEY_x},
	{SCH_NAASIKAYA,		CHTYPE_SIMPLE|CHTYPE_A__,	0,					AltIdx_VISARGA,		0, 				SCIM_KEY_X},
	{SCH_JAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_c},
	{SCH__JAYANNA,		CHTYPE_SIMPLE|CHTYPE_A__,	0, 					AltIdx_NJAYANNA,	0, 				SCIM_KEY_C},
	{SCH_DDAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_v},
	{SCH__DDAYANNA,		CHTYPE_SIMPLE|CHTYPE_A__,	0, 					AltIdx_NDDAYANNA,	0,	 			SCIM_KEY_V},
	{SCH_IYANNA,		CHTYPE_SIMPLE|CHTYPE___C,	0,					0,					0, 				SCIM_KEY_b},
	{SCH_IIYANNA,		CHTYPE_SIMPLE|CHTYPE___C,	0,					0,					0, 				SCIM_KEY_B},
	{SCH_BAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_n},
	{SCH__BAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_N},
	{SCH_PAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_m},
	{SCH__PAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_M},
	{SCH_LAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_comma},
	{SCH__LAYANNA,		CHTYPE_SIMPLE|CHTYPE_A__,	0,					AltIdx_ILUYANNA,	0, 				SCIM_KEY_less},
	{SCH_GAYANNA,		CHTYPE_SIMPLE|CHTYPE____,	0,					0,					0,				SCIM_KEY_period},
	{SCH__GAYANNA,		CHTYPE_SIMPLE|CHTYPE_A__,	0,					AltIdx_NGAYANNA,	0, 				SCIM_KEY_greater},
},AltTrans[]={	// 3rd Shift Characters
#define ALTKEY_DEF(name,flags)	\
	{SCH_##name, flags, 0, 0, ModId_Max, 0},	// key is redundant
#include "altkey_def.h"
};

// definition of 'complex' characters
const uint8_t yansaya[] = {
	0xca, ZWJ, 0xba
};

const uint8_t rakaransaya[] = {
	0xca, ZWJ, 0xbb
};

const uint8_t repaya[] = {
	0xbb, 0xca, ZWJ
};

const uint8_t mluyanna[] = {
	SCH__LAYANNA, SCH_PAA
};

// List of complex characters
#define COMPLEX_DEF(name)	{sizeof(name)/sizeof(uint8_t), name},
const Complex_t ComplexList[] = {
#include "complex_def.h"
};

// All modifications performed by some modifier keys
static const ModInfo_t AlMods[] = {
	{ SCH_EYANNA,	SCH_EEYANNA, true},
	{ SCH_OYANNA,	SCH_OOYANNA, true},
	{ SCH_KOMBUWA,	SCH_DKOMBUWA, false},	// What do you think?
	{ SCH_KOMBUAELA, SCH_DKOMBUAELA, true},
};

static const ModInfo_t AelaMods[] = {
	{ SCH_AYANNA, SCH_AAYANNA, true},
	{ SCH_KOMBUWA, SCH_KOMBUAELA, false},
	{ SCH_DKOMBUWA, SCH_DKOMBUAELA, true},
};

static const ModInfo_t AedaMods[] = {
	{ SCH_AYANNA, SCH_AEYANNA, true},
};

static const ModInfo_t DAedaMods[] = {
	{ SCH_AYANNA, SCH_AEEYANNA, true},
};

static const ModInfo_t GaetaMods[] = {
	{ SCH_IRUYANNA, SCH_IRUUYANNA, true},
	{ SCH_GAETA, SCH_DGAETA, true},
};

static const ModInfo_t KombuMods[] = {
	{ SCH_EYANNA, SCH_AIYANNA, true},
	{ SCH_AL, SCH_DKOMBUWA, true},
	{ SCH_KOMBUWA, SCH_KOMBUDEKA, true},
	{ SCH_AELA, SCH_KOMBUAELA, false},
	{ SCH_GAYANU, SCH_KOMBUGAYANU, true},
};

static const ModInfo_t GayanuMods[] = {
	{ SCH_UYANNA, SCH_UUYANNA, true},
	{ SCH_ILUYANNA, SCH_ILUUYANNA, true},
	{ SCH_OYANNA, SCH_AUYANNA, true},
	{ SCH_KOMBUWA, SCH_KOMBUGAYANU, true},
};

// List of ModLists (i.e. list of lists defined above)
#define MODLIST_DEF(name)	{ sizeof(name##Mods)/sizeof(ModInfo_t), name##Mods}, 
static const ModListPtr_t ModLists[] = {
#include "modlist_def.h"
};

WijesekeraInstance::WijesekeraInstance (WijesekeraFactory *factory,
                                    const String    &encoding,
                                    int              id)
    : IMEngineInstanceBase (factory, encoding, id),
      m_factory (factory),
      m_prev_key (0,0),
	  AuxCount(0)
{
    SCIM_DEBUG_IMENGINE(1) << "Create WIJESEKERA Instance : ";
}

WijesekeraInstance::~WijesekeraInstance ()
{
}

void
WijesekeraInstance::build_unicode_char(unsigned char lsb, unsigned char *u)
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

void 
WijesekeraInstance::translate_and_commit(void)
{
	uint8_t buf[32],*d=buf;

	if(!AuxCount) {
		return;
	}

	buf[0]=0;	
	for(int i=0;i<AuxCount;i++,d+=3) {	// XXX Assume everything is 3 bytes
		build_unicode_char(Aux[i], d);
	}
	
	commit_string(utf8_mbstowcs((const char*)buf));
	Aux[0]=0;
	AuxCount=0;
}

void 
WijesekeraInstance::display_aux(void)
{
	uint8_t buf[32],*d=buf;

	if(!AuxCount) {
		hide_aux_string();
		return;
	}
	
	buf[0]=0;	
	for(int i=0;i<AuxCount;i++,d+=3) {	// XXX Assume everything is 3 bytes
		build_unicode_char(Aux[i], d);
	}
	
	update_aux_string(utf8_mbstowcs((const char *)buf), AttributeList());
	show_aux_string();
}

void
WijesekeraInstance::build_complex_char(const uint8_t idx)
{
	const uint8_t *c=ComplexList[idx].Data;
	int i=ComplexList[idx].Count;
	
	while(i--) {
		Aux[AuxCount++]=*c;
		c++;
	}
	Aux[AuxCount]=0;
}

void
WijesekeraInstance::handle_modifier(const KeyTrans_t *kt)
{
	const ModListPtr_t *ml=ModLists;
	bool found=false;
	
	// find the matching ModList
	if(kt->ModListId<ModId_Max) {
		ml=&ModLists[kt->ModListId];
		found=true;
	} 
	
	if(found) {
		// now find the modifiee (if any)
		const ModInfo_t *mi=ml->List;
		found=false;
		for(int i=0;i<ml->Size;i++,mi++) {
			if(Aux[AuxCount-1]==mi->Source) {
				Aux[AuxCount-1]=mi->Result;
				if(mi->Commit) {
					translate_and_commit();
				}
				return;
			}
		}
	}

	if(Aux[AuxCount-1]>= SCH_AL && Aux[AuxCount-1] <= SCH_DGAYANU) {
		// disallow modifications to modifications (e.g. SCH_KOMBUDEKA +
		// SCH_AELA)
		return;
	}
	
	if((kt->Flags&CHTYPE_MASK)==CHTYPE_COMPLEX) {
		build_complex_char(kt->CmplxId);
	} else {	// XXX Assume simple
		Aux[AuxCount++]=kt->CharIdx;
		Aux[AuxCount]=0;
	}
	
	if(kt->Flags&BV(eKxf_Commit)) {	// keys such as paa-pilla
		translate_and_commit();
	}
}

bool
WijesekeraInstance::handle_key(const KeyEvent& key)
{
	KeyTrans_t *kt=&KeyTrans[0];
	bool found=false;
	
	if(is_shift_handled(key)) {
		for(int i=0;i<sizeof(KeyTrans)/sizeof(KeyTrans[0]);i++,kt++) {
			if(kt->Key==key.code) {	// matched some key
				if(key.is_mod2_down()) {
					// we're actually looking for the Alt Shift key
					if(kt->Flags&BV(eKxf_AltAlso)) {
						kt=&AltTrans[kt->AltKeyId];
					} else {
						return true;	// Just trap key
					}
				}
				found=true;
				break;
			}
		}
	}

	if(!found) {
		translate_and_commit();
		display_aux();
		return false;
	}
	
	if(kt->Flags&BV(eKxf_Modifier)) {
		if(!AuxCount) {
			// for now we won't allow lonely modifiers (simpler)
			update_aux_string(utf8_mbstowcs("<!!>"), AttributeList());
			show_aux_string();
			return true;
		} else {
			handle_modifier(kt);
		}
	} else {
		// not a modifier. Commit what was already in aux string
		translate_and_commit();
		if((kt->Flags&CHTYPE_MASK)==CHTYPE_SIMPLE) {
			Aux[AuxCount++]=kt->CharIdx;
			Aux[AuxCount]=0;
		} else if((kt->Flags&CHTYPE_MASK)==CHTYPE_PUNCT) {
			Aux[AuxCount++]=kt->CharIdx;
			Aux[AuxCount]=0;
			commit_string(utf8_mbstowcs((const char*)Aux));
			AuxCount=0;
		} else if((kt->Flags&CHTYPE_MASK)==CHTYPE_COMPLEX) {
			build_complex_char(kt->CmplxId);
		} else {
			commit_string(utf8_mbstowcs("Unknown CHTYPE"));
		}

		if(kt->Flags&BV(eKxf_Commit)) {
			translate_and_commit();
		}
	}

	display_aux();
	return true;
}

bool
WijesekeraInstance::process_key_event (const KeyEvent& key)
{
    SCIM_DEBUG_IMENGINE(2) << "process_key_event.\n";
	char temp[64];

	if(key.code==SCIM_KEY_NullKey) {
		return false;
	}
	
    // ignore key release.
    if (key.is_key_release ()) {
        return true;
    }

    // ignore modifier keys
    if (key.code == SCIM_KEY_Shift_L || key.code == SCIM_KEY_Shift_R ||
		key.code == SCIM_KEY_Alt_L ||  key.code == SCIM_KEY_Alt_R ||
        key.code == SCIM_KEY_Control_L || key.code == SCIM_KEY_Control_R)
        return false;

    // lookup user defined key binds
    if (process_key_event_lookup_keybind (key))
        return true;

	if(!handle_key(key)) {
		return false;
	}

    return true;
}

bool
WijesekeraInstance::process_key_event_lookup_keybind (const KeyEvent& key)
{
    return false;
}

void
WijesekeraInstance::move_preedit_caret (unsigned int pos)
{
}

void
WijesekeraInstance::select_candidate (unsigned int item)
{
    SCIM_DEBUG_IMENGINE(2) << "select_candidate.\n";

    select_candidate_no_direct (item);
}

void
WijesekeraInstance::select_candidate_no_direct (unsigned int item)
{
    SCIM_DEBUG_IMENGINE(2) << "select_candidate_no_direct.\n";

    m_lookup_table.set_cursor_pos_in_current_page (item);
    update_lookup_table (m_lookup_table);
}

void
WijesekeraInstance::update_lookup_table_page_size (unsigned int page_size)
{
    SCIM_DEBUG_IMENGINE(2) << "update_lookup_table_page_size.\n";

    m_lookup_table.set_page_size (page_size);
}

void
WijesekeraInstance::lookup_table_page_up ()
{
    SCIM_DEBUG_IMENGINE(2) << "lookup_table_page_up.\n";

    m_lookup_table.page_up ();
    update_lookup_table (m_lookup_table);
}

void
WijesekeraInstance::lookup_table_page_down ()
{
    SCIM_DEBUG_IMENGINE(2) << "lookup_table_page_down.\n";

    m_lookup_table.page_down ();
    update_lookup_table (m_lookup_table);
}

void
WijesekeraInstance::reset ()
{
    SCIM_DEBUG_IMENGINE(2) << "reset.\n";

    m_lookup_table.clear ();
    update_preedit_caret (0);
    update_preedit_string (utf8_mbstowcs (""));
    hide_lookup_table ();
    hide_preedit_string ();
}

void
WijesekeraInstance::focus_in ()
{
    SCIM_DEBUG_IMENGINE(2) << "focus_in.\n";

    hide_aux_string ();
}

void
WijesekeraInstance::focus_out ()
{
    SCIM_DEBUG_IMENGINE(2) << "focus_out.\n";
}

void
WijesekeraInstance::trigger_property (const String &property)
{
    String wijesekera_prop = property.substr (property.find_last_of ('/') + 1);

    SCIM_DEBUG_IMENGINE(2) << "trigger_property : " << property << " - " << wijesekera_prop << "\n";
}

/*
vi:ts=4:nowrap:ai:expandtab
*/
