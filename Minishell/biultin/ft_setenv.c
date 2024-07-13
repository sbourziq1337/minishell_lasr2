#include "../minishell.h"

char *ft_find_old_pwd(char *pwd, t_cmd *token)
{
    t_env	*head;
	t_node	*ft;
	char	*new_value;

	head = token->addres_env;
	ft = token->addres_fd;
	while (head != NULL)
	{
		if (ft_strcmp(head->name, pwd) == 0)
			return(head->value);
		head = head->next;
	}
    return (NULL);
}

void	ft_set_old(char *pwd, char *cwd, t_cmd *token)
{
	int		i;
	char	*key;
	t_node	*ft;
	char	*join;
	char	*tmp;

	i = 0;
	ft = token->addres_fd;
	key = NULL;
	join = NULL;
	while (token->env[i] != NULL)
	{
		key = ft_substr(token->env[i], 0, ft_strlen_untile_char(token->env[i],
					'='), &ft);
		if (ft_strcmp(key, pwd) == 0)
		{
			join = ft_strjoin(&ft, pwd, cwd);
			token->env[i] = ft_strdup(&ft, join);
			break ;
		}
		free(key);
		i++;
	}
}

void	ft_setenv(char *pwd, char *cwd, t_cmd *token)
{
	int		i;
	char	*key;
	t_node	*ft;
	char	*join;
	char	*tmp;

	i = 0;
	ft = token->addres_fd;
	key = NULL;
	join = NULL;
	while (token->env[i] != NULL)
	{
		key = ft_substr(token->env[i], 0, ft_strlen_untile_char(token->env[i],
					'='), &ft);
		if (ft_strcmp(key, pwd) == 0)
		{
			tmp = ft_strjoin(&ft, pwd, "=");
			join = ft_strjoin(&ft, tmp, cwd);
			token->env[i] = ft_strdup(&ft, join);
			free(tmp);
			break ;
		}
		free(key);
		i++;
	}
}

void	ft_set_old_pwd(char *pwd, t_cmd *token)
{
    t_env	*head;
	t_node	*ft;
	char	*new_value;
    char *old_pwd;

	head = token->addres_env;
	ft = token->addres_fd;
    old_pwd = ft_find_old_pwd("PWD",token);
    if(old_pwd == NULL)
        return;
	while (head != NULL)
	{
		if (ft_strcmp(head->name, pwd) == 0)
		{
			head->value = ft_strdup(&ft,old_pwd);
             ft_set_old(pwd, head->value, token);
			break ;
		}
		head = head->next;
	}

}
void	ft_setexport(char *pwd, char *cwd, t_cmd *token)
{
	t_env	*head;
	t_node	*ft;
	char	*new_value;

	head = token->addres_env;
	ft = token->addres_fd;
    ft_set_old_pwd("OLDPWD", token);
	while (head != NULL)
	{
		if (ft_strcmp(head->name, pwd) == 0)
		{
			new_value = ft_strjoin(&ft, "=", cwd);
			head->value = ft_strdup(&ft, new_value);
			free(new_value);
			break ;
		}
		head = head->next;
	}
	ft_setenv(pwd, cwd, token);
}
