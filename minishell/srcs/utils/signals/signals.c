/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:40:50 by malatini          #+#    #+#             */
/*   Updated: 2023/10/13 16:02:11 by mahautlatin      ###   ########.fr       */
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
