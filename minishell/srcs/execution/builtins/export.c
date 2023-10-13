/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 16:01:17 by malatini          #+#    #+#             */
/*   Updated: 2023/10/13 15:32:35 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sub_export(t_cmd_elem *c, t_export *e, t_mem *m)
{
	if (!e->old_value)
	{
		if (found_char(c->args[e->i], '='))
		{
			if (e->append && !e->env_elem)
				add_env_var(c->args[e->i], m, true, true);
			else if (e->append && e->env_elem)
				append_env_var(e->value, NULL, m, e->env_elem);
			else if (e->env_elem)
				append_env_var(e->value, NULL, m, e->env_elem);
			else
				add_env_var(c->args[e->i], m, true, false);
		}
		else
			add_key_no_value(c->args[e->i], m);
		return ;
	}
	e->env_elem = find_key_in_env(e->key, m);
	if (e->append)
		append_env_var(e->value, e->old_value, m, e->env_elem);
	else if (e->value)
		set_value_in_env(e->key, e->value, m);
	return ;
}

int	ft_export(t_cmd_elem *el, t_mem *m)
{
	t_export	exp;

	m->exp = &exp;
	set_exp(el, m);
	if (!check_export_key(el, m))
		return (1);
	while (el->args[exp.i])
	{
		exp.append = check_append(el->args[exp.i]);
		exp.key = isolate_key_from_string(el->args[exp.i], m);
		exp.env_elem = find_key_in_env(exp.key, m);
		if (exp.key)
			exp.old_value = find_value_in_env(exp.key, m);
		exp.value = isolate_value_from_string(el->args[exp.i], m);
		sub_export(el, &exp, m);
		if (exp.key)
			free(exp.key);
		if (exp.value)
			free(exp.value);
		if (exp.old_value)
			free(exp.old_value);
		exp.i++;
	}
	push_ret_elem(m, 0);
	return (0);
}

int	ft_check_export(t_cmd_elem *e, t_mem *m)
{
	int			i;
	char		*key;
	t_env_elem	*elem;

	i = 1;
	elem = NULL;
	while (i < e->args_len)
	{
		key = isolate_key_from_string(e->args[i], m);
		elem = find_key_in_env(key, m);
		if (elem && ft_strcmp(elem->key, key)
			&& (e->args[i][0] == '='
			|| !is_correct_key(key) || !key || !key[0]))
		{
			d5_err_p_ret("\': not a valid identifier\n", e->args[i], m, 1);
			free(key);
			free(elem);
			return (1);
		}
		i++;
		free(key);
	}
	ft_export(e, m);
	return (0);
}

int	ft_exec_export(t_cmd_elem *cmds, t_mem *mem)
{
	int		ret;

	(void)mem;
	ret = 0;
	if (cmds->args_len <= 1)
		ft_export_no_arg(cmds, mem);
	else
		ft_check_export(cmds, mem);
	return (ret);
}

void	loop_through_env_var(t_mem *mem)
{
	t_env_elem	*elem;

	elem = mem->env_list->first;
	while (elem)
	{
		if (elem->key && elem->value && elem->value[0] && !elem->display)
			elem->display = true;
		elem = elem->next;
	}
	return ;
}
