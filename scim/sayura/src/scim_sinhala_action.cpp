/*
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "scim_sinhala_action.h"

SinhalaAction::SinhalaAction(const String &name,
		const String &key_bindings, PMF pmf) :
	m_name(name), m_pmf(pmf)
{
	scim_string_to_key_list(m_key_bindings, key_bindings);
}

SinhalaAction::~SinhalaAction(void)
{
}

bool SinhalaAction::perform(SinhalaInstance *performer)
{
	if (!performer || !m_pmf)
		return false;

	return (performer->*m_pmf)();
}

bool SinhalaAction::perform(SinhalaInstance *performer, const KeyEvent &key)
{
	if (!performer || !m_pmf)
		return false;

	if (match_key_event(key))
		return (performer->*m_pmf)();

	return false;
}

bool SinhalaAction::match_key_event(const KeyEvent &key)
{
	KeyEventList::const_iterator kit;

	for (kit = m_key_bindings.begin(); kit != m_key_bindings.end(); ++kit) {
		if (key.code == kit->code && key.mask == kit->mask)
			return true;
	}
	return false;
}

