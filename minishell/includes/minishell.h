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

int				g_exit_code;

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

typedef struct s_data
{
	int					idx;
	char				*new;
	int					fd_in;
	int					fd0;
	int					fd1;
}						t_data;

typedef struct s_exe
{
	pid_t				pid;
	int					in;
	int					out;
	int					status;
	char				*env_path;
	int					n;
}						t_exe;

typedef struct s_cd
{
	int					result;
	char				*home;
	char				*path;
	char				*joins;
}						t_cd;

typedef struct s_unset
{
	t_env	*prev_env;
	t_env	*m;
	t_env	*first;
	t_env	*temp;
	int		i;
}				t_unset;

//add_export.c

void		export_put_value(char **export_oneline, t_env *lst, char *argv);
int			export_split(t_env *lst, char *argv);
int			judge_cmd(char *cmd_option);
int			add_export(t_env **env_lst, char *cmd);

//builtin.c
int			is_built(char *cmd);
void		exe_builtin(t_cmd *cmd, t_env **env_lst);

// error.c
int			error_handler(char *err_msg);
t_bool		error_check(t_cmd *cmd);
void		ft_error(int is_exit, char *cmd, char *err_msg, int exit_code);
void		parse_error(int is_exit, int exit_code);

//exe_cd.c
char		*search_home(t_env *env_lst);
void		exe_cd_space(t_env *env_lst, t_cd cd);
void		init_cd(t_cd *cd);
void		exe_cd(t_cmd *cmd, t_env *env_lst);
void		go_to_path(t_cmd *cmd, t_cd cd);

//exe_echo.c
int			echo_option_chk(char *option);
void		exe_echo(t_cmd *cmd);

//exe_env.c
char		**find_envp_path(void);
void		env_split(t_env *lst, char *env);
void		print_env(t_env *env_lst, t_cmd *cmd);
void		make_envlst(char **envp, t_env **env_lst);
void		free_double(char **env_oneline);

//exe_exit.c
void		exit_code_change(t_cmd *cmd);
void		exe_exit(t_cmd *cmd);
void		exit_utils(int exit_exe, char *err_msg, int exit_code);
void		just_exit(void);

//exe_export.c
void		sort_export(t_env *env_lst);
void		before_print_export(t_env *env_lst);
void		print_export(t_env *env_lst);
void		exe_export(t_env **env_lst, t_cmd *cmd);
int			env_rank(t_env *env_lst, t_env *move_lst);

//exe_process_utils.c
void		init_exe(t_exe *exe_data, t_cmd *cmd);
void		redirect_signal(t_cmd **cmd);
int			cmd_ok(char **env, char *cmd);

//exe_process.c
void		path_find(t_cmd **cmd, char **env);
void		exe_process(t_cmd **cmd, char **env, t_env **env_list);
void		child_process(t_cmd **cmd, char **env, \
		t_env **env_list, t_exe exe_data);
void		pipe_setting(t_cmd **cmd, t_exe *exe_data);
void		ready_next_process(t_cmd **cmd, t_exe *exe_data);

//exe_pwd.c
void		exe_pwd(void);

//exe_unset.c
void		init_unset(t_unset *unset, t_env *env_lst);
t_env		*exe_unset(t_env **env_lst, t_cmd *cmd);
void		first_unset(t_unset *unset, t_env **env_lst);
void		etc_unset(t_unset *unset);

//list.c
void		create_list(t_env **lst);
void		add_node(t_env *add_lst, t_env **env_lst);

//main.c
void		init_argument(t_cmd **cmd, t_env **env_lst, int argc, char **argv);
void		main_clear(char **line, t_cmd **cmd);
void		free_env(t_env **env_lst);

// parse_command.c
int			split_redirect(char **input);
int			split_command(char **res, char **cmd_str);
int			parse_command(t_cmd **cmd, char *cmd_str);

// parse_line.c
int			pass_quotes(char **input);
int			split_line(char **cmd, char **line);
int			parse_line(t_cmd **cmd_lst, char *line, t_env *env);

//redirect_utils.c
void		init_data(t_data *data);
void		file_error(t_redirect *redirect);
int			input_file_check(t_redirect *redirect, t_env *env_lst);

//redirect.c
void		redirect_input_single(t_redirect *redirect, t_data data);
void		redircet_input_double(t_redirect *redir, t_data data);
void		redirect_ouput_single(t_redirect *redirect, t_data data);
void		redirect_output_double(t_redirect *redirect, t_data data);
int			redirect_change(t_redirect *redirect, t_env *env_lst);

// replace.c
int			replace(t_cmd *cmd, t_env *env);

//search_export.c
void		envlst_change(t_env *env_lst, t_env *lst);
int			init_envlst(t_env *env_lst, t_env *lst);
int			duplicate_search(t_env *env_lst, t_env *lst);

//signal.c
void		emit_signal(int sig);
void		blocking_back_slash(int sig);
void		blocking_ctrl_c(int sig);
void		sig_restart(int sig);
void		switch_echoctl(int sig);

// utils_cmd.c
t_cmd		*create_cmd(void);
void		cmd_add_back(t_cmd **lst, t_cmd *new);
char		**cmd_argv_add_back(char **old_cmd, char *input);
void		cmd_clear(t_cmd **lst);

// utils_redir.c
t_redirect	*create_redir(char *line);
void		redir_add_back(t_redirect **lst, t_redirect *new);
void		redir_clear(t_redirect **lst);

//main.c
int			cmd_num(t_cmd *cmd);
char		*exe_parse(char **env, char *command_split);

#endif
