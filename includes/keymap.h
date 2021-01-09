#ifndef KEYMAP_H
# define KEYMAP_H

#include "keylogger.h"
# define XOFFSET 8
# define SHIFT_L 0x32 - XOFFSET
# define SHIFT_R 0x3e - XOFFSET
# define CAPS_LOCK 0x42 - XOFFSET
# define CTRL_L 0x25 - XOFFSET
# define CTRL_R 0x69 - XOFFSET
# define ALT_L 0x40 - XOFFSET
# define ALT_R 0x6C - XOFFSET
# define ALT_META 0xcd - XOFFSET
# define NUM_LOCK 0x4d - XOFFSET
# define SUPER_L 0x85 - XOFFSET

int     setKeyMap(t_keylogger* klg, char *s);
void    printKeyMap(t_keylogger *klg);
int		is_mod_key(t_keylogger *klg);


#endif //KEYMAP_H