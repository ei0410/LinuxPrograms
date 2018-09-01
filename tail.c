#include <stdio.h>
#include <stdlib.h>

static void do_tail(FILE *f, long nlines);
static void do_count(FILE *f, long nlines);

#define DEFAULT_N_LINES 10

int count = 0;

int main(int argc, char *argv[])
{
    long nlines = DEFAULT_N_LINES;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s n [file file...]\n", argv[0]);
        exit(1);
    }
    nlines = atol(argv[1]);
    if (argc == 2) {
        do_tail(stdin, nlines);
    } else {
        int i;
        
        for (i = 2; i < argc; i++) {
            FILE *f;
            f = fopen(argv[i], "r");
            do_count(f, nlines);

            if (!f) {
                perror(argv[i]);
                exit(1);
            }
            do_tail(f, nlines);
            fclose(f);
        }
    }
    exit(0);
}

static void do_tail(FILE *f, long nlines)
{
    int c;
    
    if (nlines <= 0) {
        return;
    }

    while ((c = getc(f)) != EOF) {
        if (putchar(c) < 0) {
            exit(1);
        }
        if (c == '\n') {
            nlines--;
            if (nlines == 0) {
                return;
            }
        }
    }
}

static void do_count(FILE *f, long nlines)
{
    int c;

    while ((c = getc(f)) != EOF) {
        if (c == '\n') {
            count++;
        }
    }
    printf("%d\n", count);
}
