#ifndef SHELL_H_
#define SHELL_H_

#define FLAG_CHAIN 3
#define BUFF_READ 1024
#define BUFF_WRITE 1024
#define FLUSH_SIZE -1
#define FLAG_AND 2
#define NORM 0
#define FLAG_OR	1
#define MAJUSCLE 1
#define MINUSCLE 2
#include <sys/types.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#define GET_LINE 0
#define STR_TOK 0


extern char **environ;
#define FILE_HISTORY ".simple_shell"
#define FILE_HISTORY_SIZE 4096

#define NODE_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL,\
	NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


/**
 * struct singly_string - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct singly_string
{
	int num;
	char *str;
	struct singly_string *next;
} list_t;

/**
 * info_node – all arguments passed into our shell
 * function, including pointer and prototype for struct
 * @arg: all arguments such as strings in getline
 * @argv: all the arrays of strings generated from arguments string in getline
 * @path: the path of our program current command
 * @count_flag_line: if on count this line of input
 * @progName: the program filename
 * @env: linked list local copy of environ
 * @argc: the argument counts
 * @err_num: the error count
 * @err_exit: our exit
 * @fd_read: shell file description
 * @history_line: the history line number count
 * @ch_env: function tochannge our shell environ
 * @status: reveals command line status
 * @buff_cmd_lin: command line buffer size
 * @buff_cmdline_type: Command line _type
 * @environ: shell environ
 * @history: command line history
 * @alias: shell alias
 */
typedef struct info_node
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int err_num;
	int err_exit;
	int count_flag_line;
	char *ProgName;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int ch_env;
	int status;
	char **buff_cmd_line;
	int buff_cmdline_type;
	int fd_read;
	int histcount;
} node_t;

/**
 *struct shell_builtin - contains a builtin string and related function
 *@type: builtin commanline execute lines
 *@func: shell_builtin function
 */
typedef struct shell_builtin
{
        char *type;
        int (*func)(node_t *);
} builtin_ssh;
ssize_t input_buf(node_t *, char **, size_t *);

int simple_shell(node_t *, char **);
int shell_loop(char **);
list_t start_here(node_t *, char *, char);
char *start_ptr(const char *, const char *);
int builtin_shell(node_t *);
void command_path(node_t *);
void handle_path(node_t *);
int command_line(node_t *, char *);
char *chars_double(char *, int, int);
char *find_cmd_path(node_t *, char *, char *);
void err_writes(char *);
int err_write(char);
int write_fd(char c, int);
int writes_fd(char *str, int);
void _writes(char *);
int f_printf(int, int);
int _write(char);
int str_len(char *);
int str_cmp(char *, char *);
char *str_cat(char *, char *);
char *strn_cpy(char *, char *, int);
char *strn_cat(char *, char *, int);
char *str_cpy(char *, char *);
char *str_up(const char *);
char *str_chr(char *, char);
char *mem_set(char *, char, unsigned int);
void buff_free(char **);
void *re_allocate(void *, unsigned int, unsigned int);
int _free(void **);
int err_atoi(char *);
void error_(node_t *, char *);
int print_decimal(int, int);
char *convert_num (long int, int, int);
void comment(char *);
int shell_alias(node_t *);
int shell_exit(node_t *);
int shell_cd(node_t *);
int shell_help(node_t *);
int shell_history(node_t *);
char *history_file(node_t *node);
int write_history(node_t *node);
int read_history(node_t *node);
int history_list(node_t *, char *, int);
int history_replace(node_t *node);
char *history_file(node_t *node);

void clear_node(node_t *);
void set_node(node_t *, char **);
void free_node(node_t *, int);
char *get_env(node_t *, const char *);
int shell_env(node_t *);
int shell_setenv(node_t *);
int shell_unsetenv(node_t *);
int manage_env(node_t *);
char **environ_init(node_t *);
int _unsetenv(node_t *, char *);
int _setenv(node_t *, char *, char *);
ssize_t get_input(node_t *);
int get_line(node_t *, char **, size_t *);
void handle_sign (int);
list_t *add_node(list_t **, const char *, int);
list_t *node_end(list_t **, const char *, int);
size_t print_list(const list_t *);
int clear_index(list_t **, unsigned int);
void free_node_list(list_t **);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_node_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
int chain_link(node_t *, char *, size_t *);
void chain_init(node_t *, char *, size_t *, size_t, size_t);
int alias_(node_t *);
int Var(node_t *);
int var_string(char **, char *);
char **strtow(char *, char *);
char **strtow2(char *, char);
int interactive(node_t *);
int delim(char, char *);
int is_alpha(int);
int atoi_(char *);

#endif

