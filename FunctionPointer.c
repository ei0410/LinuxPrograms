#include <stdio.h>

double f(double x) {
    return (x*x);
}

double g(double x) {
    return (x*x*x + x*x);
}

double trapezoid(double w1, double w2, double h) {
    return ((w1 + w2) * h / 2.0);
}

double daikei(double x1, double x2, int n, double (*fp)(double)) {
    int i;
    double s = 0.0;
    double step = (x2 - x1) / n;

    for (i = 0; i < n; i++) {
        s += trapezoid((*fp)(x1 + step*i), (*fp)(x1 + step*(i+1)), step);
    }

    return s;
}

int main(void) {
    int n;
    double x1, x2;

    printf("start:  ");
    scanf("%lf", &x1);
    printf("finish: ");
    scanf("%lf", &x2);
    printf("step:   ");
    scanf("%d", &n);

    printf("f = %.4f\n", daikei(x1, x2, n, f));
    printf("g = %.4f\n", daikei(x1, x2, n, g));

    return 0;
}
