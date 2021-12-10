/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:47:19 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/11/13 19:42:56 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error_handler(char *err_msg)
{
	printf("minishell: %s\n", err_msg);
	parse_error(0, 258);
	return (EXIT_FAILURE);
}

t_bool	error_check(t_cmd *cmd)
{
	t_redirect	*rp;

	rp = cmd->redirect;
	while (rp)
	{
		if (rp->file == NULL || rp->file[0] == '\0'
			|| rp->file[0] == '<' || rp->file[0] == '>')
			return (TRUE);
		rp = rp->next;
	}
	return (FALSE);
}

void	parse_error(int is_exit, int exit_code)
{
	g_exit_code = exit_code;
	if (is_exit)
		exit (g_exit_code);
}

void	ft_error(int is_exit, char *cmd, char *err_msg, int exit_code)
{
	if (cmd != NULL)
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
		write(2, err_msg, ft_strlen(err_msg));
	}
	g_exit_code = exit_code;
	if (is_exit)
		exit (g_exit_code);
}
