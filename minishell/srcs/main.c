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

// void exe_main(t_cmd *cmd, char **env)
// {
// 	if (cmd->next == NULL)
// 	{
// 		exe_just(cmd, env);
// 		return ;
// 	}
// 	char *env_path;
// 	int status;
// 	pid_t pid1;

// 	//fd[1] write
// 	//fd[0] read
// 	int in = 0;
// 	int out = 1;
	
// 	env_path = exe_parse(env, cmd->argv[0]);

// 	pipe(cmd->fd);
// 	out = cmd->fd[1];

// 	pid1 = fork();	
// 	if(pid1 == 0)
// 	{
// 		if (in != 0)
// 		{
// 			dup2 (in, 0);
// 			close (in);
// 		}
// 		if (out != 1)
// 		{
// 			dup2 (out, 1);
// 			close (out);
// 		}
// 		// close(cmd->fd[0]);
// 		// dup2(cmd->fd[1], STDOUT_FILENO);
// 		// close(cmd->fd[1]);
// 		execve(env_path, cmd->argv, NULL);
// 	}
// 	else
// 	{
// 		// close(cmd->fd[0]);
// 		// close(cmd->fd[1]);
// 		waitpid(pid1, &status, 0);
// 	}
// 	close(cmd->fd[1]);
// 	in = cmd->fd[0];

// 	t_cmd *cmd_next = cmd->next;

// 	// printf("%s", *(cmd->argv));
// 	pid1 = fork();

// 	env_path = exe_parse(env, cmd->next->argv[0]);
// 	if(pid1 == 0)
// 	{	
// 		if (in != 0)
// 		{
// 			dup2 (in, 0);
// 			close (in);
// 		}
// 		if (out != 1)
// 		{
// 			dup2 (out, 1);
// 			close (out);
// 		}
// 		dprintf(1, "here\n");
// 		execve(env_path, cmd_next->argv, NULL);
// 	}
// 	else 
// 	{
// 		// dup2(fd_out, 1);
// 		waitpid(pid1, &status, 0);
// 	}
	
// }

// void exe_main(t_cmd *cmd, char **env)
// {

// 	if (cmd->next == NULL)
// 	{
// 		exe_just(cmd, env);
// 		return ;
// 	}
//     pid_t pid, wpid;
//     int status;
// 	char *env_path;
//     int in;
//     int out;
//     int fd[2];
//     in = 0;
//     out = 1;
	
//     while(cmd != NULL)
//     {
//         if (cmd->next != NULL)
//         {
//             pipe(fd);
//             out = fd[1];
//         }
// 		env_path = exe_parse(env, cmd->argv[0]);
//         pid = fork();
//         if (pid == -1)
//             exit(EXIT_FAILURE);
//         else if (pid == 0)
//         {
//             if (in != 0)
//             {
//                 dup2 (in, 0);
//                 close (in);
//             }
//             if (out != 1)
//             {
//                 dup2 (out, 1);
//                 close (out);
//             }
//             if (execve(env_path, cmd->argv, NULL) == -1)
//                 perror("Could not execve");
//             exit(EXIT_SUCCESS);
//         }
//         else if (pid > 0)
//         {
//             //do {
//                 wpid = waitpid(pid, &status, WUNTRACED);
//             //} while (!WIFEXITED(status) && !WIFSIGNALED(status));
//         }
//         close(fd[1]);
//         in = fd[0];
//         // move current position
// 		cmd = cmd->next;
// 	}
// }

void exe_made(t_cmd *cmd, char **env)
{
	pid_t pid[cmd_num(cmd)];
	int i = 0;
	int in = 0;
	int out = 1;
	char *env_path;
	int status;

	if ((cmd)->next == NULL)
	{
		exe_just(cmd, env);
		return ;
	}
	while (cmd)
	{
		if((cmd)->next != NULL)
		{
			pipe((cmd)->fd);
			out = (cmd)->fd[1];
		}
		env_path = exe_parse(env, (cmd)->argv[0]);
		pid[i] = fork();
		if(pid[i] == 0)
		{
			if(in != 0)
			{	
				dup2(in, 0);
				close(in);
			}
			if (out != 1 && (cmd)->next != NULL)
			{
				dup2(out, 1);
				close(out);
			}
			execve(env_path, (cmd)->argv, NULL);
		}
		else if(pid[i] > 0)
		{
			waitpid(pid[i], &status, 0);
		}
		close(out); // 마지막일때는 굳이 할 필요는 없는 듯?
		in = (cmd)->fd[0];
		(cmd) = (cmd)->next;
		++i;
	}
}

void exe_pwd(void)
{
    char *buf;
	buf = NULL;
    char *ret;
	
	ret = getcwd(0, MAXSIZE);
	if (ret == NULL)
		return ;// 오류처리 하기

	ft_putstr_fd(ret, 1);
	ft_putstr_fd("\n", 1);
	free(ret);
	return ;
}

void	create_list(t_env **lst)
{
	*lst = malloc(sizeof(t_env));
	(*lst)->key = NULL;
	(*lst)->value = NULL;
	(*lst)->next = NULL;
	(*lst)->env_flag = 0;
}

void add_node(t_env *add_lst, t_env **env_lst)
{
	t_env *move;

	move = *env_lst;

	if (*env_lst == NULL)
		*env_lst = add_lst;
	else
	{
		while (move->next)
			move = move->next;
		move->next = add_lst;
	}
}

void export_split(t_env *lst, char **argv)
{
	char **export_oneline;

	export_oneline = ft_split(argv[1], '=');

	int i = 0;
	while(export_oneline[i])
	{
		printf("____%s____%d\n", export_oneline[i], i);
		++i;
	}
	lst->key = export_oneline[0];
	
	
	if(ft_strchr(argv[1], '='))
	{
		lst->value = export_oneline[1];
		lst->env_flag = 1;
	}

}

int duplicate_search(t_env *env_lst, t_env *lst)
{
	//a만 들어가면 일단 들어는 가져 a
	//a=, a=dadsa 이런식으로 들어가면 다 엎어


	while(env_lst)
	{	
		if(ft_strncmp(env_lst->key, lst->key, ft_strlen(lst->key)) == 0)
		{
			printf("key ; %s  value : %s  env_flag :%d\n", lst->key, lst->value, lst->env_flag);
			if (lst->env_flag == 0)
				return (1);
			else
			{
				// printf("before\t");
				// printf("env\tkey ; %s  value : %s  env_flag :%d\n", env_lst->key, env_lst->value, env_lst->env_flag);
				// printf("lst\tkey ; %s  value : %s  env_flag :%d\n", lst->key, lst->value, lst->env_flag);
				env_lst->value = lst->value;
				env_lst->env_flag = 1;
				// printf("after\t");
				// printf("env\tkey ; %s  value : %s  env_flag :%d\n", env_lst->key, env_lst->value, env_lst->env_flag);
				// printf("lst\tkey ; %s  value : %s  env_flag :%d\n", lst->key, lst->value, lst->env_flag);
				return (1);
			}
		}
		env_lst = env_lst->next;
	}
	return (0);
}

int add_export(t_env **env_lst, t_cmd *cmd)
{
	t_env *lst;

	create_list(&lst);
	export_split(lst, cmd->argv);
	if (duplicate_search(*env_lst, lst))
	{
			return (1);
		// printf("out");
		// printf("key ; %s  value : %s  env_flag :%d\n", (*env_lst)->key, (*env_lst)->value, (*env_lst)->env_flag);
		// printf("key ; %s  value : %s  env_flag :%d\n", lst->key, lst->value, lst->env_flag);
		// free(lst);
	}

//printf("key ; %s  value : %s  env_flag :%d\n", lst->key, lst->value, lst->env_flag);
	add_node(lst, env_lst);

	return (0);
}

// void sort_export(t_env **env_lst)
// {
// 	t_env *big;
// 	t_env *move;
// 	t_env *set;

// 	set = *env_lst;
// 	big = *env_lst;
// 	move = *env_lst;
// 	int i = 0;

// 	while (set)
// 	{
// 		while (move)
// 		{
// 			i = 0;
// 			while (big->key[i] == NULL || move->key[i] == NULL)
// 			{
// 				if (big->key[i] < move->key[i])
// 				{
				
// 				}
// 				i++;
// 			}
// 			move = move->next;
// 		}
// 	}
// }

void print_export(t_env *env_lst)
{
	t_env *print_lst;

	print_lst = env_lst;
	//sort_export(&env_lst);
			// print로 빼버리기
	while (print_lst)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(print_lst->key, 1);

		if(print_lst->env_flag == 1)
		{
			ft_putstr_fd("=", 1);
			if(print_lst->value == NULL)
				ft_putstr_fd("\"\"", 1);
			ft_putstr_fd(print_lst->value, 1);	
		}
		ft_putstr_fd("\n", 1);
	//두가지를 구분하기 위함 플래그
		print_lst = print_lst->next;
	}

}

void exe_export(t_env **env_lst, t_cmd *cmd)
{

	if (cmd->argv[1])
	{
		if (add_export(env_lst, cmd))
			return ; // 탐색의 과정도 필요할 듯
		//정렬하여서 출력하기
	}
	else
	{
		print_export(*env_lst); // 정렬을 하고 출력을 하기
	}
	// 	//print로 빼버리기
	// 	while (print_lst)
	// 	{
	// 		ft_putstr_fd("declare -x ", 1);
	// 		ft_putstr_fd(print_lst->key, 1);

	// 		if(print_lst->env_flag == 1)
	// 		{
	// 			ft_putstr_fd("=", 1);
	// 			if(print_lst->value == NULL)
	// 				ft_putstr_fd("\"\"", 1);
	// 			ft_putstr_fd(print_lst->value, 1);	
	// 		}
	// 		ft_putstr_fd("\n", 1);
	// 	//두가지를 구분하기 위함 플래그
	// 		print_lst = print_lst->next;
	// 	}
	// }
	//정렬하는 과정 여기서 쯤 필요할 듯
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
	move = *env_lst;
	while (move)
	{	
		if (ft_strncmp(move->key, cmd->argv[1], ft_strlen(cmd->argv[1])) == 0)
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
}

void exe_cd(t_cmd *cmd)
{
	int result = 0;
	char *home;
	char *path;

	home = getenv("HOME");
	path = ft_strjoin(home, "/");

	printf("%s , %s\n",cmd->argv[0], cmd->argv[1]);

	//cd ~/Downloads
	if(cmd->argv[1])
	{
		if(ft_strchr(cmd->argv[1],'~'))
		{
			if(ft_strlen(cmd->argv[1]) > 1)
			{
				char *joins = ft_strjoin(path, &cmd->argv[1][2]);
				printf("\t%s\n", joins);
				chdir(joins);
			}
			else
				chdir(home);
		}
		else
		{
			result = chdir(cmd->argv[1]);
			if( result == 0 )
			{
				printf( "이동 성공" );
			}
			else if( result == -1 )
			{
				perror( "이동 실패 - " );
			}
		}
	}
}

int echo_option_chk(char *option)
{
	int i = 2;
	if(option[0] == '-' && option[1] == 'n')
	{
		while (option[i])
		{
			if (option[i] != 'n')
			{
				//printf("--------");
				return (0);
			}
			++i;
		}
		return (1);
	}
	return (0);
}

void exe_echo(t_cmd *cmd)
{
	int i;
	int option = 0;
	i = 1;
	//printf("%s %s\n", cmd->argv[0], cmd->argv[1]);

	if(cmd->argv[1])
	{
		option = echo_option_chk(cmd->argv[1]);
		// printf("%d", option);
	}
	if (option)
		i = 2;
	while(cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], 1);

		++i;
		if(cmd->argv[i])
			ft_putstr_fd(" ", 1);
	}
	if(!option)
		ft_putstr_fd("\n", 1);
	
}

void exe(t_cmd *cmd, char **env, t_env **env_lst)
{
	if (ft_strncmp((cmd->argv[0]), "pwd", 3) == 0 && ft_strlen(cmd->argv[0]) == 3)
		exe_pwd();
	else if (ft_strncmp((cmd->argv[0]), "env", 3) == 0 && ft_strlen(cmd->argv[0]) == 3)
	{
		// 만약에 이 과정이 없고 export를 한다면 export가 출력이 안되지 않을까? 
		// if / else if 외부로 빼는 것을 해야하는 것 아닌가
		print_env(*env_lst);
	}
	else if (ft_strncmp((cmd->argv[0]), "export", 6) == 0 && ft_strlen(cmd->argv[0]) == 6)
	{
		//아스키 코드순서대로 정렬하는 것이 필요하다
		
		exe_export(env_lst, cmd);
		
		//정렬과정 이거는 조금 어려워 보임..
	}
	else if (ft_strncmp((cmd->argv[0]), "unset", 5) == 0 && ft_strlen(cmd->argv[0]) == 5)
		exe_unset(env_lst, cmd);
	
	else if (ft_strncmp((cmd->argv[0]), "cd", 5) == 0 && ft_strlen(cmd->argv[0]) == 2)
		exe_cd(cmd);
	else if (ft_strncmp((cmd->argv[0]), "echo", 4) == 0 && ft_strlen(cmd->argv[0]) == 4)
		exe_echo(cmd);
	else
		exe_made(cmd, env);
	
	//env_lst 를 free해주거나 꺼내거나
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
		line = readline("minishell$ ");
		exit_function(line);
		if(line)
		{
			if (parse_line(&cmd, line, envp))
				return (EXIT_FAILURE);
			if (ft_strlen(line) > 0)
			{
				exe (cmd, env, &env_lst);
				add_history (line);
			}
		}
		free(line);
		line = NULL;
		cmd_clear(&cmd);
	}
	return (EXIT_SUCCESS);
}
