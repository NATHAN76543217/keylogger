#include "keymap.h"

static int		is_mod_press(t_keylogger *klg)
{
	switch (klg->event.code)
	{
		case SHIFT_L:
			klg->mod.shift = 1;
            dprintf(1, "SHIFT TRUE");
			break;
		case SHIFT_R:
			klg->mod.shift = 1;
			break;
		case CAPS_LOCK:
			klg->mod.capslock = 1;
		case CTRL_L:
			klg->mod.ctrl = 1;
			break;
		case CTRL_R:
			klg->mod.ctrl = 1;
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
            dprintf(1, "SHIFT FALSE");
			break;
		case SHIFT_R:
			klg->mod.shift = 0;
			break;
		case CAPS_LOCK:
			klg->mod.capslock = 0;
		case CTRL_L:
			klg->mod.ctrl = 0;
			break;
		case CTRL_R:
			klg->mod.ctrl = 0;
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