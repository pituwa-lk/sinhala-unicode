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

/*
 * The original code is scim_uim_imengine.cpp in scim-uim-0.1.3. 
 * Copyright (C) 2004 James Su <suzhe@tsinghua.org.cn>
 */

#ifndef __SCIM_WIJESEKERA_IMENGINE_H__
#define __SCIM_WIJESEKERA_IMENGINE_H__

#include <scim.h>

using namespace scim;

#include "sinhala.h"

class WijesekeraInstance : public IMEngineInstanceBase
{
    friend class WijesekeraFactory;

private:
    WijesekeraFactory        *m_factory;

    KeyEvent                m_prev_key;

    /* for candidates window */
    CommonLookupTable       m_lookup_table;

    /* for toolbar */
    PropertyList            m_properties;

	uint8_t Aux[32];	// Aux String (in LSBs)
	int AuxCount;	// # of bytes in string

public:
    WijesekeraInstance (WijesekeraFactory *factory,
                      const String    &encoding,
                      int              id = -1);
    virtual ~WijesekeraInstance ();

    virtual bool process_key_event             (const KeyEvent& key);
    virtual void move_preedit_caret            (unsigned int pos);
    virtual void select_candidate              (unsigned int item);
    virtual void update_lookup_table_page_size (unsigned int page_size);
    virtual void lookup_table_page_up          (void);
    virtual void lookup_table_page_down        (void);
    virtual void reset                         (void);
    virtual void focus_in                      (void);
    virtual void focus_out                     (void);
    virtual void trigger_property              (const String &property);

public:

private: // actions

private:
    void   select_candidate_no_direct          (unsigned int    item);

    /* processing key event */
    bool   process_key_event_lookup_keybind    (const KeyEvent &key);
    bool   process_key_event_without_preedit   (const KeyEvent &key);
    bool   process_key_event_with_preedit      (const KeyEvent &key);
    bool   process_key_event_with_candidate    (const KeyEvent &key);
    bool   process_remaining_key_event         (const KeyEvent &key);

	inline bool is_shift_handled(const KeyEvent &key)
	{
		return (key.mask==0||key.is_shift_down()||key.is_mod2_down());
	}
	void   build_unicode_char(unsigned char lsb, unsigned char *u);
	void   translate_and_commit(void);
	void   build_complex_char(const uint8_t idx);
	void   display_aux(void);
	void   handle_modifier(const KeyTrans_t *kt);
	bool   handle_key(const KeyEvent& key);
};
#endif /* __SCIM_WIJESEKERA_IMENGINE_H__ */
/*
vi:ts=4:nowrap:ai:expandtab
*/
