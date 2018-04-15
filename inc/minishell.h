/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:50:54 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/15 02:36:44 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "functions.h"
# include "parse.h"
# include "libft.h"
# include "libftprintf.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>
# include <signal.h>
# include <dirent.h>

typedef struct		s_av
{
	char			*in;
	char			*out;
	char			*key;
	char			*val;
	char			**argv;
}					t_av;

typedef struct		s_process
{
	char			**argv;
	char			**envp;
	pid_t			pid;
	int				exit_code;
	int				status;
	int				fd[2];
}					t_process;

typedef struct		s_exec
{
	char			*cmd;
	struct s_exec	*next;
}					t_exec;

typedef struct		s_shell
{
	struct termios	t_original;
	struct termios	t_custom;
	t_exec			*exec;
	t_exec			*last_exec;
	char			keycode[10];
	char			*buffer;
	char			*partial_input;
	char			*carriage_return;
	char			*clear_down;
	char			*clear_till_eol;
	char			*clear_all;
	char			*cursor_move_left;
	char			*cursor_move_right;
	char			*cursor_move_down;
	char			*cursor_move_up;
	char			**child_argv;
	char			**history;
	char			**argv;
	char			**envp;
	size_t			bufsize;
	size_t			input_size;
	size_t			buf_i;
	size_t			cursor;
	int				exit_code;
	int				argc;
	int				history_count;
	int				history_i;
	int				custom_terminal;
	int				state;
}					t_shell;

t_shell	*g_sh;

# define SHELL_PROMPT		"$> "
# define SHELL_NAME			"minishell"
# define PAGE_SIZE			4096
# define E_NOMEM			"out of memory"
# define E_READFAIL			"read() failed"
# define E_GNLFAIL			"get_next_line() failed"
# define E_CWDFAIL			"getcwd() failed"
# define E_NOVARIABLE		"No %s variable set.\n"
# define E_CHDIRFAIL		"chdir() failed\n"
# define E_ALNUM			"Variable name must be alphanumeric characters."
# define E_TOOMANY			"Too many arguments."
# define E_TOOMANY2			"%s: Too many arguments.\n"
# define E_TOOFEW			"Too few arguments."
# define E_LETTER			"Variable name must begin with a letter."
# define E_NOTFOUND			"%s: Command not found.\n"
# define E_FORK				"fork() failed"
# define UNDEFINED_VARIABLE	"%s: Undefined variable.\n"
# define UNMATCHED_QUOTE	"Unmatched %c.\n"
# define STRONG_QUOTE		0x27
# define WEAK_QUOTE			0x22
# define BACKSLASH			0x5c
# define COMMAND_SEPARATOR	';'
# define STATE_READ			1
# define STATE_EXEC			2
# define TAB_SIZE			8
# define EMPTY_STRING		""
# define DOLLAR_SIGN		'$'
# define NUM_BUILTINS		7
# define NUM_SPECIAL_KEYS	11
# define HISTORY_FILE		".minishell_history"
# define KEY_UP_ARROW		"\e[A"
# define KEY_DOWN_ARROW		"\e[B"
# define KEY_LEFT_ARROW		"\e[D"
# define KEY_RIGHT_ARROW	"\e[C"
# define KEY_BACKSPACE		"\x7f"
# define KEY_DELETE			"\e[3~"
# define KEY_CTRL_A			"\x01"
# define KEY_CTRL_E			"\x05"
# define KEY_CTRL_K			"\x0b"
# define KEY_CTRL_L			"\x0c"
# define KEY_TAB			"\x09"

#endif