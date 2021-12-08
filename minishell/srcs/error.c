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
	(void)err_msg;
	parse_error(0, 258);
	printf("minishell: %s\n", err_msg);
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
