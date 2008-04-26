/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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
 * Based on scim-hangul.
 * Copyright (c) 2004 James Su <suzhe@turbolinux.com.cn>
 */

#define Uses_SCIM_CONFIG_BASE

#include <gtk/gtk.h>

#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif

#include <scim.h>
#include <gtk/scimkeyselection.h>
#include "scim_wijesekera_prefs.h"
#include "intl.h"

using namespace scim;

#define scim_module_init wijesekera_imengine_setup_LTX_scim_module_init
#define scim_module_exit wijesekera_imengine_setup_LTX_scim_module_exit

#define scim_setup_module_create_ui       wijesekera_imengine_setup_LTX_scim_setup_module_create_ui
#define scim_setup_module_get_category    wijesekera_imengine_setup_LTX_scim_setup_module_get_category
#define scim_setup_module_get_name        wijesekera_imengine_setup_LTX_scim_setup_module_get_name
#define scim_setup_module_get_description wijesekera_imengine_setup_LTX_scim_setup_module_get_description
#define scim_setup_module_load_config     wijesekera_imengine_setup_LTX_scim_setup_module_load_config
#define scim_setup_module_save_config     wijesekera_imengine_setup_LTX_scim_setup_module_save_config
#define scim_setup_module_query_changed   wijesekera_imengine_setup_LTX_scim_setup_module_query_changed

#define DATA_POINTER_KEY "scim-wijesekera::ConfigPointer"

static GtkWidget * create_setup_window ();
static void        load_config (const ConfigPointer &config);
static void        save_config (const ConfigPointer &config);
static bool        query_changed ();

// Module Interface.
extern "C" {
    void scim_module_init (void)
    {
        bindtextdomain (GETTEXT_PACKAGE, SCIM_WIJESEKERA_LOCALEDIR);
        bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
    }

    void scim_module_exit (void)
    {
    }

    GtkWidget * scim_setup_module_create_ui (void)
    {
        return create_setup_window ();
    }

    String scim_setup_module_get_category (void)
    {
        return String ("IMEngine");
    }

    String scim_setup_module_get_name (void)
    {
        return String (_("Wijesekera"));
    }

    String scim_setup_module_get_description (void)
    {
        return String (_("Wijesekera IMEngine Module."));
    }

    void scim_setup_module_load_config (const ConfigPointer &config)
    {
        load_config (config);
    }

    void scim_setup_module_save_config (const ConfigPointer &config)
    {
        save_config (config);
    }

    bool scim_setup_module_query_changed ()
    {
        return query_changed ();
    }
} // extern "C"


// Internal data structure
struct KeyboardConfigData
{
    const char *key;
    String      data;
    const char *label;
    const char *title;
    const char *tooltip;
    GtkWidget  *entry;
    GtkWidget  *button;
};

struct KeyboardConfigPage
{
    const char         *label;
    KeyboardConfigData *data;
};

struct ComboConfigData
{
    const char *label;
    const char *data;
};

// Internal data declaration.
static bool __have_changed    = true;

static GtkTooltips * __widget_tooltips = 0;

static KeyboardConfigData __config_keyboards_common [] =
{
    {
        NULL,
        "",
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
};

static KeyboardConfigData __config_keyboards_mode [] =
{
    {
        NULL,
        "",
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
};

static KeyboardConfigData __config_keyboards_caret [] =
{
    {
        NULL,
        "",
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
};

static KeyboardConfigData __config_keyboards_candidates [] =
{
    {
        NULL,
        "",
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
};

static struct KeyboardConfigPage __key_conf_pages[] =
{
    {N_("Common keys"),     __config_keyboards_common},
    {N_("Mode keys"),       __config_keyboards_mode},
    {N_("Caret keys"),      __config_keyboards_caret},
    {N_("Candidates keys"), __config_keyboards_candidates},
};
static unsigned int __key_conf_pages_num = sizeof (__key_conf_pages) / sizeof (KeyboardConfigPage);


static void on_default_editable_changed       (GtkEditable     *editable,
                                               gpointer         user_data);
static void on_default_toggle_button_toggled  (GtkToggleButton *togglebutton,
                                               gpointer         user_data);
static void on_default_key_selection_clicked  (GtkButton       *button,
                                               gpointer         user_data);
#if 0
static void on_default_combo_changed          (GtkEditable     *editable,
                                               gpointer         user_data);
#endif
static void setup_widget_value ();


#if 0
static GtkWidget *
create_combo_widget (const char *label_text, GtkWidget **widget,
                     gpointer data_p, gpointer candidates_p)
{
    GtkWidget *hbox, *label;

    hbox = gtk_hbox_new (FALSE, 0);
    gtk_widget_show (hbox);
    gtk_container_set_border_width (GTK_CONTAINER (hbox), 4);

    label = gtk_label_new (label_text);
    gtk_widget_show (label);
    gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 4);

    *widget = gtk_combo_new ();
    gtk_combo_set_value_in_list (GTK_COMBO (*widget), TRUE, FALSE);
    gtk_combo_set_case_sensitive (GTK_COMBO (*widget), TRUE);
    gtk_entry_set_editable (GTK_ENTRY (GTK_COMBO (*widget)->entry), FALSE);
    gtk_widget_show (*widget);
    gtk_box_pack_start (GTK_BOX (hbox), *widget, FALSE, FALSE, 4);
    g_object_set_data (G_OBJECT (GTK_COMBO (*widget)->entry), DATA_POINTER_KEY,
                       (gpointer) candidates_p);

    g_signal_connect ((gpointer) GTK_COMBO (*widget)->entry, "changed",
                      G_CALLBACK (on_default_combo_changed),
                      data_p);

    return hbox;
}
#endif

#define APPEND_ENTRY(text, tooltip, widget, i)   \
{ \
    label = gtk_label_new (NULL); \
    gtk_label_set_text_with_mnemonic (GTK_LABEL (label), text); \
    gtk_widget_show (label); \
    gtk_misc_set_alignment (GTK_MISC (label), 1.0, 0.5); \
    gtk_misc_set_padding (GTK_MISC (label), 4, 0); \
    gtk_table_attach (GTK_TABLE (table), label, 0, 1, i, i+1, \
                      (GtkAttachOptions) (GTK_FILL), \
                      (GtkAttachOptions) (GTK_FILL), 4, 4); \
    widget = gtk_entry_new (); \
    gtk_widget_show (widget); \
    gtk_table_attach (GTK_TABLE (table), widget, 1, 2, i, i+1, \
                      (GtkAttachOptions) (GTK_FILL|GTK_EXPAND), \
                      (GtkAttachOptions) (GTK_FILL), 4, 4); \
    if (tooltip && *tooltip) \
        gtk_tooltips_set_tip (__widget_tooltips, widget, \
                              tooltip, NULL); \
}

static GtkWidget *
create_options_page ()
{
    GtkWidget *vbox, *table, *label;

    vbox = gtk_vbox_new (FALSE, 0);
    gtk_widget_show (vbox);

    table = gtk_table_new (2, 2, FALSE);
    gtk_box_pack_start(GTK_BOX(vbox), table, FALSE, FALSE, 4);
    gtk_widget_show (table);

    if (!__widget_tooltips)
        __widget_tooltips = gtk_tooltips_new();

    return vbox;
}

static GtkWidget *
create_keyboard_page (unsigned int page)
{
    GtkWidget *table;
    GtkWidget *label;

    if (page >= __key_conf_pages_num)
        return NULL;

    KeyboardConfigData *data = __key_conf_pages[page].data;

    table = gtk_table_new (3, 3, FALSE);
    gtk_widget_show (table);

    if (!__widget_tooltips)
        __widget_tooltips = gtk_tooltips_new();

    // Create keyboard setting.
    for (unsigned int i = 0; data[i].key; ++ i) {
        APPEND_ENTRY(_(data[i].label),  _(data[i].tooltip), data[i].entry, i);
        gtk_entry_set_editable (GTK_ENTRY (data[i].entry), FALSE);

        data[i].button = gtk_button_new_with_label ("...");
        gtk_widget_show (data[i].button);
        gtk_table_attach (GTK_TABLE (table), data[i].button, 2, 3, i, i+1,
                          (GtkAttachOptions) (GTK_FILL),
                          (GtkAttachOptions) (GTK_FILL), 4, 4);
        gtk_label_set_mnemonic_widget (GTK_LABEL (label), data[i].button);
    }

    for (unsigned int i = 0; data[i].key; ++ i) {
        g_signal_connect ((gpointer) data[i].button, "clicked",
                          G_CALLBACK (on_default_key_selection_clicked),
                          &(data[i]));
        g_signal_connect ((gpointer) data[i].entry, "changed",
                          G_CALLBACK (on_default_editable_changed),
                          &(data[i].data));
    }

#if 0
    for (unsigned int i = 0; data[i].key; ++ i) {
        gtk_tooltips_set_tip (__widget_tooltips, data[i].entry,
                              _(data[i].tooltip), NULL);
    }
#endif

    return table;
}

static GtkWidget *
create_setup_window ()
{
    static GtkWidget *window = NULL;

    if (!window) {
        GtkWidget *notebook = gtk_notebook_new();
        gtk_widget_show (notebook);
        window = notebook;
        gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook), TRUE);

        // Create the first page.
        GtkWidget *page = create_options_page ();
        GtkWidget *label = gtk_label_new (_("Options"));
        gtk_widget_show (label);
        gtk_notebook_append_page (GTK_NOTEBOOK (notebook), page, label);

        // Create the key bind pages.
        for (unsigned int i = 0; i < __key_conf_pages_num; i++) {
            page = create_keyboard_page (i);
            label = gtk_label_new (_(__key_conf_pages[i].label));
            gtk_widget_show (label);
            gtk_notebook_append_page (GTK_NOTEBOOK (notebook), page, label);
        }

        // for preventing enabling left arrow.
	gtk_notebook_set_current_page (GTK_NOTEBOOK (notebook), 1);
        gtk_notebook_set_current_page (GTK_NOTEBOOK (notebook), 0);

        setup_widget_value ();
    }

    return window;
}

#if 0
static void
setup_combo_value (GtkCombo *combo,
                   ComboConfigData *data, const String & str)
{
    GList *list = NULL;
    const char *defval = NULL;

    for (unsigned int i = 0; data[i].label; i++) {
        list = g_list_append (list, (gpointer) _(data[i].label));
        if (!strcmp (data[i].data, str.c_str ()))
            defval = _(data[i].label);
    }

    gtk_combo_set_popdown_strings (combo, list);
    g_list_free (list);

    if (defval)
        gtk_entry_set_text (GTK_ENTRY (combo->entry), defval);
}
#endif

static void
setup_widget_value ()
{
#if 0
    if (__widget_command) {
        gtk_entry_set_text (
            GTK_ENTRY (__widget_command),
            __config_sample_string.c_str ());
    }
#endif

    for (unsigned int j = 0; j < __key_conf_pages_num; ++j) {
        for (unsigned int i = 0; __key_conf_pages[j].data[i].key; ++ i) {
            if (__key_conf_pages[j].data[i].entry) {
                gtk_entry_set_text (
                    GTK_ENTRY (__key_conf_pages[j].data[i].entry),
                    __key_conf_pages[j].data[i].data.c_str ());
            }
        }
    }
}

static void
load_config (const ConfigPointer &config)
{
    if (config.null ())
        return;

#if 0
    __config_sample_string =
        config->read (String (SCIM_WIJESEKERA_CONFIG_SAMPLE_STRING),
                      __config_sample_string);
#endif

    for (unsigned int j = 0; j < __key_conf_pages_num; ++ j) {
        for (unsigned int i = 0; __key_conf_pages[j].data[i].key; ++ i) {
            __key_conf_pages[j].data[i].data =
                config->read (String (__key_conf_pages[j].data[i].key),
                              __key_conf_pages[j].data[i].data);
        }
    }

    setup_widget_value ();

    __have_changed = false;
}

static void
save_config (const ConfigPointer &config)
{
    if (config.null ())
        return;

#if 0
    config->write (String (SCIM_WIJESEKERA_CONFIG_SAMPLE_STRING),
                   __config_sample_string);
#endif

    for (unsigned int j = 0; j < __key_conf_pages_num; j++) {
        for (unsigned int i = 0; __key_conf_pages[j].data[i].key; ++ i) {
            config->write (String (__key_conf_pages[j].data[i].key),
                           __key_conf_pages[j].data[i].data);
        }
    }

    __have_changed = false;
}

static bool
query_changed ()
{
    return __have_changed;
}


static void
on_default_toggle_button_toggled (GtkToggleButton *togglebutton,
                                  gpointer         user_data)
{
    bool *toggle = static_cast<bool*> (user_data);

    if (toggle) {
        *toggle = gtk_toggle_button_get_active (togglebutton);
        __have_changed = true;
    }
}

static void
on_default_editable_changed (GtkEditable *editable,
                             gpointer     user_data)
{
    String *str = static_cast <String *> (user_data);

    if (str) {
        *str = String (gtk_entry_get_text (GTK_ENTRY (editable)));
        __have_changed = true;
    }
}

static void
on_default_key_selection_clicked (GtkButton *button,
                                  gpointer   user_data)
{
    KeyboardConfigData *data = static_cast <KeyboardConfigData *> (user_data);

    if (data) {
        GtkWidget *dialog = scim_key_selection_dialog_new (_(data->title));
        gint result;

        scim_key_selection_dialog_set_keys (
            SCIM_KEY_SELECTION_DIALOG (dialog),
            gtk_entry_get_text (GTK_ENTRY (data->entry)));

        result = gtk_dialog_run (GTK_DIALOG (dialog));

        if (result == GTK_RESPONSE_OK) {
            const gchar *keys = scim_key_selection_dialog_get_keys (
                            SCIM_KEY_SELECTION_DIALOG (dialog));

            if (!keys) keys = "";

            if (strcmp (keys, gtk_entry_get_text (GTK_ENTRY (data->entry))) != 0)
                gtk_entry_set_text (GTK_ENTRY (data->entry), keys);
        }

        gtk_widget_destroy (dialog);
    }
}

static void
on_default_combo_changed (GtkEditable *editable,
                          gpointer user_data)
{
    String *str = static_cast<String *> (user_data);
    ComboConfigData *data
        = static_cast<ComboConfigData *> (g_object_get_data (G_OBJECT (editable),
                                                             DATA_POINTER_KEY));

    if (!str) return;
    if (!data) return;

    const char *label =  gtk_entry_get_text (GTK_ENTRY (editable));

    for (unsigned int i = 0; data[i].label; i++) {
        if (label && !strcmp (_(data[i].label), label)) {
            *str = data[i].data;
            __have_changed = true;
            break;
        }
    }
}
/*
vi:ts=4:nowrap:ai:expandtab
*/
