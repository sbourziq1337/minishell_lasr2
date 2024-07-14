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

void ft_signal_back_slash(int signum)
{
	write(1, "sddsdsdsdsdsdsdsdsds\n\n",23);
	if(signum == SIGQUIT)
	{
		write(1, "Quit\n", 6);
        exit(131); // Exit if SIGINT is received
	}
}

void ft_signal_handler_herdoc(int signum)
{
    if (signum == SIGINT)
    {
		sleep(1);
        write(1, "\n", 1);
        exit(130); // Exit if SIGINT is received
    }
}

void ft_find_herdoc(t_cmd *env, int *i, int *id, t_node **gc)
{
    char *str = NULL;

    ft_fork_pipe(env, id, *i, gc);
    if (id[*i] == 0) // Child process
    {
        close((env->fd)[*i][0]);
        signal(SIGINT, ft_signal_handler_herdoc);

        while (env->heredoc)
        {
            while (1)
            {
                str = readline("heredoc> ");
                if (str == NULL || (ft_strcmp(env->heredoc->data, str) == 0))
                    break;

                char *temp = str;
                str = ft_strjoin(gc, str, "\n");
                free(temp);

                if (env->heredoc->next == NULL)
                    write((env->fd)[*i][1], str, ft_strlen(str));
            }
            if (env->heredoc->next == NULL)
                close((env->fd)[*i][1]);

            env->heredoc = env->heredoc->next;
        }
        exit(0);
    }
    else // Parent process
    {
        close((env->fd)[*i][1]);
        int status;
        waitpid(id[*i], &status, 0);
        if (WEXITSTATUS(status) == 130) // Check if child exited due to SIGINT
            env->flag_signle = 1;
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
