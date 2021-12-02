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

#include "../includes/minishell.h"

void	init_argument(t_cmd **cmd, t_env **env_lst, int argc, char **argv)
{
	*cmd = NULL;
	*env_lst = NULL;
	(void)argc;
	(void)argv;
}

void	main_clear(char **line, t_cmd *cmd)
{
	free(*line);
	*line = NULL;
	cmd_clear(&cmd);
}

int	exe(t_cmd *cmd, char *line, t_env *env_lst, char **env)
{			
	if (parse_line(&cmd, line, env_lst))
		return (EXIT_FAILURE);
	if (ft_strlen(line) > 0)
	{
		exe_process(&cmd, env, &env_lst);
		add_history (line);
	}
	return (0);
}

void free_env(t_env *env_lst)
{
	t_env *temp;

	while (env_lst)
	{
		temp = env_lst->next;
		free(env_lst);
		env_lst = temp;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;
	char	**env;
	t_env	*env_lst;

	init_argument(&cmd, &env_lst, argc, argv);
	make_envlst(envp, &env_lst);
	env = find_envp_path();
	while (1)
	{
		switch_echoctl(TURN_OFF);
		emit_signal(OMIT);
		line = readline("minishell$ ");
		if (!line)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			exit(EXIT_SUCCESS);
		}
		if (line)
			exe(cmd, line, env_lst, env);
		main_clear(&line, cmd);
	}
	free_env(env_lst);
	return (EXIT_SUCCESS);
}
