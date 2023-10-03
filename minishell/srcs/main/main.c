/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:19:10 by malatini          #+#    #+#             */
/*   Updated: 2021/09/29 22:58:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
** Variable globale necessaire pour les signaux
*/
t_sig	g_sig_var;

/**
** Permet de gerer l'historique et les tabs sans passer par les termcaps.
* @author: malatini
*/
void	ft_add_history(char *line)
{
	if (line && *line)
		add_history(line);
}

/**
** Sous function pour la norme, va looper pour lire les lignes de commandes
* @author: malatini
*/
bool	loop_readline(char *line, t_mem *mem, char *buffer, t_cmd *cmd)
{
	while (true)
	{
		cmd = init_cmd(mem);
		init_cmd_elem(cmd, mem);
		buffer = NULL;
		s_init(mem);
		line = readline("\033[1;36muser@minishell$ \033[0m");
		define_mem(mem, cmd, line, &buffer);
		if (line)
		{
			if (parse_line(mem) >= 0)
				ft_execution(mem);
			else if (buffer)
				free(buffer);
			ft_add_history(line);
			free_mem_no_exit(mem);
			free(line);
			continue ;
		}
		ft_putstr_fd("exit\n", 1);
		free_mem_no_exit(mem);
		free_mem(mem);
		exit (EXIT_SUCCESS);
	}
	return (true);
}

/**
** Fonction de lecture + initialisation des structures
* @author: malatini
*/
int	ft_read(char **envp, bool env_set)
{
	char	*line;
	t_mem	*mem;
	char	*buffer;
	t_cmd	*cmd;

	buffer = NULL;
	cmd = NULL;
	mem = init_mem(envp, env_set);
	line = NULL;
	init_env_list(mem, env_set);
	loop_for_shell_level(mem);
	init_ret_list(mem);
	push_ret_elem(mem, 0);
	return (loop_readline(line, mem, buffer, cmd));
}

/**
 ** Main
 * @author: malatini
 */
int	main(int argc, char **argv, char **env)
{
	bool	env_set;

	(void)argv;
	env_set = true;
	if (!*env)
		env_set = false;
	if (argc == 1)
	{
		ascii_art();
		signal(SIGINT, &s_int);
		signal(SIGQUIT, &s_quit);
		ft_read(env, env_set);
	}
	exit (EXIT_SUCCESS);
}

/**
 ** Fonction de free + exit en cas d'erreurs appel systeme (malloc)
 * @author: malatini
 */
void	failure(int error, t_mem *mem)
{
	free_mem_no_exit(mem);
	free_mem(mem);
	ft_putstr_fd(SYS_MALLOC, 2);
	exit (error);
}
