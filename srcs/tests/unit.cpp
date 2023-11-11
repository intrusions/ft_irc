#include "unit.hpp"
#include "color.hpp"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>
#ifdef __linux__
#include <wait.h>
#endif

bool declare_test(bool (* test)(void), const char *title)
{
	fprintf(stderr, " running: %s%35s%s -> ", YEL, title, CRESET);
	int	ret;

	clock_t start_time = clock();
	pid_t pid = fork();
	if (pid == -1) assert(0 && "Internal error");

	else if (pid == 0) {
	
		// int original_stdout = dup(fileno(stdout));
  	// int original_stderr = dup(fileno(stderr));
		// (void)freopen("/dev/null", "w", stdout);
		// (void)freopen("/dev/null", "w", stderr);

		alarm(TIMEOUT_LIMIT);
		if (test())
			exit(0);
		exit(1);

		// (void)fflush(stdout);
		// (void)fflush(stderr);
		// (void)dup2(original_stdout, fileno(stdout));
		// (void)dup2(original_stderr, fileno(stderr));
		// (void)close(original_stdout); 
		// (void)close(original_stderr);

	}
	while (waitpid(pid, &ret, 0) != -1)
		continue ;

	clock_t end_time = clock();
	double execution_time_ms = (double)(end_time - start_time) * 1000 / CLOCKS_PER_SEC;

	if (WEXITSTATUS(ret))
		goto test_ko;

	if (WIFSIGNALED(ret)) {
		fprintf(stderr, "SIGNAL %s, ", strsignal(WTERMSIG(ret)));
		goto test_ko;
	}

	__xre_specs__.passed++;
	fprintf(stderr, "(%f ms) " BGRN "OK %s\n", execution_time_ms, CRESET);
	return (true);

test_ko:
	__xre_specs__.failed++;
	fprintf(stderr, "(%f ms) " BRED "KO %s\n", execution_time_ms, CRESET);
	return (false);
}
