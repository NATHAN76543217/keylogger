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
	return SUCCESS;
}
int		setKeyMap(t_keylogger* klg)
{
	int     i;
	int     line;
	int		ndx;
	char	*tmp;

	line = 0;
	i = 0;
	while (klg->rawMap[i] != '\0')
	{
		ndx = lentochar(&(klg->rawMap[i]), '|');
		if ((tmp = malloc(sizeof(char) * ndx)) == NULL)
			return ERROR;
		ft_strncpy(tmp, &(klg->rawMap[i]), ndx);
		if (splitKey(klg, line, tmp) == ERROR)
			return ERROR;
		i += ndx + 1;
		line++;
		free(tmp);
	}
	return SUCCESS;
}
