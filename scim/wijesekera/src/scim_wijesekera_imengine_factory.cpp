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

#define scim_module_init wijesekera_LTX_scim_module_init
#define scim_module_exit wijesekera_LTX_scim_module_exit
#define scim_imengine_module_init wijesekera_LTX_scim_imengine_module_init
#define scim_imengine_module_create_factory wijesekera_LTX_scim_imengine_module_create_factory

#define SCIM_CONFIG_IMENGINE_WIJESEKERA_UUID     "eecc608c-900e-490e-b533-74b0738b2c7d"

#ifndef SCIM_WIJESEKERA_ICON_FILE
    #define SCIM_WIJESEKERA_ICON_FILE           (SCIM_ICONDIR"/scim-wijesekera.png")
#endif

static ConfigPointer _scim_config (0);

extern "C" {
    void scim_module_init (void)
    {
        bindtextdomain (GETTEXT_PACKAGE, SCIM_WIJESEKERA_LOCALEDIR);
        bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
    }

    void scim_module_exit (void)
    {
        _scim_config.reset ();
    }

    uint32 scim_imengine_module_init (const ConfigPointer &config)
    {
        SCIM_DEBUG_IMENGINE(1) << "Initialize WIJESEKERA Engine.\n";

        _scim_config = config;

        return 1;
    }

    IMEngineFactoryPointer scim_imengine_module_create_factory (uint32 engine)
    {
        WijesekeraFactory *factory = 0;

        try {
            factory = new WijesekeraFactory (String ("si_LK"),
					     String (SCIM_CONFIG_IMENGINE_WIJESEKERA_UUID),
                                           _scim_config);
        } catch (...) {
            delete factory;
            factory = 0;
        }

        return factory;
    }
}


WijesekeraFactory::WijesekeraFactory (const String &lang,
                                const String &uuid,
                                const ConfigPointer &config)
    : m_uuid (uuid),
      m_config (config)
{
    SCIM_DEBUG_IMENGINE(1) << "Create Wijesekera Factory :\n";
    SCIM_DEBUG_IMENGINE(1) << "  Lang : " << lang << "\n";
    SCIM_DEBUG_IMENGINE(1) << "  UUID : " << uuid << "\n";

    if (lang.length () >= 2)
        set_languages (lang);

    // config
    reload_config (m_config);
    m_reload_signal_connection
        = m_config->signal_connect_reload (slot (this, &WijesekeraFactory::reload_config));
}

WijesekeraFactory::~WijesekeraFactory ()
{
}

WideString
WijesekeraFactory::get_name () const
{
    return utf8_mbstowcs (String ("Wijesekera"));
}

WideString
WijesekeraFactory::get_authors () const
{
    return WideString ();
}

WideString
WijesekeraFactory::get_credits () const
{
    return WideString ();
}

WideString
WijesekeraFactory::get_help () const
{
    return WideString ();
}

String
WijesekeraFactory::get_uuid () const
{
    return m_uuid;
}

String
WijesekeraFactory::get_icon_file () const
{
    return String (SCIM_WIJESEKERA_ICON_FILE);
}

IMEngineInstancePointer
WijesekeraFactory::create_instance (const String &encoding, int id)
{
    return new WijesekeraInstance (this, encoding, id);
}

void
WijesekeraFactory::reload_config (const ConfigPointer &config)
{
    if (!config) return;
}
