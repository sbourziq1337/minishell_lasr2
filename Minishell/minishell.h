#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

typedef struct s_node
{
	void			*data;
	struct s_node	*next;
}					t_node;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	int				**fd;
	int 			flag;
	int             flag_signle;
	char			*access_path;
	char			**env;
	char			**cmd;
	t_node			*infile;
	t_node			*outfile;
	t_node			*heredoc;
	t_node			*append;
	t_env			*like_env;
	int				count;
	int				her;
	int				file;
	int	cmd_count;
	t_env			*addres_env;
	t_node			*addres_fd;
	char *env_line;
}					t_cmd;

t_cmd *shell(void);
void	ft_signal_handler(int signum);
void ft_signal_back_slash(int signum);
void				*gc_malloc(t_node **gc, int size);
char				**ft_split_str(char *str, char *charset);
char				**ft_split(char *s, char c, t_node **gc);
void				ft_lstadd_back(t_node **lst, t_node *new);
void				ft_exc_cmd(t_node *cmd, t_node **gc, t_cmd *env);
t_node				*ft_lstnew(void *ptr);
char				*ft_strchr_hlber(char *s, int c, int *n);
char				*ft_check_path(char *str, t_node **gc, t_cmd *env);
void				ft_access_to_path(t_node **gc, char **str, char *path_cmd);
void				ft_lstclear(t_node **lst);
char				*ft_check_space(char *av, t_node **gc);
char				*ft_strjoin(t_node **gc, char *s1, char *s2);
void				ft_first_child(int i, t_node **gc, t_cmd *token,
						char *line);
void				ft_last_child(int i, t_node **gc, t_cmd *token, char *line);
void				ft_midll_child(int i, t_node **gc, t_cmd *token,
						char *line);
int					ft_strncmp(char *str, char *path, int line);
char				*ft_substr(char *s, int start, int len, t_node **gc);
void				ft_putstr_fd(char *s, int fd);
void				ft_lstclear(t_node **lst);
int					ft_strlen(char *s1);
t_node				*ft_lstlast(t_node *lst);
int					ft_strcmp(char *s1, char *s2);
void				tokenisation(void *line, t_node **gc, t_cmd *tkoen);
void				ft_find_herdoc(t_cmd *env, int *i, int *id, t_node **gc);
int					ft_file(char *str);
int					count_herdoc(t_node *herdoc);
void				ft_fork_pipe(t_cmd *file_des, int *id, int i, t_node **gc);
char				*ft_strchr(char *s, int c);
void				ft_check_file(t_cmd *token, int file, t_node **gc, int her);
void				ft_check_infile(t_cmd *token, int file, int her,
						t_node **gc);
void				ft_one_child(int i, t_node **gc, t_cmd *token);
void				ft_pwd(char *line, t_node **gc);
void				ft_echo(char *line, t_cmd *token);
void				ft_cd(char *line, t_cmd *token);
void				ft_exit(t_node **gc);
void				ft_putendl_fd(char *s, int fd);
void				ft_check_buldin(t_cmd *env, char *line, t_node **gc);
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
int					ft_check_buldin1(t_cmd *env, char *line, t_node **gc);
int					ft_strlen_untile_char(char *str, char c);
char				*ft_strdup(t_node **gc, char *s1);
void				ft_export(t_cmd *token, char *line);
void				ft_sort_env_list(t_cmd *token);
int					find_char(char *str, char c);
int					ft_isalpha(char *str);
void				ft_env(t_cmd *token);
void ft_setexport(char *pwd, char *cwd, t_cmd *token);

// utils tokens
void handle_append(char *line1, int *i, t_node **gc, t_cmd *token);
void handle_outfile(char *line1, int *i, t_node **gc, t_cmd *token);
void handle_heredoc(char *line1, int *i, t_node **gc, t_cmd *token);
void handle_infile(char *line1, int *i, t_node **gc, t_cmd *token);

int input_validation(char *line);
//handle quotes

int	in_single_quote(char *line, int index);
int	in_double_quote(char *line, int index);
void	handle_quotes(t_cmd *cmd, t_node **gc);

char *ft_strcpy(char *s1, char *s2, int len);
static char check(const char *set, char c);
char *ft_strtrim(char *s1, char *set, t_node **gc);

void	ft_remove_key_env(t_cmd *token, char *str);
void	ft_remove_key_export(t_cmd *token, char *str);
void	ft_unset(t_cmd *token, char *line);
char	**ft_split_qoute(char *s, char c, t_node **gc);

void ft_history(t_cmd *token);
int	checkchar(char a, char *b);
char	*ft_strtrim1(char *s1, char *set, t_node **gc);
char *expand_quotes(char *line);
void ft_remove_quotes(t_cmd *token);
void ft_add_qiotes(t_cmd *token);
 void	ft_signal_handler_herdoc(int signum);
