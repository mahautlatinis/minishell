/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:35:35 by malatini          #+#    #+#             */
/*   Updated: 2023/10/13 16:50:47 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	unsigned char	*buf_dest;
	unsigned char	*buf_src;

	buf_dest = (unsigned char *)dest;
	buf_src = (unsigned char *)src;
	if (dest == src)
		return (dest);
	while (size--)
		*(buf_dest++) = *(buf_src++);
	return (dest);
}

char	*flatten_env_var(t_env_elem *e, t_mem *mem)
{
	char	*ret;
	int		i;
	int		total_len;

	ret = NULL;
	total_len = ft_strlen(e->key) + 1 + ft_strlen(e->value) + 1;
	ret = (char *)malloc(sizeof(char *) * total_len);
	if (!ret)
		failure(-1, mem);
	i = ft_strlen(e->key);
	ret[i++] = '=';
	ret[total_len - 1] = '\0';
	ft_memcpy(ret, e->key, ft_strlen(e->key));
	ft_memcpy(&(ret[i]), e->value, ft_strlen(e->value));
	return (ret);
}

int	list_env_len(t_env_list *env)
{
	t_env_elem	*elem;
	int			i;

	i = 0;
	elem = env->first;
	while (elem)
	{
		elem = elem->next;
		i++;
	}
	return (i);
}

char	**ft_env_string_tab(t_env_list *env, t_mem *mem)
{
	int			i;
	t_env_elem	*elem;
	char		**ret;
	int			length;

	i = 0;
	length = list_env_len(env);
	ret = (char **)malloc(sizeof(char *) * (length + 1));
	if (!ret)
		failure(-1, mem);
	ret[length] = NULL;
	elem = env->first;
	while (elem)
	{
		ret[i] = flatten_env_var(elem, mem);
		i++;
		elem = elem->next;
	}
	return (ret);
}
