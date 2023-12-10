#include "shell.h"
/**
 * builtin_shell - finds a builtin command
 * @node: argument struct
 * Return: -1 if error 0 on success -2 if signal ends
 *			
*/
int builtin_shell(node_t *node)
{
	int index;
       	int shellbuiltin = -1;
	builtin_ssh builtinshell[] = {
		{"exit", shell_exit},
		{"env", shell_env},
		{"help", shell_help},
		{"history", shell_history},
		{"setenv", shell_setenv},
		{"unsetenv", shell_unsetenv},
		{"cd", shell_cd},
		{"alias", shell_alias},
		{NULL, NULL}
	};

	for (index = 0; builtinshell[index].type; index++)
		if (str_cmp(node->argv[0], builtinshell[index].type) == 0)
		{
			node->err_num++;
			shellbuiltin = builtinshell[index].func(node);
			break;
		}
	return (shellbuiltin);
}

