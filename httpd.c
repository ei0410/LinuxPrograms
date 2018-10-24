#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// prototype
static void log_exit(char *fmt, ...);
static void* xmalloc(size_t sz);

// main
int main(int argc, char *argv[])
{
	int *p;
	p = xmalloc(1024);

	printf("%p\n", p);

	return 0;
}

// output log and error
static void log_exit(char *fmt, ...)
{
	/*
		va_list ap;
		va_start(ap, fmt);
		< code with ap >
		va_end(ap);
	*/
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fputc('\n', stderr);
	va_end(ap);
	exit(1);
}

// memories
static void* xmalloc(size_t sz)
{
	void *p;

	p = malloc(sz);
	if (!p) log_exit("failed to allocate memory");
	return p;
}
