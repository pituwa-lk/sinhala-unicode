/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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

#ifndef __SCIM_SINHALA_IMENGINE_FACTORY_H__
#define __SCIM_SINHALA_IMENGINE_FACTORY_H__

#define Uses_SCIM_ICONV
#include <scim.h>
#include "scim_sinhala_action.h"

using namespace scim;

class SinhalaFactory : public IMEngineFactoryBase
{
    String m_uuid;

    friend class SinhalaInstance;

    /* config */
    ConfigPointer  m_config;
    Connection     m_reload_signal_connection;

    /* for preference */

    /* for key bindings */
    std::vector<SinhalaAction> m_actions;

public:
    SinhalaFactory (const String &lang,
                  const String &uuid,
                  const ConfigPointer &config);
    virtual ~SinhalaFactory ();

    virtual WideString  get_name      () const;
    virtual WideString  get_authors   () const;
    virtual WideString  get_credits   () const;
    virtual WideString  get_help      () const;
    virtual String      get_uuid      () const;
    virtual String      get_icon_file () const;

    virtual IMEngineInstancePointer create_instance (const String& encoding,
                                                     int id = -1);

private:
    void reload_config (const ConfigPointer &config);
};

#endif /* __SCIM_SINHALA_IMENGINE_FACTORY_H__ */
/*
vi:ts=4:nowrap:ai:expandtab
*/
