#include "minishell.h"

void	ft_access_to_path(t_node **gc, char **str, char *path_cmd)
{
	if (access(path_cmd, F_OK) == 0)
	{
		if (access(path_cmd, X_OK) == 0)
			*str = path_cmd;
		else
			(perror(path_cmd), exit(127));
	}
}