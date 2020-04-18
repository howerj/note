/* a very small note taking and logging application
 * see <https://github.com/howerj/note> */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

static char *note_file = "note.log";

int main(int argc, char **argv) {
        FILE *note = 0;
        time_t tm;
        int i = 0;
        char *p = NULL, *homedir = NULL;
        struct passwd *pw = getpwuid(getuid());

        if (NULL == pw) {
                perror("getpwuid");
                return EXIT_FAILURE;
        }

        homedir = calloc(strlen(pw->pw_dir) + strlen(note_file) + 2, sizeof(char));
        if (NULL == homedir) {
                perror("calloc");
                return EXIT_FAILURE;
        }

        strcat(homedir, pw->pw_dir);
        strcat(homedir, "/");
        strcat(homedir, note_file);

        if (argc < 2) {
                if ((note = fopen(homedir, "r"))) {
                        while ((i = fgetc(note)) != EOF)
                                putchar(i);
                } else {
                        perror(homedir);
                        return EXIT_FAILURE;
                }
        } else {
                if ((note = fopen(homedir, "a"))) {
                        tm = time(0);
                        p = ctime(&tm);

                        /* skip the newline */
                        while (*p)
                                fputc(*p != '\n' ? *p : '\t', note), p++;

                        for (i = 1; i < argc; i++)
                                fprintf(note, "%s%c", argv[i], 1 + i - argc ? ' ' : '\n');
                } else {
                        perror(homedir);
                        return EXIT_FAILURE;
                }
        }

        if (note)
                fclose(note);
        free(homedir);

        return EXIT_SUCCESS;
}

