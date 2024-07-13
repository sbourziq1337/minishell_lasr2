#include "minishell.h"

void ft_fork_pipe(t_cmd *file_des, int *id, int i, t_node **gc)
{
	if (pipe((file_des->fd)[i]) == -1)
	{
		perror("pipe failed");
		ft_lstclear(gc);
		exit(1);
	}
	id[i] = fork();
	if (id[i] < 0)
	{
		perror("fork failed");
		(ft_lstclear(gc), exit(1));
	}
}

int count_cmd(t_node *cmd)
{
	int i;

	i = 0;
	while (cmd != NULL)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

void malloc_fd_id(int **id, t_cmd *file_des, int count, t_node **gc)
{
	int i;

	i = 0;
	*id = gc_malloc(gc, count * sizeof(int));
	file_des->fd = gc_malloc(gc, count * sizeof(int *));
	while (i < count)
	{
		(file_des->fd)[i] = gc_malloc(gc, 2 * sizeof(int));
		i++;
	}
}

void ft_exc_cmd(t_node *line, t_node **gc, t_cmd *env)
{
	int *id;
	int count;
	int i;
	int her;

	i = 0;
	env->her = 0;
	count = count_cmd(line) + count_herdoc(line);
	malloc_fd_id(&id, env, count + 1, gc);
	while (line != NULL)
	{
		tokenisation(line->data, gc, env);
		handle_quotes(env, gc);
		if (env->heredoc != NULL)
			ft_find_herdoc(env, &i, id, gc);
		if ((count_cmd(line) == 1) && (i == 0))
			if ((ft_check_buldin1(env, (char *)line->data, gc)) == 0)
			{
				ft_check_buldin(env, (char *)line->data, gc);
				break;
			}
		ft_fork_pipe(env, id, i, gc);
		if (id[i] == 0)
		{
			env->her = ft_file((char *)line->data);
			if (count == 1)
				ft_one_child(i, gc, env);
			else
			{
				if (i == 0)
					ft_first_child(i, gc, env, (char *)line->data);
				else if (i + 1 == count)
					ft_last_child(i, gc, env, (char *)line->data);
				else
					ft_midll_child(i, gc, env, (char *)line->data);
			}
		}
		else
		{
			if (i == 0)
				close((env->fd)[i][1]);
			else
			{
				close((env->fd)[i][1]);
				close((env->fd)[i - 1][0]);
			}
		}
		line = line->next;
		i++;
	}
	i = -1;
	while (++i < count)
		waitpid(id[i], NULL, 0);
	ft_lstclear(gc);
}
