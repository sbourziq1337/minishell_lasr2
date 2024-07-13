#include "../minishell.h"

void	ft_remove_quotes(t_cmd *token)
{
	t_env	*head;
	t_node	*gc;

	head = token->addres_env;
	gc = token->addres_fd;
	while (head != NULL)
	{
		head->value = expand_quotes(head->value);
		head = head->next;
	}
}
void	ft_add_qiotes(t_cmd *token)
{
	t_env	*head;
	t_node	*gc;
	char	*s;

	head = token->addres_env;
	gc = token->addres_fd;
	while (head != NULL)
	{
		if (head->value[0] == '=')
		{
			s = gc_malloc(&gc, ft_strlen(head->value) + 3);
			s = "=\"";
			s = ft_strjoin(&gc, s, (head->value + 1));
			s = ft_strjoin(&gc, s, "\"");
			head->value = ft_strdup(&gc, s);
		}
		head = head->next;
	}
}

int	ft_check_path_env(t_cmd *token)
{
	int		i;
	int		b;
	char	*key;
	t_node	*ft;

	i = 0;
	b = 1;
	ft = token->addres_fd;
	while (token->env[i] != NULL)
	{
		key = ft_substr(token->env[i], 0, ft_strlen_untile_char(token->env[i],
					'='), &ft);
		if (ft_strcmp(key, "PATH") == 0)
			b = 0;
		i++;
	}
	return (b);
}
void	ft_env(t_cmd *token)
{
	int	i;

	i = 0;
	while (token->cmd[i] != NULL)
	{
		if (ft_strcmp(token->cmd[i], "env") != 0)
		{
			write(2, token->cmd[i], ft_strlen(token->cmd[1]));
			if (token->cmd[i][0] == '.' && token->cmd[i][1] == '/')
				write(2, ": Permission denied\n", 21);
			else
				write(2, ": No such file or directory\n", 29);
			return ;
		}
		i++;
	}
	i = 0;
	if(token->flag == 1)
	{
		while (token->env[i] != NULL)
		{
			printf("%s\n", token->env[i]);
			i++;
		}
		return;
	}
	if (ft_check_path_env(token) == 0)
	{
		while (token->env[i] != NULL)
		{
			printf("%s\n", token->env[i]);
			i++;
		}
	}
	else
		write(2, "env: No such file or directory\n", 32);
}

void	ft_add_env(char *value, char *name, t_cmd *token)
{
	int		i;
	char	*join;
	char	*key;
	char	*value1;
	char	*new_node;
	t_node	*ft;

	i = 0;
	join = NULL;
	key = NULL;
	value1 = NULL;
	ft = token->addres_fd;
	new_node = ft_substr(name, 0, ft_strlen_untile_char(name, '+'), &ft);
	while (token->env[i] != NULL)
	{
		key = ft_substr(token->env[i], 0, ft_strlen_untile_char(token->env[i],
					'='), &ft);
		value1 = ft_strchr(token->env[i], '=');
		if (ft_strcmp(key, new_node) == 0)
		{
			if (name[ft_strlen(name) - 1] == '+')
				token->env[i] = ft_strjoin(&ft, token->env[i], value + 1);
			else
			{
				join = ft_strjoin(&ft, name, value);
				token->env[i] = ft_strdup(&ft, join);
			}
			return ;
		}
		free(key);
		i++;
	}
	join = ft_strjoin(&ft, name, value);
	token->env[i] = ft_strdup(&ft, join);
	token->env[i + 1] = NULL;
	free(join);
}
void	ft_sort_env_list(t_cmd *token)
{
	t_env	*head;
	t_node	*ft;
	char	*env_copy_name;
	char	*env_copy_value;
	int		swapped;
	t_env	*current;

	if (token == NULL || token->addres_env == NULL)
		return ;
	head = token->addres_env;
	ft = token->addres_fd;
	while (1)
	{
		swapped = 0;
		current = head;
		while (current != NULL && current->next != NULL)
		{
			if (strcmp(current->name, current->next->name) > 0)
			{
				env_copy_name = ft_strdup(&ft, current->name);
				env_copy_value = ft_strdup(&ft, current->value);
				free(current->name);
				free(current->value);
				current->name = current->next->name;
				current->value = current->next->value;
				current->next->name = env_copy_name;
				current->next->value = env_copy_value;
				swapped = 1;
			}
			current = current->next;
		}
		if (!swapped)
			break ;
	}
}

void	ft_print_export(t_cmd *token)
{
	t_env	*temp;

	temp = token->addres_env;
	ft_remove_quotes(token);
	ft_add_qiotes(token);
	while (temp != NULL)
	{
		if (temp->value != NULL)
			printf("declare -x %s%s\n", temp->name, temp->value);
		else
			printf("declare -x %s\n", temp->name);
		temp = temp->next;
	}
}

void	ft_add_value_to_export(t_cmd *token, char *line)
{
	t_env	*head;
	t_node	*ft;
	char	**str;
	char	*name;
	char	*value;
	char	*env_copy;
	int		i;
	t_env	*new_node;
	t_env	*current;
	t_env	*prev;

	head = token->addres_env;
	ft = token->addres_fd;
	str = ft_split_qoute(line, ' ', &ft);
	ft_remove_quotes(token);
	name = NULL;
	value = NULL;
	env_copy = NULL;
	i = 1;
	while (str[i] != NULL)
	{
		env_copy = strdup(str[i]);
		if (!env_copy)
			return ;
		name = ft_substr(env_copy, 0, ft_strlen_untile_char(env_copy, '='),
				&ft);
		value = ft_strchr(env_copy, '=');
		// remove the sngle and double qoute for name
		name = expand_quotes(name);
		value = expand_quotes(value);
		// check is we have valid indentifier
		if (name == NULL || name[0] == '\0' || (ft_isalpha(name) == 0))
		{
			// i have same errror in this line
			printf("export: %s", value);
			if (name[0] == '-')
				printf(": invalid option\n");
			else
				printf(": not a valid identifier\n");
			free(env_copy);
			return ;
		}
		new_node = (t_env *)malloc(sizeof(t_env));
		if (!new_node)
		{
			free(env_copy);
			return ;
		}
		new_node->name = ft_substr(name, 0, ft_strlen_untile_char(name, '+'),
				&ft);
		new_node->value = ft_strdup(&ft, value);
		new_node->next = NULL;
		// Check if the variable already exists
		current = head;
		prev = NULL;
		while (current != NULL)
		{
			if (strcmp(current->name, new_node->name) == 0)
			{
				if (name[ft_strlen(name) - 1] == '+')
				{
					if (current->value == NULL)
						current->value = ft_strjoin(&ft, current->value,
								(new_node->value));
					else
						current->value = ft_strjoin(&ft, current->value,
								(new_node->value + 1));
				}
				else
				{
					if (value != NULL)
						current->value = ft_strdup(&ft, value);
				}
				break ;
			}
			prev = current;
			current = current->next;
		}
		// add varialble to the env
		if (value != NULL && value[0] != '\0')
			ft_add_env(value, name, token);
		// If variable doesn't exist, add it to the list
		if (current == NULL)
		{
			if (prev == NULL)
				token->addres_env = new_node;
			else
				prev->next = new_node;
		}
		free(env_copy);
		i++;
	}
	ft_add_qiotes(token);
}

void	ft_export(t_cmd *token, char *line)
{
	if (token->cmd[1] == NULL)
		ft_print_export(token);
	ft_add_value_to_export(token, line);
}
