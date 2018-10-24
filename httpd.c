#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <signal.h>
#include <errno.h>

// structures
struct HTTPHeaderField {
	char *name;
	char *value;
	struct HTTPHeaderField *next;
};

struct HTTPRequest {
	int protocol_minor_version;
	char *method;
	char *path;
	struct HTTPHeaderField *header;
	char *body;
	long length;
};

// prototypes
static void log_exit(char *fmt, ...);
static void* xmalloc(size_t sz);
static void signal_exit(int sig);
static void trap_signal(int sig, sighandler_t handler);
static void install_signal_handlers(void);
static void service(FILE *in, FILE *out, char *docroot);
static void free_request(struct HTTPRequest *req);

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

// read, response and free
static void service(FILE *in, FILE *out, char *docroot)
{
	struct HTTPRequest *req;

	//req = read_request(in);
	//respond_to(req, out, docroot);
	free_request(req);
}

// free all members
static void free_request(struct HTTPRequest *req)
{
	struct HTTPHeaderField *h, *head;

	head = req->header;
	while (head) {
		h = head;
		head = head->next;
		free(h->name);
		free(h->value);
		free(h);
	}
	free(req->method);
	free(req->path);
	free(req->body);
	free(req);
}

// main
int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <docroot>\n", argv[0]);
		exit(1);
	}
	install_signal_handlers();
	service(stdin, stdout, argv[1]);
	exit(0);
}
