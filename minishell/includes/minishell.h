/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 12:21:58 by malatini          #+#    #+#             */
/*   Updated: 2023/10/13 16:56:28 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <curses.h>
# include <signal.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# include <stdbool.h>
# include <stdint.h>
# include <limits.h>
# include <termios.h>

# define E_CATCHALL	1
# define E_MISUSE	2
# define E_CEXEC	126
# define E_NOTF		127
# define E_INVALID	128
# define E_SIG		130
# define E_OUT		255

# define SYS_MALLOC	"Error during memory allocation.\n"
# define SYS_OPEN	"Can not open the file.\n"
# define SYS_CLOSE	"Error while closing the file.\n"
# define SYS_DUP2D	"Error when using dup2.\n"
# define SYS_EXECVE	"Error when using execve.\n"
# define SYS_WRITE	"Error when writing.\n"
# define SYS_FORK	"Error when forking.\n"
# define SYS_CHDIR	"Error when changing working directory.\n"
# define SYS_PIPE	"Error when piping.\n"
# define M_CMD		": command not found\n"

enum e_r
{
	R_NONE,
	R_INPUT,
	R_OUTPUT,
	RR_INPUT,
	RR_OUTPUT
};

typedef struct s_cmd_elem	t_cmd_elem;
typedef struct s_cmd		t_cmd;
typedef struct s_ret_elem	t_ret_elem;
typedef struct s_ret_list	t_ret_list;
typedef struct s_env_list	t_env_list;
typedef struct s_env_elem	t_env_elem;
typedef struct s_file_elem	t_file_elem;
typedef struct s_file_list	t_file_list;
typedef struct s_parse		t_parse;
typedef struct s_env_var	t_env_var;
typedef struct s_export		t_export;
typedef struct s_mem		t_mem;

struct			s_ret_elem
{
	int			ret_code;
	t_ret_elem	*next;
};

struct			s_ret_list
{
	t_ret_elem	*first;
};

struct			s_env_elem
{
	char		*key;
	char		*value;
	t_env_elem	*next;
	bool		display;
	bool		last_ret;
};

struct			s_env_list
{
	t_env_elem	*first;
};

struct			s_file_elem
{
	char		*path;
	int			fd;
	t_file_elem	*next;
	bool		quotes;
	enum e_r	redir_type;
};

struct			s_file_list
{
	t_file_elem	*first;
};

struct			s_cmd_elem
{
	char		**args;
	int			args_len;
	t_file_list	*file;
	t_cmd_elem	*next;
	pid_t		pid;
	bool		is_piped;
	bool		is_builtin;
	enum e_r	redir_type;
	char		*path;
	bool		path_set;
	int			pipe[2];
	bool		is_forked;
};

struct			s_cmd
{
	t_cmd_elem	*first;
};

struct	s_parse
{
	int			i;
	t_cmd_elem	*e;
	enum e_r	r_type;
	int			ret;
	bool		error;
};

struct	s_env_var
{
	int		i;
	char	*key;
	char	*value;
	int		j;
	int		k;
};

struct s_export
{
	int			i;
	bool		append;
	char		*old_value;
	char		*value;
	char		*key;
	t_env_elem	*env_elem;
};

struct	s_mem
{
	char		*line;
	t_cmd		*cmd;
	char		**buffer;
	char		**env;
	t_env_list	*env_list;
	t_ret_list	*ret_list;
	bool		quotes;
	t_export	*exp;
	t_env_list	*temp;
	bool		no_display_temp;
	bool		exited;
	bool		found;
	char		**env_test;
	bool		cmd_not_found;
};

typedef struct s_sig
{
	int			sigint;
	int			sigquit;
	int			exit_status;
	pid_t		pid;
	bool		heredoc;
	t_mem		*mem;
}				t_sig;

bool			check_append(char *str);
bool			check_export_key(t_cmd_elem *elem, t_mem *mem);
bool			check_key(char *str, t_mem *mem);
bool			found_char(char *str, char c);
bool			ft_isalnum(int c);
bool			ft_isdigit(int c);
bool			is_correct_key(char *key);
bool			is_file(char *path);
bool			is_key_char_begin(char c);
bool			is_key_char(char c);
bool			is_redir(char c);
bool			is_sep(char c);
bool			replace_value_in_env(char *key, char *value, t_mem *mem);
bool			setup_builtin_pipe(t_cmd_elem *e, t_mem *m, t_cmd_elem **prev);
bool			spe_case(char c);
bool			str_is_all_digit(char *str);
char			**add_str_to_tab(t_cmd_elem *elem, char *buffer, t_mem *mem);
char			**ft_env_string_tab(t_env_list *env, t_mem *mem);
char			**ft_split(char const *str, char c);;
char			*copy_in_buffer(char *old_buf, char c, t_mem *mem);
char			*copy_str_in_buf(char *old_buf, char *s1, t_mem *mem);
char			*cpy_key(t_mem *mem, int j);
char			*expand_line(char *l, t_mem *m, int i, char *temp);
char			*find_exec(t_cmd_elem *elem, t_mem *mem);
char			*find_value_in_env(char *k, t_mem *mem);
char			*flatten_env_var(t_env_elem *env, t_mem *mem);
char			*ft_itoa(int n, t_mem *mem);
char			*ft_strcat(char *dest, char *src);
char			*ft_strchr(char *str, int c);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strdup(const char *s1, t_mem *mem);
char			*ft_strndup(t_mem *mem, char *str, int i);
char			*isolate_key_from_string(char *str, t_mem *mem);
char			*isolate_value_from_string(char *str, t_mem *mem);
char			*loop_in_paths(t_cmd_elem *e, char **sp, char *bin);
char			*read_quoted(t_mem *mem, int *pos, t_parse *p);
char			*sub_isolate(char *str, char *value, int i);
int				add_key_no_value(char *str, t_mem *mem);
int				append_env_var(char *v, char *old, t_mem *m, t_env_elem *e);
int				check_cmd(t_cmd *cmd);
int				check_file(t_mem *mem);
int				check_parsing_end_conditions(t_mem *m, int *r);
int				check_path_set(t_mem *mem);
int				close_all_fds(t_mem *mem);
int				d_err_p_ret(char *error, t_mem *mem, int ret, int fd);
int				d2_err_p_ret(char *error, char *arg, t_mem *mem, int ret);
int				d3_err(char *error, char *arg, t_mem *mem, int ret);
int				d4_err_p_ret(char *error, char *arg, t_mem *mem, int ret);
int				d5_err_p_ret(char *error, char *arg, t_mem *mem, int ret);
int				exec_build(t_cmd_elem *elem, t_mem *mem);
int				exec_process(t_cmd_elem *elem, t_mem *mem);
int				ft_atoi(const char *str, bool *big);
int				ft_close_pipes(t_mem *mem);
int				ft_exec_cd(t_cmd_elem *elem, t_mem *mem);
int				ft_exec_echo(t_cmd_elem *e, t_mem *mem);
int				ft_exec_env(t_env_list *env, t_mem *mem);
int				ft_exec_exit(t_cmd_elem *elem, t_mem *mem);
int				ft_exec_export(t_cmd_elem *cmds, t_mem *mem);
int				ft_exec_pwd(t_mem *mem);
int				ft_exec_unset(t_cmd_elem *elem, t_mem *m);
int				ft_execution(t_mem *mem);
int				ft_export_no_arg(t_mem *mem);
int				ft_heredoc(t_file_elem *f, t_mem *m);
int				ft_isalpha(int c);
int				ft_read(char **envp, bool env_set);
int				ft_redirection(t_cmd_elem *elem, t_mem *mem);
int				ft_strcmp(char *s1, char *s2);
int				ft_strlen(char *str);
int				handle_pipe(t_mem *m, t_parse *p);
int				handle_redir(t_mem *m, t_parse *p);
int				increment_shell_level(t_env_elem *elem, t_mem *mem);
int				is_builtin(char *s);
int				last_file_fd(t_cmd_elem *elem);
int				list_env_len(t_env_list *env);
int				loop_for_shell_level(t_mem *mem);
int				main(int argc, char **argv, char **env);
int				parse_line(t_mem *mem);
int				return_last_ret(t_mem *mem);
int				set_redir_type(char *line, int i, t_cmd_elem *elem, t_mem *mem);
int				syntax_error(t_mem *mem);
int				wait_exec_cmds(t_cmd_elem *elem, t_mem *mem);
t_cmd			*init_cmd(t_mem *mem);
t_cmd_elem		*init_cmd_elem(t_cmd *cmd, t_mem *mem);
t_cmd_elem		*prev_is_piped(t_cmd_elem *elem, t_cmd *cmd);
t_cmd_elem		*push_cmd(t_cmd *cmd, t_mem *mem);
t_env_elem		*find_key_in_env(char *key, t_mem *mem);
t_env_list		*bubble_sort(t_env_list *cpy);
t_env_list		*cpy_env_list(t_mem *mem);
t_mem			*init_mem(char **envp, bool env_set);
t_ret_list		*init_ret_list(t_mem *mem);
void			*ft_calloc(size_t count, size_t size);
void			*ft_memcpy(void *dest, const void *src, size_t size);
void			*ft_memset(void *dest, int c, size_t len);
void			add_env_var(char *str, t_mem *mem, bool d, bool append);
void			ascii_art(void);
void			child_function(t_cmd_elem *e, t_mem *m, t_cmd_elem *prev);
void			close_forked(int old_fd, int old_fd0);
void			define_mem(t_mem *mem, t_cmd *cmd, char *line, char **buffer);
void			dup_forked(int *old_fd, int *old_fd0);
void			end_arg(char **buf, t_cmd_elem *e, t_mem *m, enum e_r *t);
void			expansion_split(t_mem *m, int *i, t_cmd_elem *e, enum e_r *t);
void			failure(int error, t_mem *mem);
void			free_cmd_no_exit(t_cmd *cmd);
void			free_cmd(t_cmd *cmd);
void			free_env_list(t_env_list *list);
void			free_file_list(t_file_list *file);
void			free_mem_no_exit(t_mem *mem);
void			free_mem(t_mem *mem);
void			free_ret_list(t_mem *mem);
void			free_tab(char **tab);
void			ft_add_history(char *line);
void			ft_bzero(void *s, size_t n);
void			ft_putstr_fd(char *s, int fd);
void			init_env_list(t_mem *mem, bool env_set);
void			init_env_var(t_env_var *v);
void			loop_heredoc(char *l, t_mem *m, t_file_elem *f, int *h);
void			loop_through_env_var(t_mem *mem);
void			print_tab_env(t_env_list *env);
void			push_env_var(char *key, char *value, t_mem *mem);
void			push_file_elem(t_cmd_elem *e, char **buff, bool q, enum e_r t);
void			push_ret_elem(t_mem *mem, int ret_value);
void			quote_expand(t_mem *m, int *pos);
void			s_init(t_mem *m);
void			s_int(int code);
void			s_quit_hd(int signal);
void			s_quit(int code);
void			set_exp(t_mem *m);
void			set_value_in_env(char *key, char *value, t_mem *mem);
void			setup_file_dup(t_cmd_elem *elem);
void			sub_add_env_var(char *str, t_env_var *v, t_mem *mem, bool ap);

extern t_sig				g_sig_var;

#endif
