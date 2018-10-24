#include <stdio.h>
#include <stdarg.h>

// prototype
static void log_exit(char *fmt, ...);

// main
int main(int argc, char *argv[])
{
	printf("hello\n");
	return 0;
}

// output log and error
static void log_exit(char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fputc('\n', stderr);
	va_end(ap);
	exit(1);
}
