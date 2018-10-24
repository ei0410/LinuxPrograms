#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <signal.h>
#include <errno.h>

// prototype
static void log_exit(char *fmt, ...);
static void* xmalloc(size_t sz);
static void install_signal_handlers(void);
static void install_signal_handlers(void);
static void trap_signal(int sig, sighandler_t handler);
static void signal_exit(int sig);

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

// signal process
static void install_signal_handlers(void)
{
	trap_signal(SIGPIPE, signal_exit);
}

static void trap_signal(int sig, sighandler_t handler)
{
	struct sigaction act;

	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	if (sigaction(sig, &act, NULL) < 0)
		log_exit("sigaction() failed: %s", strerror(errno));
}

static void signal_exit(int sig)
{
	log_exit("exit by signal %d", sig);
}
