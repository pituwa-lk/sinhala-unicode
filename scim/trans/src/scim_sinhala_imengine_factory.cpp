/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 *  Copyright (C) Hiroyuki Ikezoe <poincare@ikezoe.net>
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

#define Uses_SCIM_UTILITY
#define Uses_SCIM_IMENGINE
#define Uses_SCIM_CONFIG_BASE

#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <scim.h>
#include "scim_sinhala_imengine_factory.h"
#include "scim_sinhala_imengine.h"
#include "intl.h"

/* SCIM Related Definitions */
#define scim_module_init sinhala_LTX_scim_module_init
#define scim_module_exit sinhala_LTX_scim_module_exit
#define scim_imengine_module_init sinhala_LTX_scim_imengine_module_init
#define scim_imengine_module_create_factory sinhala_LTX_scim_imengine_module_create_factory
#define SCIM_CONFIG_IMENGINE_SINHALA_UUID     "/IMEngine/Sinhala/UUID-"
#ifndef SCIM_SINHALA_ICON_FILE
    #define SCIM_SINHALA_ICON_FILE           (SCIM_ICONDIR"/scim-sinhala.png")
#endif

static ConfigPointer _scim_config (0);

extern "C" {
    void scim_module_init (void)
    {
        bindtextdomain (GETTEXT_PACKAGE, SCIM_SINHALA_LOCALEDIR);
        bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
    }

    void scim_module_exit (void)
    {
        _scim_config.reset ();
    }

    uint32 scim_imengine_module_init (const ConfigPointer &config)
    {
        SCIM_DEBUG_IMENGINE(1) << "Initialize SINHALA Engine.\n";

        _scim_config = config;

        return 1;
    }

    IMEngineFactoryPointer scim_imengine_module_create_factory (uint32 engine)
    {
        SinhalaFactory *factory = 0;

        try {
            factory = new SinhalaFactory (String ("si_LK"),
                                          String ("c16a58be-6f71-4137-b0ac-441859d58641"),
                                          _scim_config);
        } catch (...) {
            delete factory;
            factory = 0;
        }

        return factory;
    }
}


SinhalaFactory::SinhalaFactory (const String &lang,
                            const String &uuid,
                            const ConfigPointer &config)
    : m_uuid (uuid),
      m_config (config)
{
    SCIM_DEBUG_IMENGINE(1) << "Create Sinhala Factory :\n";
    SCIM_DEBUG_IMENGINE(1) << "  Lang : " << lang << "\n";
    SCIM_DEBUG_IMENGINE(1) << "  UUID : " << uuid << "\n";

    if (lang.length () >= 2)
        set_languages (lang);

    // config
    reload_config (m_config);
    m_reload_signal_connection
        = m_config->signal_connect_reload (slot (this, &SinhalaFactory::reload_config));
}

SinhalaFactory::~SinhalaFactory ()
{
    m_reload_signal_connection.disconnect ();
}

WideString
SinhalaFactory::get_name () const
{
    return utf8_mbstowcs (String ("Sinhala"));
}

WideString
SinhalaFactory::get_authors () const
{
    return WideString ();
}

WideString
SinhalaFactory::get_credits () const
{
    return WideString ();
}

WideString
SinhalaFactory::get_help () const
{
    return WideString ();
}

String
SinhalaFactory::get_uuid () const
{
    return m_uuid;
}

String
SinhalaFactory::get_icon_file () const
{
    return String (SCIM_SINHALA_ICON_FILE);
}

IMEngineInstancePointer
SinhalaFactory::create_instance (const String &encoding, int id)
{
    return new SinhalaInstance (this, encoding, id);
}

void
SinhalaFactory::reload_config (const ConfigPointer &config)
{
    if (!config) return;
}

