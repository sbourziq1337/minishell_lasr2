#include "minishell.h"

int	count_herdoc(t_node *herdoc)
{
	int	number;
	int	i;

	number = 0;
	i = 0;
	while (herdoc != NULL)
	{
		while (((char *)(herdoc->data))[i] != '\0')
		{
			if ((((char *)(herdoc->data))[i] == '<')
				&& (((char *)(herdoc->data))[i + 1] == '<'))
			{
				number++;
				break ;
			}
			i++;
		}
		i = 0;
		herdoc = herdoc->next;
	}
	return (number);
}

 void	ft_signal_handler_herdoc(int signum)
{
	if (signum == SIGINT)
    	{
        	ft_putstr_fd("\n", 1);
        	exit(1);
    	}
	if(signum == SIGQUIT)
	{
		ft_putstr_fd("\n", 1);
        	exit(1);
	}
}
void	ft_find_herdoc(t_cmd *env, int *i, int *id, t_node **gc)
{
	char	*str;

	str = NULL;
	ft_fork_pipe(env, id, *i, gc);
	if (id[*i] == 0)
	{
		signal(SIGINT, ft_signal_handler_herdoc);
		close((env->fd)[*i][0]);
		while (env->heredoc)
		{
			while (1)
			{
				str = readline("herdoc> ");
				if (str == NULL || (ft_strcmp(env->heredoc->data, str) == 0))
					break ;
				str = ft_strjoin(gc, str, "\n");
				if (env->heredoc->next == NULL)
					write((env->fd)[*i][1], str, ft_strlen(str));
			}
			if (env->heredoc->next == NULL)
				close((env->fd)[*i][1]);
			env->heredoc = env->heredoc->next;
		}
		exit(0);
	}
	else
	{
		close((env->fd)[*i][1]);
		waitpid(id[*i], 0, 0);
	}
	(*i)++;
}

int	ft_file(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			nb = 2;
			++i;
		}
		else if (str[i] == '<')
			nb = 1;
		i++;
	}
	return (nb);
}
