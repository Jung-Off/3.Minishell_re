/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:00:58 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/11/14 19:00:04 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    switch_echoctl(int sig)
{
    struct termios  conf;
    ioctl(ttyslot(), TIOCGETA, &conf);
    if (sig == TURN_OFF)
        conf.c_lflag &= ~(ECHOCTL);
    else if (sig == TURN_ON)
        conf.c_lflag |= ECHOCTL;
    ioctl(ttyslot(), TIOCSETA, &conf);
}

void    sig_restart(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		(void)sig;
	}
}
void    blocking_ctrl_c(int sig)
{
    write(STDOUT_FILENO, "\n", 1);
    (void)sig;
}
void    blocking_back_slash(int sig)
{
    ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
    (void)sig;
}

void    emit_signal(int sig)
{
    if (sig == 1)
    {
        signal(SIGINT, sig_restart);
        signal(SIGQUIT, SIG_IGN);
    }
    if (sig == 2)
    {
        switch_echoctl(TURN_ON);
        signal(SIGINT, blocking_ctrl_c);
        signal(SIGQUIT, blocking_back_slash);
    }
}

void	test_print(t_cmd *cmd, char *line)
{
	int	i;

	printf("%s\n", line);
	printf("--------------------\n");
	i = 1;
	while (cmd)
	{
		printf("%d\n", i++);
		while (*cmd->argv)
			printf("[%s]\n", *cmd->argv++);
		printf("redirect\n");
		while (cmd->redirect)
		{
			printf("[%d %s]\n", cmd->redirect->type, cmd->redirect->file);
			cmd->redirect = cmd->redirect->next;
		}
		printf("\n");
		cmd = cmd->next;
	}
}

char	**find_envp_path()
{
	char	**envp_path;
	char 	*path;

   	path = getenv("PATH");
	if(path == NULL)
		printf("Failed to get path\n");
	envp_path = ft_split(path, ':');

	return (envp_path);
}

int exit_function(char *line)
{
	if (ft_strncmp(line, "exit", 4) == 0 && ft_strlen(line) == 4)
	{	
		//printf("%s\n", line);
		free(line);
		exit (1);
	}
	return (0);
}

int cmd_num(t_cmd *cmd)
{
	int i = 0;
	
	while(cmd)
	{
		cmd = cmd->next;
		++i;
	}
	return (i);
}

char *exe_parse(char **env, char *command_split)
{
	int i;
	char *env_path;
	//char *command_path;
	char *add_slash;

	struct stat buf;

	i = 0;
	while(env[i])
	{
		env_path = ft_strdup(env[i]);
		//free(env[i]); //>> 빨리 없애버리고 싶었으나 명령어가 안들어오면 free된 것이라고 함
		add_slash = ft_strjoin(env_path, "/");
		free(env_path);
		env_path = ft_strjoin(add_slash, command_split);

		//printf("env_path :%s\n", env_path);
		if(stat(env_path, &buf) == 0)
		{
			//printf("여기가 출력이 안되는데 함수가 실행이 되네?");
			//printf("%s", env_path);
			return (env_path);
		}
		++i;
	}
	printf("not invalid command\n");
	return (0);
}


int exe_just(t_cmd *cmd_lst, char **env)
{
	char *env_path;
	int status;
	pid_t pid;
	static int i;

	env_path = exe_parse(env, cmd_lst->argv[0]);
	if (env_path == 0)
	{
		printf("명령어가 없어서 함수 나가는중\n");
		return (1);
	}

	pid = fork(); // 이함수 안쓰면 waitpid == -1 로 해서 error
	if (pid == 0)
	{
		// printf("pid %d", pid[i]);
		i++;	
		//printf(" --------자식\n");
			execve(env_path, cmd_lst->argv, NULL);
	}
	else
	{
		// printf("pid %d", pid);
		waitpid(pid, &status, 0);
	}
	
	return (1);
}

void exe_unset(t_env **env_lst, t_cmd *cmd)
{
	t_env *prev_env;
	t_env *move;
	(void)env_lst;
	(void)cmd;
	
	printf("%s %s\n", cmd->argv[0], cmd->argv[1]);

	prev_env = NULL;
	// prev_env->next = *env_lst;
	int i = 0;
	while (cmd->argv[i])
	{
		move = *env_lst;
	while (move)
	{	
		if (ft_strncmp(move->key, cmd->argv[i], ft_strlen(cmd->argv[i])) == 0
		&& ft_strncmp(move->key, cmd->argv[i], ft_strlen(move->key)) == 0)
		{
			printf("check : %s %s\n", move->key, move->value);
			if (prev_env == NULL)
			{
				printf("NULL ? %s %s\n", move->key, move->value);
				(*env_lst) = (*env_lst)->next;
				// prev_env = move->next;
			}
			else
			{
				printf("else : %s %s\n", move->key, move->value);
				prev_env->next = move->next;
			}
			// move->next = NULL;
			// free(move);
			break;
		}
		prev_env = move;
		move = move->next;
	}
		i++;
	}	
}

void exe_exit(t_cmd *cmd)
{
	if (cmd->argv[1])
	{
		write(1, cmd->argv[1], ft_strlen(cmd->argv[1]));
		write(1, "\n", 1);
	}
}

int is_built(char *cmd)
{
	if ((ft_strncmp((cmd), "pwd", 3) == 0 && ft_strlen(cmd) == 3)
	|| (ft_strncmp((cmd), "env", 3) == 0 && ft_strlen(cmd) == 3)
	|| (ft_strncmp((cmd), "export", 6) == 0 && ft_strlen(cmd) == 6)
	|| (ft_strncmp((cmd), "unset", 5) == 0 && ft_strlen(cmd) == 5)
	|| (ft_strncmp((cmd), "cd", 2) == 0 && ft_strlen(cmd) == 2)
	|| (ft_strncmp((cmd), "echo", 4) == 0 && ft_strlen(cmd) == 4)
	|| (ft_strncmp((cmd), "exit", 4) == 0 && ft_strlen(cmd) == 4))
		return (1);
	return (0);
}

void exe_builtin(t_cmd *cmd, t_env **env_lst)
{
	if (ft_strncmp((cmd->argv[0]), "pwd", 3) == 0 && ft_strlen(cmd->argv[0]) == 3)
		exe_pwd();
	else if (ft_strncmp((cmd->argv[0]), "env", 3) == 0 && ft_strlen(cmd->argv[0]) == 3)
		print_env(*env_lst);
	else if (ft_strncmp((cmd->argv[0]), "export", 6) == 0 && ft_strlen(cmd->argv[0]) == 6)
		exe_export(env_lst, cmd);
	else if (ft_strncmp((cmd->argv[0]), "unset", 5) == 0 && ft_strlen(cmd->argv[0]) == 5)
		exe_unset(env_lst, cmd);
	else if (ft_strncmp((cmd->argv[0]), "cd", 2) == 0 && ft_strlen(cmd->argv[0]) == 2)
		exe_cd(cmd, *env_lst);
	else if (ft_strncmp((cmd->argv[0]), "echo", 4) == 0 && ft_strlen(cmd->argv[0]) == 4)
		exe_echo(cmd);
	else if (ft_strncmp((cmd->argv[0]), "exit", 4) == 0 && ft_strlen(cmd->argv[0]) == 4)
		exe_exit(cmd);
}

void redirect_change(t_redirect *redirect)
{
	while(redirect)
	{
		if (redirect->type == REDIRECT_INPUT_SINGLE)
		{
			int fd0 = open(redirect->file, O_RDWR, 0644);
			dup2(fd0, STDIN_FILENO);
			close(fd0);
		}
		else if (redirect->type == REDIRECT_INPUT_DOUBLE) // <<
		{
			// tmp file init
			
			//printf("eof: %s\n", redirect->file);
			
			while(redirect)
			{
				int fd1 = open("./temp/tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);

				while(1)
				{
					// input readline
			// printf("here");
					char *new_input = readline("> ");

					// eof exit
					if (!ft_strncmp(new_input, redirect->file, ft_strlen(redirect->file)))
						break ;
					write(fd1, new_input, ft_strlen(new_input));
					write(fd1, "\n", 1);
				
					free(new_input);
					// write
				}
				redirect = redirect->next;
				close(fd1); //<< 
			}	
			int fd3 = open("./temp/tmp", O_RDWR, 0644);
			// printf("here");
			//ft_putnbr_fd(fd3, 1);
			dup2(fd3, STDIN_FILENO);
			//ft_putnbr_fd(fd3, 1); // 표준 출력으로 돌리기
			close(fd3);
			//ft_putnbr_fd(fd3, 1);
		}
		else if (redirect->type == REDIRECT_OUTPUT_SINGLE)
		{
			//write(1, "output\n", 7);
			int fd1 = open(redirect->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			dup2(fd1, STDOUT_FILENO);
			close(fd1);
		}
		else if (redirect->type == REDIRECT_OUTPUT_DOUBLE)
		{
			int fd1 = open(redirect->file, O_RDWR | O_CREAT | O_APPEND, 0644);
			dup2(fd1, STDOUT_FILENO);
			close(fd1);
		}
		redirect = redirect->next;
	}
}

void exe_process(t_cmd **cmd, char **env, t_env **env_list)
{
	pid_t pid;
	// int i = 0;
	int in = 0;
	int out = 1;
	char *env_path;
	int status;

	// if ((*cmd)->next == NULL)
	// {
	// 	exe_just(*cmd, env);
	// 	return ;
	// }

	//^C를 넣기 위함
	if (!(*cmd)->redirect) // cat grep
		emit_signal(2);
	int flag = cmd_num(*cmd);
	while (*cmd)
	{		
		if (is_built((*cmd)->argv[0]) && flag == 1 && !(*cmd)->redirect) //명령어가 하나이고, 명령어 길이가 1이다.
		{
			printf("only builtin\n");
			exe_builtin(*cmd, env_list);
			(*cmd) = (*cmd)->next;
		}
		else
		{
			//redirect
			//pipe 라인
			if ((*cmd)->next != NULL)		//다음이 있다.
			{
				printf("here pipe\n");
				pipe((*cmd)->fd);
				out = (*cmd)->fd[1];
			}
			env_path = exe_parse(env, (*cmd)->argv[0]);
			pid = fork();
			if (pid == 0)
			{
				if ((*cmd)->redirect > 0)
					redirect_change((*cmd)->redirect);
				//printf("cmd: %s\n", (*cmd)->argv[0]);
				if (in != 0) // 처음 빼고 , 파이프 있을 때
				{	
					dup2(in, 0);
					close(in);
				}
				if (out != 1 && (*cmd)->next != NULL) // 마지막에 빼고, 파이프 있을 때
				{
					dup2(out, 1);
					close(out);
				}
				//ft_putstr_fd("i am cat\n", 3);
				// func
				if (is_built((*cmd)->argv[0])) //내가 만든 함수
				{
					printf("here_is_built\n");
					exe_builtin(*cmd, env_list); //실행
					exit(0);					//종료
				}
				else
				{
					// cat
					// ft_putstr_fd("i am cat\n", 3);
					//printf("here_is_external\n");
					if (execve(env_path, (*cmd)->argv, NULL) == -1)
						perror("cmd not found");
				}
			}
			else if (pid > 0)
			{
				waitpid(pid, &status, 0);
			}
			// here !		//ls //ls | cat
			// printf("here_end\n");
			if ((*cmd)->next != NULL) //마지막이면 close 해주면 안됨 //이게 없으면 ls 하나일때 문제가 있음
				close(out); // 마지막일 때는 굳이 할 필요는 없는 듯?
			in = (*cmd)->fd[0]; //연결하는 과정은 있든 없든 상관없음
			//printf("here_end\n");
			(*cmd) = (*cmd)->next; //다음으로 넘기기
			// ++i;
		}
	}
	// printf("here\n");
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;
	char **env;

	(void)argc;
	(void)argv;
	cmd = NULL;
	t_env *env_lst = NULL;
	

	
	exe_env(envp, &env_lst);
	env = find_envp_path();


	while(1)
	{
		switch_echoctl(TURN_OFF);
		//^C을 끄기위함
		emit_signal(1);		
		line = readline("minishell$ ");
		if (!line)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			exit(EXIT_SUCCESS);
		}
		//exit_function(line); 기가막히게 문제가 생기네
		if (line)
		{
			if (parse_line(&cmd, line, env_lst))
				return (EXIT_FAILURE);
			if (ft_strlen(line) > 0)
			{
				//printf("%d\n", cmd->redirect->type);
				exe_process(&cmd, env, &env_lst);
				add_history (line);
			}
		}
		free(line);
		line = NULL;
		cmd_clear(&cmd);
	}
	return (EXIT_SUCCESS);
}
