#include "shell.h"
/**
 * _write - write character to stdout
 * @c: character
 * REturn: 1 on sucess
 */
int _write(char c)
{
	static int ag;
	static char size[BUFF_WRITE];

	if (c == FLUSH_SIZE || ag >= BUFF_WRITE)
	{
		write(1, size, ag);
		ag = 0;
	}
	if (c != FLUSH_SIZE)
		size[ag++] = c;
	return (1);
}

/**
 * _writes - write string to stdio
 * @ag: string
 * REturn: void
 */
void _writes(char *ag)
{
	int str = 0;

	if (!ag)
		return;
	while (ag[str] != '\0')
	{
		_write(ag[str]);
		str++;
	}
}
