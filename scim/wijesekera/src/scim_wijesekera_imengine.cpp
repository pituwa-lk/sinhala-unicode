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
#include <string.h>

#include <scim.h>
#include "scim_wijesekera_imengine_factory.h"
#include "scim_wijesekera_imengine.h"
#include "scim_wijesekera_prefs.h"
#include "intl.h"
#include "parser.h"

WijesekeraInstance::WijesekeraInstance (WijesekeraFactory *factory,
                                    const String    &encoding,
                                    int              id)
    : IMEngineInstanceBase (factory, encoding, id),
      m_factory (factory)
{
	SCIM_DEBUG_IMENGINE(1) << "Create WIJESEKERA Instance : ";
	memset(&m_parser_data, 0, sizeof(m_parser_data));
	m_parser_data.compat.inst_base = this;
}

WijesekeraInstance::~WijesekeraInstance ()
{
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

    printf("code %x, mask=%x\n", key.code, key.mask);

    if(key.code == SCIM_KEY_Alt_R) {
	    m_parser_data.compat.alt_gr = 1;
	    return true;
    }

    // ignore modifier keys
    if (key.code == SCIM_KEY_Shift_L || key.code == SCIM_KEY_Shift_R ||
	key.code == SCIM_KEY_Alt_L ||
        key.code == SCIM_KEY_Control_L || key.code == SCIM_KEY_Control_R)
        return false;


    // lookup user defined key binds
    if (process_key_event_lookup_keybind (key))
        return true;

    if(!(key.mask & SCIM_KEY_AltMask)) {
	    m_parser_data.compat.alt_gr = 0;
    }

    if(parse_key(key.code, key.mask, m_parser_data.compat.alt_gr, &m_parser_data)) {
	    // The right Alt key (AltGr) is highjacked
	    return m_parser_data.compat.alt_gr?true:false;
    }

    return true;
}

bool
WijesekeraInstance::process_key_event_lookup_keybind (const KeyEvent& key)
{
    return false;
}

void
WijesekeraInstance::reset ()
{
    SCIM_DEBUG_IMENGINE(2) << "reset.\n";

    m_lookup_table.clear ();
    update_preedit_caret (0);
    parse_key(0, 0, 0, &m_parser_data);
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
    parse_key(0, 0, 0, &m_parser_data);
}

void 
WijesekeraInstance::update_client_capabilities (unsigned int cap)
{
    m_parser_data.compat.cap = cap;
}

/*
vi:ts=4:nowrap:ai:expandtab
*/
