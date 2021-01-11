#include "keylogger.h"

void    SIGhandler(int signal)
{
	t_keylogger *klg;

	klg = getKlg();
	dprintf(klg->logFD, "SIGNAL: %d\n", signal);
	clean_quit(klg, signal);
}

void    signal_handle(void)
{
    signal(SIGINT, SIGhandler);
	signal(SIGKILL, SIGhandler);
	signal(SIGTERM, SIGhandler);
}