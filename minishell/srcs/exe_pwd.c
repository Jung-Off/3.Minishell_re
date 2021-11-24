
#include "../includes/minishell.h"

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