#include <gtk/gtk.h>

gint
main(int argc, char *argv[])
{
	g_print("%s\n", gtk_rc_get_im_module_file());
	return 0;
}

