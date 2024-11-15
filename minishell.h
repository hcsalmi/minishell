/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 16:57:50 by esirnio           #+#    #+#             */
/*   Updated: 2023/10/11 13:44:15 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <sys/ioctl.h>
# include "libft/includes/libft.h"
# include <fcntl.h>

# define PIPE 2
# define CMD 3
# define WORD 4
# define RDR_R 5
# define RDR_L 6
# define RDR_RR 7
# define RDR_LL 8

typedef struct s_tokens {
	char			*str;
	int				type;
	int				dont_expand;
	struct s_tokens	*next;
}				t_tokens;

typedef struct s_node
{
	char			**command;
	int				is_builtin;
	int				pid;
	int				write_fd;
	int				read_fd;
	struct s_node	*next;
}				t_node;

typedef struct s_data
{
	char		**envs;
	int			exit_status;
	int			heredoc_count;
	int			word_idx;
	int			idx;
	int			quote_state;
	t_tokens	*tokens;
	t_node		*nodes;
}					t_data;

/*------			ENVS			------*/
void	print_envs(char **envs);
int		count_envs(char **envs);
void	add_envs(char **new_env, t_data *data);
void	del_envs(char **env_to_del, t_data *data);
char	*ft_get_env_value(char **current_envs, char *key);
char	**create_new_envs(int *locations, t_data *data);
int		find_env(char *env, char *current);
void	replace_env(char **current, int idx, char *replace);

/*------			INPUTS					-------*/
int		lexer(char *input, t_data *data);
int		is_quote(char c);
int		skip_white_spaces(const char *str, int i);
int		is_delimiter(char c, int *quote_state, int len);
char	*sort_stuff_in_between(char *expanded_var, char *s);
int		stuff_in_between(char *s);
char	*shell_strjoin(char *s1, char *s2);
void	do_expansion(t_tokens *token, t_data *data);
char	**make_command_to_node(t_tokens *token, t_data *data);
int		define_type(char *token, int found_cmd, char **splitted, int i);
char	*trim_quotes(char *str, t_tokens *token);
t_node	*parser(t_tokens *tokens, t_data *data);
int		is_redir(t_tokens *temp_token, t_node **node, t_data *data);
char	**split_input(char const *str, t_data *data);

/*------			BUILTINS					-------*/
int		do_builtin(t_node *head, t_data *data);
int		do_echo(t_node *node, t_data *data);
void	do_cd(char **command, t_data *data);
int		is_builtin(char *str);
void	do_pwd(t_data *data);

/*------			SIGNALS					-------*/
void	ctrl_c_main(int signal);
void	disable_echo_ctrl_c(struct termios *termios);
void	enable_echo_ctrl_c(struct termios *termios);
void	ctrl_c_child(int signal);
void	init_signals(void);

/*					PWD				*/
char	*get_path(void);
char	*set_path(char *command, t_data *data);

/* --	--	--	--	HEREDOC 	-	---	*/
int		here_doc(char *delimiter, t_data *data);
void	remove_here_doc_files(t_data *data);

/*					UTILS				*/
void	ft_free_2d_array(void **array, int size);
char	*ft_strndup(const char *src, size_t len);
int		strchr_idx(char *str, char delimiter);

/*					ERRORS				*/
void	malloc_error(void);
void	not_a_directory_error(char *str, t_data *data);
void	print_env_error(char *command, char *action, t_data *data);
void	execve_error(t_node *node);
void	open_error(t_data *data);
void	env_to_add_error(char *command, t_data *data);
void	exit_error(char *str);
void	syntax_error_near_token(t_data *data);

/*-- -- -- -- -- -- EXEC -- -- -- -- -- --*/
void	exec(t_node *head, t_data *data);
int		ft_child(t_node *node, t_data *data);
void	close_current_fds(t_node *node);
void	ft_wait(t_node *head, t_data *data);
int		check_if_working_path(char *str);

#endif
