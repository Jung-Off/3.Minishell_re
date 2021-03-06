/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:55:44 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/12/14 13:52:36 by applemang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pass_quotes(char **input)
{
	int	quote;

	quote = NONE;
	if (**input == '\"' && (*input)++)
		quote = DOUBLE;
	else if (**input == '\'' && (*input)++)
		quote = SINGLE;
	while (**input != QUOTE[quote])
	{
		if (!**input)
			return (error_handler("unclosed quote"));
		(*input)++;
	}
	return (EXIT_SUCCESS);
}

int	split_line(char **cmd, char **line)
{
	char	*start;

	if (**line == '|')
		(*line)++;
	while (ft_isspace(**line))
		(*line)++;
	start = *line;
	while (**line && **line != '|')
	{
		if (**line == '\'' || **line == '\"')
			if (pass_quotes(line))
				return (EXIT_FAILURE);
		(*line)++;
	}
	*cmd = ft_substr(start, 0, *line - start);
	return (EXIT_SUCCESS);
}

int	parse_line_2(t_cmd **cmd_lst, t_cmd **new_cmd, char *cmd, t_env *env)
{
	cmd_add_back(cmd_lst, *new_cmd);
	if (parse_command(new_cmd, cmd))
		return (EXIT_FAILURE);
	if (replace(*new_cmd, env))
		return (EXIT_FAILURE);
	if (error_check(*new_cmd))
		return (error_handler("syntax error near unexpected token"));
	return (EXIT_SUCCESS);
}

int	parse_line(t_cmd **cmd_lst, char *line, t_env *env)
{
	t_cmd	*new_cmd;
	char	*cmd;

	if (*line == '|')
		return (error_handler("syntax error near unexpected token \'|\'"));
	while (*line)
	{
		if (split_line(&cmd, &line))
			return (EXIT_FAILURE);
		if (!*cmd)
		{
			free(cmd);
			return (error_handler("syntax error near unexpected token \'|\'"));
		}
		new_cmd = create_cmd();
		if (!new_cmd)
			return (error_handler("malloc error in create_cmd()"));
		if (parse_line_2(cmd_lst, &new_cmd, cmd, env))
		{
			free(cmd);
			return (EXIT_FAILURE);
		}
		free(cmd);
	}
	return (EXIT_SUCCESS);
}
