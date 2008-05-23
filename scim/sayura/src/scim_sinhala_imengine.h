/*
 *  Copyright (C) 2004 Hiroyuki Ikezoe
 *  Copyright (C) 2005 Kazuki Ohta <mover@hct.zaq.ne.jp>
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

#ifndef __SCIM_SINHALA_IMENGINE_H__
#define __SCIM_SINHALA_IMENGINE_H__

#include <scim.h>

using namespace scim;

class SinhalaInstance : public IMEngineInstanceBase
{
	friend class SinhalaFactory;

private:
	SinhalaFactory *m_factory;
	KeyEvent m_prev_key;

	/* for candidates window */
	CommonLookupTable m_lookup_table;
	WideString m_preedit_string;

	/* for toolbar */
	PropertyList m_properties;

public:
	SinhalaInstance(SinhalaFactory *factory,
			const String &encoding, int id = -1);
	virtual ~SinhalaInstance();

	virtual bool process_key_event(const KeyEvent& key);
	virtual void move_preedit_caret(unsigned int pos);
	virtual void select_candidate(unsigned int item);
	virtual void update_lookup_table_page_size(unsigned int page_size);
	virtual void lookup_table_page_up(void);
	virtual void lookup_table_page_down(void);
	virtual void reset(void);
	virtual void focus_in(void);
	virtual void focus_out(void);
	virtual void trigger_property(const String &property);

public:

private: // actions

private:
	void select_candidate_no_direct(unsigned int item);

	/* processing key event */
	bool process_key_event_lookup_keybind(const KeyEvent &key);
	bool process_key_event_without_preedit(const KeyEvent &key);
	bool process_key_event_with_preedit(const KeyEvent &key);
	bool process_key_event_with_candidate(const KeyEvent &key);
	bool process_remaining_key_event(const KeyEvent &key);
	void backspace();

	/* sinhala related functions */
	int get_known_lsb_character(int c);
	int lsb_to_unicode(int lsb);
	int is_consonent(int c);
	int is_vowel(int c);
	int is_modifier(int c);
	int find_consonent_by_key(int k);
	int find_consonent(int c);
	int find_vowel_by_key(int k);
	unsigned char* create_unicode_character_from_lsb(unsigned int lsb);
	void update_preedit();
	bool sinhala_transliterated_filter_keypress(const KeyEvent &key);
	bool handle_consonant_pressed(const KeyEvent &event, int c);
	bool handle_vowel_pressed(const KeyEvent &event, int c);
};

#endif /* __SCIM_SINHALA_IMENGINE_H__ */
