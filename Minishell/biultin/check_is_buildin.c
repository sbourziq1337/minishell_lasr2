#include "../minishell.h"

void ft_history(t_cmd *token)
{
    t_history *head = token->history;
    while (head != NULL)
    {
        printf("%d  %s\n", head->number_of_history, head->history);
        head = head->next;
    }
}
int	checkchar(char a, char *b)
{
	int	i;

	i = ft_strlen(b);
	while (i >= 0)
	{
		if (b[i] == a)
			return (1);
		i--;
	}
	return (0);
}
char	*ft_strtrim1(char *s1, char *set, t_node **gc)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(gc, s1));
	j = ft_strlen(s1);
	if (j == 0)
	{
		str = (char *)malloc(1);
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	while (s1[i] && checkchar(s1[i], set))
		i++;
	while (s1[j - 1] && checkchar(s1[j], set) && i < j)
		j--;
	str = ft_substr(s1, i, j - i + 1, gc);
	return (str);
}

int	ft_isalpha(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] == '+')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			i++;
		else if ((str[i] >= 'A' && str[i] <= 'Z'))
			i++;
		else if (str[i] == '_')
			i++;
		else if (str[i] == '+' && str[i + 1] == '\0')
			i++;
		else if ((i != 0) && (str[i] >= '0' && str[i] <= '9'))
			i++;
		else
			return (0);
	}
	return (i);
}
void	ft_check_buldin(t_cmd *env, char *line, t_node **gc)
{
	if (ft_strcmp((env->cmd)[0], "pwd") == 0)
		ft_pwd(line, gc);
	else if (ft_strcmp((env->cmd)[0], "echo") == 0)
		ft_echo(line, env);
	else if (ft_strcmp((env->cmd)[0], "export") == 0)
		ft_export(env, line);
	else if (ft_strcmp((env->cmd)[0], "cd") == 0)
		ft_cd(line, env);
	else if (ft_strcmp((env->cmd)[0], "exit") == 0)
		ft_exit(gc);
	else if (ft_strcmp((env->cmd)[0], "env") == 0)
		ft_env(env);
	else if (ft_strcmp((env->cmd)[0], "unset") == 0)
		ft_unset(env, line);
	else if (ft_strcmp((env->cmd)[0], "history") == 0)
		ft_history(env);
}
int	ft_check_buldin1(t_cmd *env, char *line, t_node **gc)
{
	int	n;

	n = 1;
	if (ft_strcmp((env->cmd)[0], "pwd") == 0)
		n = 0;
	else if (ft_strcmp((env->cmd)[0], "echo") == 0)
		n = 0;
	else if (ft_strcmp((env->cmd)[0], "cd") == 0)
		n = 0;
	else if (ft_strcmp((env->cmd)[0], "exit") == 0)
		n = 0;
	else if (ft_strcmp((env->cmd)[0], "export") == 0)
		n = 0;
	else if (ft_strcmp((env->cmd)[0], "env") == 0)
		n = 0;
	else if (ft_strcmp((env->cmd)[0], "unset") == 0)
		n = 0;
	else if (ft_strcmp((env->cmd)[0], "history") == 0)
		n = 0;
	return (n);
}