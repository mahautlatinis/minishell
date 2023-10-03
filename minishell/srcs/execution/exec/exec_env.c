/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:35:35 by malatini          #+#    #+#             */
/*   Updated: 2021/09/26 11:16:36 by user42           ###   ########.fr       */
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

/**
** Utils pour permettre de recreer un char **env
* @author: malatini
*/
char	*flatten_env_var(t_env_elem *e, t_mem *mem)
{
	char	*ret;
	int		i;
	int		total_len;

	ret = NULL;
	(void)mem;
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

/**
** Retourne la longueur de la liste chainee de variable d'env 
* @author: malatini
*/
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

/**
** Fonction necessaire pour le execve qui a besoin d'un char **env
* @author: malatini
*/
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
