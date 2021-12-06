/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jji <jji@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 20:47:11 by jji               #+#    #+#             */
/*   Updated: 2021/11/30 20:47:12 by jji              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exe_pwd(void)
{
	char	*buf;
	char	*ret;

	buf = NULL;
	ret = getcwd(0, MAXSIZE);
	if (ret == NULL)
		return ;

	ft_putstr_fd(ret, 1);
	ft_putstr_fd("\n", 1);
	free(ret);
	g_exit_code = 0;
	return ;
}
