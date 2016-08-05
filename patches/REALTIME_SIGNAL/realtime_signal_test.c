#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <errno.h>

static int signals[] = {
	SIGINT, SIGRTMIN + 1, SIGINT, SIGRTMIN + 0, SIGRTMIN + 2,
	SIGQUIT, SIGRTMIN + 1
};
#ifdef __arraycount
#define CNT	__arraycount(signals)
#else
#define CNT	(sizeof(signals) / sizeof(signals[0]))
#endif

static sig_atomic_t count = 0;
static int delivered[CNT];

static void
myhandler(int signo, siginfo_t *info, void *context) {
	printf("Inside Handler = %d\n", signo);
	delivered[count++] = signo;
}

static int
compare(const void *p1, const void *p2) {
	return *(const int *)p2 - *(const int *)p1;
}
/*
 * given a array of signals to be delivered in tosend of size len
 * place in ordered the signals to be delivered in delivery order
 * and return the number of signals that should be delivered
 */
static size_t
sigorder(int *ordered, const int *tosend, size_t len)
{
	/* copy tosend into ordered */
	/* sort ordered in descending order */
	/* eliminate dups for signals < SIGRTMIN */
	/* return count of signals */
	int tmp[CNT];
	int i, ret = 0;
	for (i = 0; i<CNT; i++) tmp[i] = tosend[i];
	qsort(tmp, CNT, sizeof(int), compare);
	for (i = 0; i<CNT; i++) {
		if (tmp[i] >= SIGRTMIN) {
			ordered[ret] = tmp[i];
			ret += 1;
		} else {
			if (i > 0 && ordered[ret-1] == tmp[i]) continue;
			ordered[ret] = tmp[i];
			ret += 1;
		}
	}
	return ret;
}

int
main(void)
{
	pid_t pid;
	union sigval value;
	struct sigaction act;
	int ordered[CNT];
	size_t ndelivered;

	ndelivered = sigorder(ordered, signals, CNT);

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = myhandler;
	sigemptyset(&act.sa_mask);
	for (size_t i = 0; i < CNT; i++)
		if (sigaction(signals[i], &act, NULL) == -1)
			err(EXIT_FAILURE, "sigaction");

	value.sival_int = 0;
	pid = getpid();

	sigset_t mask, orig;
	sigemptyset(&mask);
	for (size_t i = 0; i < CNT; i++)
		sigaddset(&mask, signals[i]);

	if (sigprocmask(SIG_BLOCK, &mask, &orig) == -1)
		err(EXIT_FAILURE, "sigprocmask/BLOCK");
	
	for (size_t i = 0; i < CNT; i++)
		if (sigqueue(pid, signals[i], value) == -1)
			err(EXIT_FAILURE, "sigqueue");
	
	if (sigprocmask(SIG_UNBLOCK, &mask, &orig) == -1)
		err(EXIT_FAILURE, "sigprocmask/UNBLOCK");
	sleep(3);
	if ((size_t)count != ndelivered)
		errx(EXIT_FAILURE, "count %zu != ndelivered %zu",
		    (size_t)count, ndelivered);
	for (size_t i = 0; i < ndelivered; i++)
		if (ordered[i] != delivered[i])
			errx(EXIT_FAILURE, "%zu: ordered %d != delivered %d",
			    i, ordered[i], delivered[i]);
	return 0;
}
