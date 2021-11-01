/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malatini <malatini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 17:17:34 by malatini          #+#    #+#             */
/*   Updated: 2021/09/30 11:22:33 by malatini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_key_char(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (true);
	return (false);
}

bool	is_key_char_begin(char c)
{
	if (c == '_' || ft_isalpha(c))
		return (true);
	return (false);
}

bool	is_correct_key(char *key)
{
	int		i;
	bool	alpha;

	i = 0;
	alpha = false;
	while (key[i])
	{
		if (ft_isdigit(key[i]))
		{
			if (alpha == false)
				return (false);
		}
		else
			alpha = true;
		if (key[i] == '+' && key[i + 1] && !(key[i + 1] == '='))
			return (false);
		else if (!is_key_char(key[i]) && key[i] != '=' && key[i] != '+')
			return (false);
		i++;
	}
	return (true);
}

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

bool	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (true);
	return (false);
}
