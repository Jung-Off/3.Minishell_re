/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:32:13 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/12/02 18:23:00 by jji              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h> //getenv
# include <stdio.h> //readline
# include <signal.h> //signal, kill
# include <term.h> // tget~
# include <termios.h> // tcget~
# include <dirent.h> // ~dir
# include <sys/stat.h> // ~stat
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/ioctl.h>

# include "../libft/libft.h"

# define TRUE 1
# define FALSE 0

# define READ 0
# define WRITE 1

# define NONE 0
# define SINGLE 1
# define DOUBLE 2

# define REDIRECT_INPUT_SINGLE 1
# define REDIRECT_INPUT_DOUBLE 2
# define REDIRECT_OUTPUT_SINGLE 3
# define REDIRECT_OUTPUT_DOUBLE 4

# define QUOTE "\0\'\""

# define MAXSIZE		1024

# define TURN_ON	1
# define TURN_OFF	0

# define OMIT 1
# define N_OMIT 0

typedef int		t_bool;

typedef struct s_redirect
{
	int					type;
	char				*file;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_cmd
{
	char				**argv;
	struct s_redirect	*redirect;
	struct s_cmd		*next;
	int					fd[2];
}						t_cmd;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
	int					idx;
	int					env_flag;
}						t_env;

// error.c
int			error_handler(char *err_msg);
t_bool		error_check(t_cmd *cmd);

// execute.c
int			execute(t_cmd *cmd, char **envp, int fd_in);

// parse_command.c
int			split_redirect(char **input);
int			split_command(char **res, char **cmd_str);
int			parse_command(t_cmd **cmd, char *cmd_str);

// parse_line.c
int			pass_quotes(char **input);
int			split_line(char **cmd, char **line);
int			parse_line(t_cmd **cmd_lst, char *line, t_env *env);

// replace.c
int			replace(t_cmd *cmd, t_env *env);

// utils_cmd.c
t_cmd		*create_cmd(void);
void		cmd_add_back(t_cmd **lst, t_cmd *new);
char		**cmd_argv_add_back(char **old_cmd, char *input);
void		cmd_clear(t_cmd **lst);

// utils_redir.c
t_redirect	*create_redir(char *line);
void		redir_add_back(t_redirect **lst, t_redirect *new);
void		redir_clear(t_redirect **lst);

//exe_env.c
char		**find_envp_path(void);
void		env_split(t_env *lst, char *env);
void		print_env(t_env *env_lst);
void		make_envlst(char **envp, t_env **env_lst);

//exe_cd.c
void		exe_cd(t_cmd *cmd, t_env *env_lst);

//exe_echo.c
int			echo_option_chk(char *option);
void		exe_echo(t_cmd *cmd);

//exe_export.c
void		before_print_export(t_env *env_lst);
void		print_export(t_env *env_lst);
void		exe_export(t_env **env_lst, t_cmd *cmd);
int			env_rank(t_env *env_lst, t_env *move_lst);

//add_export.c
int			init_envlst(t_env *env_lst, t_env *lst);
int			duplicate_search(t_env *env_lst, t_env *lst);
void		export_split(t_env *lst, char *argv);
int			judge_cmd(char *cmd_option);
int			add_export(t_env **env_lst, char *cmd);

//exe_unset.c
void		exe_unset(t_env **env_lst, t_cmd *cmd);

//exe_pwd.c
void		exe_pwd(void);

//list.c
void		create_list(t_env **lst);
void		add_node(t_env *add_lst, t_env **env_lst);

//signal.c
void		emit_signal(int sig);
void		blocking_back_slash(int sig);
void		blocking_ctrl_c(int sig);
void		sig_restart(int sig);
void		switch_echoctl(int sig);

//redirect.c
int			redirect_change(t_redirect *redirect, t_env *env_lst);

//exe_process.c
void		exe_process(t_cmd **cmd, char **env, t_env **env_list);

//builtin.c
int			is_built(char *cmd);
void		exe_builtin(t_cmd *cmd, t_env **env_lst);

//exe_exit.c
int			exit_function(char *line);
void		exe_exit(t_cmd *cmd);

//main.c
int			cmd_num(t_cmd *cmd);
char		*exe_parse(char **env, char *command_split);
void		init_argument(t_cmd **cmd, t_env **env_lst, int argc, char **argv);

#endif
