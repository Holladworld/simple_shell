#include "shell.h"

/**
 * main – simple shell starting point
 * @agc: argument count
 * @agv: argument  vector
 *
 * Return: 1 if error 0 on success.
 */
int main(int agc, char **agv)
{
	node_t node[] = { NODE_INIT };
	int shell_file = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (shell_file)
		: "r" (shell_file));

	if (agc == 2)
	{
		shell_file = open(agv[1], O_RDONLY);
		if (shell_file == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				err_writes(agv[0]);
				err_writes (": 0: not found ");
				err_writes (agv[1]);
				err_write('\n');
				err_write(FLUSH_SIZE);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		node->fd_read = shell_file;

	}
	manage_env(node);
	read_history(node);
	simple_shell(node, agv);
	return (EXIT_SUCCESS);
}

/**
 * simple_shell – function to create simple shell
 * @node: the parameter struct
 * @agv: main argument vector
 *
 * Return: 1 if error 0 on success
 */
int simple_shell(node_t *node, char **agv)
{
	ssize_t index = 0;
	int shellbuiltin = 0;

	while (index != -1 && shellbuiltin != -2)
	{
		clear_node(node);
		if (interactive(node))
			_writes("$ ");
		err_write(FLUSH_SIZE);
		index = get_input(node);
		if (index != -1)
		{
			set_node(node, agv);
			shellbuiltin = builtin_shell(node);
			if (shellbuiltin == -1)
				command_path(node);
		}
		else if (interactive(node))
			_write('\n');
		free_node(node, 0);
	}
	write_history(node);
	free_node(node, 1);
	if (!interactive(node) && node->status)
		exit(node->status);
	if (shellbuiltin == -2)
	{
		if (node->err_exit == -1)
			exit(node->status);
		exit(node->err_exit);
	}
	return (shellbuiltin);
}
