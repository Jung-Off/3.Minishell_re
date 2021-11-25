
#include "../includes/minishell.h"

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
			//cd __ > home 을 탐색
			//cd
			//getenv("HOME"); unset하고 나서는 없어야됨
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