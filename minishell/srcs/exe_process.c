/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jji <jji@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:44:55 by jji               #+#    #+#             */
/*   Updated: 2021/12/02 15:44:56 by jji              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int cmd_ok(char **env, char *cmd)
{
	int			i;
	char		*env_path;
	char		*add_slash;
	struct stat	buf;

	i = 0;
	while (env[i])
	{
		env_path = ft_strdup(env[i]);
		add_slash = ft_strjoin(env_path, "/");
		free(env_path);
		env_path = ft_strjoin(add_slash, cmd);
		if (stat(env_path, &buf) == 0)
		{
			// ft_putstr_fd("found", 1);
			// ft_putstr_fd(env_path, 1);
			return (1);
		}
		++i;
	}
	// ft_putstr_fd("not_found", 1);
	// ft_putstr_fd(env_path, 1);
	return (0);
}

void exe_process(t_cmd **cmd, char **env, t_env **env_list)
{
	pid_t pid;
	int in = 0;
	int out = 1;
	char *env_path;
	int status;

	//^C를 넣기 위함
	if (!(*cmd)->redirect) // cat grep
		emit_signal(N_OMIT);
	int flag = cmd_num(*cmd);
	while (*cmd)
	{	//빌트인이면 통과, 외부함수면 통과, 그경로에 없으면 실행
		// if (!(cmd_ok(env, (*cmd)->argv[0]) || is_built((*cmd)->argv[0]))) //여기서 export 걸림
		// //찾으면 1					//빌트인이면 1
		// //못찾으면 0				// 아니면 0
		// {
		// 	// ft_putstr_fd("front : ", 1);
		// 	// ft_putnbr_fd(cmd_ok(env, (*cmd)->argv[0]), 1);
		// 	// ft_putstr_fd(" back : ", 1);
		// 	// ft_putnbr_fd(is_built((*cmd)->argv[0]), 1);

		// 	// ft_putstr_fd("minishell: ", 1);
		// 	// ft_putstr_fd((*cmd)->argv[0], 1);
		// 	// ft_putstr_fd(": command not found\n", 1);
		// 		// printf("------------%d------------\n", g_exit_code);
		// 		// 		ft_error(1, 127);
		// 		// 		printf("~~~~~~~~~~~~~~~%d~~~~~~~~~~\n", g_exit_code);

		// 	// if ((*cmd)->next != NULL)
		// 		(*cmd) = (*cmd)->next;
		// 	continue;//명령어가 맞는지 확인하는 부분이 필요한듯
		// }
		if (is_built((*cmd)->argv[0]) && flag == 1 && !(*cmd)->redirect) //명령어가 하나이고, 명령어 길이가 1이다.
		{
			printf("only builtin\n");
			exe_builtin(*cmd, env_list);
			(*cmd) = (*cmd)->next;
		}
		else
		{
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

				if (!(cmd_ok(env, (*cmd)->argv[0]) || is_built((*cmd)->argv[0])))
				{
					//printf("not command g_exit_code : %d\n", g_exit_code);
					ft_error(1, (*cmd)->argv[0], "command not found", 127);
					//printf("not command g_exit_code : %d\n", g_exit_code);
				}
				if ((*cmd)->redirect > 0)
				{
					if(redirect_change((*cmd)->redirect, *env_list))	
						exit(0);
				}
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
				if (is_built((*cmd)->argv[0])) //내가 만든 함수
				{
					printf("here_is_built\n");
					exe_builtin(*cmd, env_list); //실행
					exit(g_exit_code);					//종료
				}
				else
				{
					if (execve(env_path, (*cmd)->argv, NULL) == -1)
					{	// perror("cmd not found");
						// printf("before not_built_in g_exit_code : %d\n", g_exit_code);
						// ft_error(1, 127);
						// printf("after not_built_in g_exit_code : %d\n", g_exit_code);
					}
				}
			}
			else if (pid > 0)
			{	
				waitpid(pid, &status, 0);
				printf("------------%d------------\n", g_exit_code);
				g_exit_code = WEXITSTATUS(status);
				printf("~~~~~~~~~~~~~~~%d~~~~~~~~~~\n", g_exit_code);
			}
			if ((*cmd)->next != NULL) //마지막이면 close 해주면 안됨 //이게 없으면 ls 하나일때 문제가 있음
				close(out); 
			in = (*cmd)->fd[0]; 

			(*cmd) = (*cmd)->next; 
		}
	}

}