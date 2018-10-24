#include <stdio.h>

int main(void)
{
    char filename[FILENAME_MAX];
    FILE *fp;
    int c;

    printf("Input a file name.\n");
    gets(filename);
    
    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("No file");
        return -1;
    }

    while ((c = fgetc(fp)) != EOF) {
        putchar(c);
    }
    fclose(fp);
    return 0;
}
