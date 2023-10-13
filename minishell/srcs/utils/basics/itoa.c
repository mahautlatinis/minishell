/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:55:27 by malatini          #+#    #+#             */
/*   Updated: 2023/10/13 16:59:49 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

int	n_size(int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*create_string(char *str, long nb, long length, long sign)
{
	str[length] = '\0';
	while (length > 0)
	{
		str[--length] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (sign < 0)
		str[length++] = '-';
	return (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		return (0);
	while ((*(unsigned char *)(s1 + i)) == *(unsigned char *)(s2 + i) &&
			i < n - 1 && s1[i] && s2[i])
		i++;
	return ((int)((*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i))));
}

char	*ft_itoa(int n, t_mem *mem)
{
	char	*str;
	long	length;
	long	nb;
	long	sign;

	nb = n;
	sign = 1;
	length = (long)n_size(nb);
	if (nb == 0)
		return (ft_strdup("0", mem));
	if (nb == -2147483648)
		return (ft_strdup("-2147483648", mem));
	if (nb < 0)
	{
		nb = -nb;
		sign = -sign;
	}
	str = (char *)malloc(sizeof(char) * (length + 1));
	if (!(str))
		failure(-1, mem);
	str = create_string(str, nb, length, sign);
	return (str);
}
