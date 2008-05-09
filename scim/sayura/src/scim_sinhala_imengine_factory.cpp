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
#define scim_module_init sayura_LTX_scim_module_init
#define scim_module_exit sayura_LTX_scim_module_exit
#define scim_imengine_module_init sayura_LTX_scim_imengine_module_init
#define scim_imengine_module_create_factory sayura_LTX_scim_imengine_module_create_factory
#define SCIM_CONFIG_IMENGINE_SINHALA_UUID     "/IMEngine/Sayura/UUID-"
#ifndef SCIM_SINHALA_ICON_FILE
    #define SCIM_SINHALA_ICON_FILE           (SCIM_ICONDIR"/scim-sayura.png")
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
        SCIM_DEBUG_IMENGINE(1) << "Initialize Sayura Engine.\n";

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
    return utf8_mbstowcs (String ("Sayura"));
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

WideString SinhalaFactory::get_help () const
{
	String help;

	help =  String (_("Keyboard usage:\n")) + 
		String (_("\tඅ: a\t\tආ: aa\tඇ: q,A,aaa\tඈ: qq,AA,aaaa\n")) +
		String (_("\tඉ: i\t\tඊ: ii\t\tඋ: u\t\t\tඌ: uu\n")) +
		String (_("\tඑ: e\t\tඒ: ee\tඔ: o\t\t\tඕ: oo\n")) +
		String (_("\tඓ: I\t\tඖ: O\tඍ: U\t\tඎ: UU\n\n")) +
		String (_("\tක: k\t\tඛ: kH\tග: g\t\tඝ: gH\tඞ: X\n")) +
		String (_("\tච: c\t\tඡ: C,cH\tජ: j\t\tඣ: J,jH\tඤ: z\n")) +
		String (_("\tට: T\t\tඨ: TH\tඩ: D\t\tඪ: DH\tණ: N\n")) +
		String (_("\tත: t\t\tථ: tH\tද: d\t\tධ: dH\tන: n\n")) +
		String (_("\tප: p\t\tඵ: P,pH\tබ: b\t\tභ: B,bH\tම: m\n")) +
		String (_("\tය: y\t\tර: r\t\tල: l\t\tව: v\n")) +
		String (_("\tස: s\t\tශ: S\t\tෂ: sH,SH\tහ: h\t\tළ: L\n\n")) +
		String (_("\tඟ: gG\tඦ: jG\tඬ: DG\tඳ: dG\n")) +
		String (_("\tඹ: M,bG\tඥ: Z\tෆ: f\n\n")) +
		String (_("\tක: k\t\tකා: ka\tකැ: kq\tකෑ: kqq\n")) +
		String (_("\tකි: ki\tකී: kii\tකු: ku\tකූ: kuu\n")) +
		String (_("\tකෙ: ke\tකේ: kee\tකො: ko\tකෝ: koo\n")) +
		String (_("\tකෛ: kI\tකෞ: kO\tකෘ: kU\tකෲ: kUU\n")) +
		String (_("\tක්‍ර: kR\tක්‍ය: kY\tක්: kw\tක්‍ෂ: kWsH\n")) +
		String (_("\tකං: kx\tකඃ: khH\n")) +
		String (_("\n"));
	return utf8_mbstowcs (help);
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

