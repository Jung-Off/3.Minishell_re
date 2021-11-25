
#include "../includes/minishell.h"

char	*search_home(t_env *env_lst)
{
	while (env_lst)
	{
		if (ft_strncmp(env_lst->key, "HOME", ft_strlen("HOME")) == 0
			&& ft_strncmp(env_lst->key, "HOME", ft_strlen(env_lst->key)) == 0)
			{
				ft_putstr_fd(env_lst->key, 1);
			ft_putstr_fd("\n", 1);
			return (env_lst->value);
			}
		env_lst = env_lst->next;
	}
	return (0);
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
	
	if (!cmd->argv[1])
	{
		if (!search_home(env_lst))
		{
			ft_putstr_fd("minishell: cd: HOME not set", 1);
			ft_putstr_fd("\n", 1);
			return ;
		}
		chdir(search_home(env_lst));
	}
	if(cmd->argv[1])
	{
		if(ft_strchr(cmd->argv[1], '~'))
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