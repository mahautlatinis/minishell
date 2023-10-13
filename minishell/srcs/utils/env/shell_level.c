/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   shell_level.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: malatini <malatini@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/09/22 14:10:29 by malatini		  #+#	#+#			 */
/*   Updated: 2021/09/25 16:37:55 by malatini         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

int	increment_shell_level(t_env_elem *elem, t_mem *mem)
{
	int		new_value;
	int		ret;
	char	*itoa;

	ret = 0;
	new_value = 0;
	if (!ft_strcmp(elem->key, "SHLVL"))
	{
		new_value = ft_atoi(elem->value, false);
		new_value++;
		itoa = ft_itoa(new_value, mem);
		set_value_in_env(elem->key, itoa, mem);
		free(itoa);
		ret = 1;
	}
	return (ret);
}

int	loop_for_shell_level(t_mem *mem)
{
	t_env_elem	*elem;

	elem = mem->env_list->first;
	while (elem && !increment_shell_level(elem, mem))
		elem = elem->next;
	return (1);
}
