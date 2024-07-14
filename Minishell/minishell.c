#include "minishell.h"

t_cmd *shell(void)
{
	static t_cmd shell;
	return(&shell);
}

int ft_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}


t_env *init_env_list(char **envp, t_node **gc)
{
	t_env *head = NULL;
	t_env *new_node;
	char *name;
	char *value;
	char *env_copy;
	int i = 0;

	while (envp[i] != NULL)
	{
		env_copy = strdup(envp[i]);
		if (!env_copy)
			return NULL;

		name = ft_substr(env_copy, 0, ft_strlen_untile_char(env_copy, '='), gc);
		value = ft_strchr(env_copy, '=');

		new_node = gc_malloc(gc, sizeof(t_env));
		if (!new_node)
		{
			free(env_copy);
			return NULL;
		}

		new_node->name = ft_strdup(gc, name);
		new_node->value = ft_strdup(gc, value);
		new_node->next = head;
		head = new_node;

		free(env_copy);
		i++;
	}
	return head;
}

void split_pipe(char *cmd, t_cmd *env, t_node **gc)
{
	t_node *link_cmd;
	char **all_cmd;

	link_cmd = NULL;
	all_cmd = ft_split(cmd, '|', gc);
	while (*all_cmd != NULL)
	{
		ft_lstadd_back(&link_cmd, ft_lstnew(*all_cmd));
		(all_cmd)++;
	}
	ft_exc_cmd(link_cmd, gc, env);
}

void	ft_signal_handler(int signum)
{
	(void)signum;
	 ft_putstr_fd("\n", 1);
	 rl_on_new_line();
	 rl_replace_line("", 0);
	 rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	t_node *gc;
	t_node *fd;
	t_cmd ev;
	int i;

	gc = NULL;
	fd = NULL;
	i = 0;
	char *line;
	t_env *env_list;

	ev.flag = 0;
	if (envp == NULL || envp[0] == NULL)
    {
		ev.flag = 1;
        envp = gc_malloc(&fd, 4 * sizeof(char *));
        envp[0] = ft_strdup(&fd, "PWD=/nfs/homes/oait-bou/Downloads");
        envp[1] = ft_strdup(&fd, "SHLVL=1");
        envp[2] = ft_strdup(&fd, "_=/usr/bin/env");
        envp[3] = NULL;
    }
	ev.env = envp;
	env_list = init_env_list(envp, &fd);
	ev.addres_env = env_list;
	ev.addres_fd = fd;
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		ft_sort_env_list(&ev);
		printf("\033[0m");
		line = readline("$ ");
		if (line != NULL)
		{
			ev.flag_signle = 0;
			if (input_validation(line) != 1)
				split_pipe(line, &ev, &gc);
			add_history(line);
			ft_lstclear(&gc);
		}
		else
			break ;
	}
	rl_clear_history();
	ft_lstclear(&gc);
	return (0);
}