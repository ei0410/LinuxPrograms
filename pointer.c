#include <stdio.h>
/*
void swap(int *xp, int *yp)
{
    int temp;

    temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int main(void)
{
    int x, y;

    x = 4;
    y = 5;

    printf("%d, %d\n", x, y);
    swap(&x, &y);
    printf("%d, %d\n", x, y);

    return 0;
}
*/

int main(void)
{
    int i;
    int *p;
    int a[10];

    p = &a[0];

    for (i = 0; i < 10; i++) {
        *p = i*i;
        printf("%d\n", *p);
        p++;
    }

    return 0;
}
