#include <stdio.h>
#include <string.h>

void init()
{
	printf("<html>\n");
	printf("\t<head>\n");
	printf("\t\t<title>title</title>\n");
	printf("\t\t<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");
	printf("\t</head>\n");
	printf("\t<body bgcolor=\"#ffffff\">\n");

	printf("\t\t<table width=\"1%%\" align=\"center\">\n");
	printf("\t\t\t<tr><td>\n");
}

void done()
{
	printf("\t\t\t</td></tr>\n");
	printf("\t\t</table>\n");
	printf("\t</body>\n");
	printf("</html>\n");
}

int main()
{
	int c = 0;
	int i, t;
	char buffer[4096];
	int tabs[64];
	int in_verse = 0;

	init();

	tabs[0] = 0;

	while (c != EOF) {
		i = 0;

		while (((c = getchar()) != EOF) && (c != '\n'))
			if (c == ' ') {
				strcpy(buffer + i, "&nbsp;");
				i += 6;
			}
			else
				buffer[i++] = c;
		buffer[i] = 0;

		if (buffer[0]) {
			t = 0;
			for (i = 0; buffer[i]; i++)
				if (buffer[i] == '\t') {
					buffer[i] = 0;
					tabs[++t] = i + 1;
				}
			if (!in_verse)
				printf("\t\t\t\t<table width=\"100%%\">\n");
			in_verse = 1;

			printf("\t\t\t\t\t<tr>");
			for (i = 0; i < t; i++)
				printf("<td align=\"left\">%s</td>", buffer + tabs[i]);
			printf("<td width=\"100%%\" align=\"");
			printf(t ? "right" : "left");
			printf("\">%s</td></tr>\n", buffer + tabs[t]);
		}
		else {
			if (in_verse)
				printf("\t\t\t\t</table><br />\n");
			in_verse = 0;
		}
	}

	done();

	return 0;
}

