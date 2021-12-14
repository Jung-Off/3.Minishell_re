/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: applemango <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:19:51 by applemang         #+#    #+#             */
/*   Updated: 2021/12/14 13:22:01 by applemang        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*sh_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*join;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = 0;
	return (join);
}

int	add_char(char **str, char ch)
{
	char	*ch_str;
	char	*new;

	ch_str = (char *)malloc(2);
	ch_str[0] = ch;
	ch_str[1] = 0;
	new = sh_strjoin(*str, ch_str);
	free(*str);
	free(ch_str);
	*str = new;
	return (EXIT_SUCCESS);
}

char	*malloc_null_string(void)
{
	char	*new;

	new = malloc(1);
	*new = 0;
	return (new);
}
