/* a very small note taking and logging application
 * see <https://github.com/howerj/note> */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>

#ifndef NOTE_DEFAULT_FILE
#define NOTE_DEFAULT_FILE ("note.log")
#endif

#ifndef NOTE_ENV_PATH
#define NOTE_ENV_PATH ("NOTE")
#endif

int main(int argc, char **argv) {
	char *note = getenv(NOTE_ENV_PATH);
	note = note ? note : NOTE_DEFAULT_FILE;

        if (argc < 2) {
		FILE *f = fopen(note, "r");
		if (!f)
			goto file_error;
		for(int ch = 0; (ch = fgetc(f)) != EOF; putchar(ch))
			;
		return fclose(f) < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
        }

	FILE *f = fopen(note, "a");
	if (!f)
		goto file_error;

	time_t tm = time(0); /* NB. Compile time option for setting format might be nice. */
	for(const char *p = ctime(&tm); *p; p++)
		if (fputc(*p != '\n' ? *p : '\t', f) < 0)
			return EXIT_FAILURE;

	for (int i = 1; i < argc; i++)
		if (fprintf(f, "%s%c", argv[i], (1 + i - argc) ? ' ' : '\n') < 0)
			return EXIT_FAILURE;

        return fclose(f) < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
file_error:
	(void)fprintf(stderr, "(%s) Unable to open file '%s' for reading: %s\n", argv[0], note, strerror(errno));
	return EXIT_FAILURE;
}

