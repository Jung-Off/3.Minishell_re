/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 14:40:11 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/12/14 17:00:25 by applemang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_status(char **res, int *idx)
{
	*res = ft_itoa(g_exit_code);
	g_exit_code = 0;
	(*idx)++;
	return (EXIT_SUCCESS);
}

int	get_key(char **key, char **val, char *str, t_env *env)
{
	int		key_size;
	t_env	*p;

	key_size = 0;
	while (str[key_size] && str[key_size] != '\"' && str[key_size] != '\''
		&& str[key_size] != ' ' && str[key_size] != '$')
		key_size++;
	*key = ft_substr(str, 0, key_size);
	*val = NULL;
	p = env;
	while (p)
	{
		if (key_size == 0)
			*val = "$";
		else if (ft_strncmp(p->key, *key, ft_strlen(p->key)) == 0
			&& ft_strncmp(p->key, *key, ft_strlen(*key)) == 0)
			*val = p->value;
		p = p->next;
	}
	return (key_size);
}

int	get_env(char **res, char *str, t_env *env, int *idx)
{
	char	*key;
	char	*val;
	char	*join;

	if (!ft_strncmp("?", str, 1))
		return (get_status(res, idx));
	*idx += get_key(&key, &val, str, env);
	join = sh_strjoin(*res, val);
	free(*res);
	*res = join;
	free(key);
	return (EXIT_SUCCESS);
}

int	replace_env(char **str, t_env *env)
{
	int		i;
	int		quote;
	char	*new_str;

	i = -1;
	quote = NONE;
	new_str = NULL;
	while ((*str)[++i])
	{
		if ((*str)[i] == '\"' && quote == NONE)
			quote = DOUBLE;
		else if ((*str)[i] == '\'' && quote == NONE)
			quote = SINGLE;
		else if ((*str)[i] == QUOTE[quote])
			quote = NONE;
		else if ((*str)[i] == '$' && quote != SINGLE)
			get_env(&new_str, &((*str)[i + 1]), env, &i);
		else if ((*str)[i] != QUOTE[quote])
			add_char(&new_str, (*str)[i]);
	}
	free(*str);
	*str = new_str;
	if (!*str)
		*str = malloc_null_string();
	return (EXIT_SUCCESS);
}

int	replace(t_cmd *cmd, t_env *env)
{
	char		**p;
	t_redirect	*rp;

	p = cmd->argv;
	while (*p)
	{
		replace_env(p, env);
		p++;
	}
	rp = cmd->redirect;
	while (rp)
	{
		replace_env(&(rp->file), env);
		rp = rp->next;
	}
	return (EXIT_SUCCESS);
}
