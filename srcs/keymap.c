#include "keymap.h"

static char *getNextKey(char *keys, int ndx)
{
	char	*key;
	int		i;
	int		size;

	i = 0;
	while (keys[i] != '\0')
	{
		if (ndx == 0)
			break;
		else if (keys[i] == ' ')
		{
			ndx--;
		}
		i++;
	}
	size = lentochar(&(keys[i]), ' ') + 1;
	if ((key = malloc(sizeof(char) * size)) == NULL)
		return NULL;
	ft_strncpy(key, &(keys[i]), size);
	return key;
}
static int	splitKey(t_keylogger *klg, int line, char *keys)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if ((klg->keymap[line][i] = getNextKey(keys, i)) == NULL)
			return ERROR;
		i++;
	}
	dprintf(1, "code: %d key: %s %s %s %s %s %s %s %s\n", (int)klg->event.code, klg->keymap[line][0], klg->keymap[line][1], klg->keymap[line][2],klg->keymap[line][3],klg->keymap[line][4], klg->keymap[line][5], klg->keymap[line][6], klg->keymap[line][7]);

	return SUCCESS;
}
int		setKeyMap(t_keylogger* klg, char *s)
{
	int     i;
	int     line;
	int		ndx;
	char	*tmp;

	line = 0;
	i = 0;
	while (s[i] != '\0')
	{
		ndx = lentochar(&(s[i]), '|');
		if ((tmp = malloc(sizeof(char) * ndx)) == NULL)
			return ERROR;
		ft_strncpy(tmp, &s[i], ndx);
		if (splitKey(klg, line, tmp) == ERROR)
			return ERROR;
		i += ndx + 1;
		line++;
		free(tmp);
	}
	return SUCCESS;
}

void	printKeyMap(t_keylogger *klg)
{
	int i;
	int x;


	i = 0;
	x = 0;
	while (i < 256)
	{
		while (x < 8)
		{
			ft_putstr(klg->keymap[i][x]);
			x++;
		}
		ft_putchar('\n');
		i++;
	}
	return ;
}
