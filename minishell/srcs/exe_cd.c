
#include "../includes/minishell.h"

int search_lst(t_cmd *cmd, t_env *env_lst)
{
	while (env_lst)
	{
		if (ft_strncmp(env_lst->key, cmd->argv[0], ft_strlen(cmd->argv[0])
			&& ft_strncmp(env_lst->key, cmd->argv[0], ft_strlen(env_lst->key)) == 0))
		{
			return (0);
		}
		env_lst = env_lst->next;
	}
	return (1);
}

void exe_cd(t_cmd *cmd, t_env *env_lst)
{
	int result = 0;
	char *home;
	char *path;
	(void)env_lst;

	home = getenv("HOME");
	path = ft_strjoin(home, "/");

	//printf("%s , %s\n",cmd->argv[0], cmd->argv[1]);
	
	if (!cmd->argv[1] && search_lst(cmd, env_lst))
	{
		ft_putstr_fd("bash: cd: HOME not set", 1);
		ft_putstr_fd("\n", 1);
		return ;
	}
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
			//cd __ > home 을 탐색
			//cd
			//getenv("HOME"); unset하고 나서는 없어야됨
				chdir(home);
		}
		else
		{
			result = chdir(cmd->argv[1]);
			if( result == 0 )
				printf("이동 성공\n");
			else if( result == -1 )
				perror("이동 실패 -\n");
		}
	}
	
}