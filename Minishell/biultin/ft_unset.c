#include "../minishell.h"

void	ft_remove_key_env(t_cmd *token, char *str)
{
	int		i;
	char	*key;
	t_node	*ft;

	i = 0;
	ft = token->addres_fd;
	while (token->env[i] != NULL)
	{
		key = ft_substr(token->env[i], 0, ft_strlen_untile_char(token->env[i],
					'='), &ft);
		if (ft_strcmp(key, str) == 0)
		{
            while(token->env[i + 1] != NULL)
            {
                token->env[i] = ft_strdup(&ft, token->env[i + 1]);
                i++;
            }
            break ;
		}
        i++;
	}
}

void	ft_remove_key_export(t_cmd *token, char *str)
{
	t_env	*head;
	t_node	*ft;
	int		i;

	head = token->addres_env;
	ft = token->addres_fd;
	i = 0;
	while (head != NULL)
	{
		if (ft_strcmp(head->name, str) == 0)
		{
			while (head->next != NULL)
			{
				head->name = ft_strdup(&ft, head->next->name);
				head->value = ft_strdup(&ft, head->next->value);
				head = head->next;
			}
			break ;
		}
		head = head->next;
	}
}

void	ft_unset(t_cmd *token, char *line)
{
	int i;

	i = 0;

	while (token->cmd[i] != NULL)
	{
		ft_remove_key_export(token, token->cmd[i]);
        ft_remove_key_env(token, token->cmd[i]);
		i++;
	}
}