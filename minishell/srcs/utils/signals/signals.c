/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:40:50 by malatini          #+#    #+#             */
/*   Updated: 2023/10/13 16:21:31 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	s_init(t_mem *m)
{
	g_sig_var.sigint = 0;
	g_sig_var.sigquit = 0;
	g_sig_var.pid = -1;
	g_sig_var.exit_status = 0;
	g_sig_var.heredoc = false;
	g_sig_var.mem = m;
	return ;
}

void	s_quit(int signal)
{
	(void)signal;
	if (g_sig_var.pid > 0 && !g_sig_var.heredoc)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		g_sig_var.exit_status = 131;
		g_sig_var.sigquit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", 2);
	return ;
}

void	s_int(int code)
{
	(void)code;
	if (g_sig_var.pid == 0 && g_sig_var.heredoc)
	{
		ft_putstr_fd("\b\b\b^C\b\b", 1);
		exit(0);
	}
	if (g_sig_var.pid == 0)
		g_sig_var.exit_status = 1;
	else
	{
		ft_putstr_fd("\n", 2);
		if (g_sig_var.pid == -1)
			rl_on_new_line();
		rl_redisplay();
		g_sig_var.exit_status = 130;
	}
	g_sig_var.sigint = 1;
	push_ret_elem(g_sig_var.mem, g_sig_var.exit_status);
	return ;
}

void	s_quit_hd(int signal)
{
	(void)signal;
	ft_putstr_fd("\b\b  \b\b", 1);
	return ;
}

