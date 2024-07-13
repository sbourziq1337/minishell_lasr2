#include "../minishell.h"

int find_char(char *str, char c)
{
    int i;
	int b;

    i = 0;
	b = 0;
	if(!str)
		return (0);
    while(str[i] != '\0')
    {
        if(str[i] == c)
            b++;
        i++;
    }
    return (b);
}
int ft_strlen_untile_char(char *str, char c)
{
    int i;

    i = 0;
    while(str[i] != '\0')
    {
        if(str[i] == c)
            break ;
        i++;
    }
    return (i);
}

void	ft_pwd(char *line, t_node **gc)
{
	char	*str;

	str = NULL;
	str = ft_strtrim(line, " ", gc);
	if (ft_strncmp(str, "pwd", 3) == 0)
	{
		ft_putstr_fd(getcwd(NULL, 0), 0);
		write(1, "\n", 1);
	}
}

static char	*ft_strstr(char *haystack, char *needle)
{
	int	i;
	int	j;

	i = 0;
	if (*needle == 0)
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		j = 0;
		while (haystack[i + j] == needle[j] && needle[j] != '\0')
			j++;
		if (j == ft_strlen(needle))
        {
            while(haystack[i] != '=')
                i++;
			return ((char *)&haystack[i] + 1);
        }
		i++;
	}
	return (NULL);
}

void    search_env(char *line, t_cmd *env)
{
    int i;
    int j = 0;
    int count;

    i = 0;
    count = 0;
    while (env->env[i])
    {
        j = 0;
        count = 0;
        while (env->env[i][j] != '=' && env->env[i][j] != '\0')
        {
            count++;
            j++;
        }
        if (ft_strncmp(env->env[i], line, count) == 0)
        {
            env->env_line = ft_strstr(env->env[i], line);
            break;
        }
        i++;
    }
    if (!env->env_line)
    {
        env->env_line = NULL;
    }
}

char *expand_quotes(char *line)
{
    int i, j, k;
    int len;
    int in_dq;
    int in_sq;
    char c;
    char *buffer;

    len = ft_strlen(line);
    in_dq = in_double_quote(line, len);
    in_sq = in_single_quote(line, len);
    buffer = (char *)malloc(sizeof(char) * (len + 1));
    if (!buffer)
        return NULL;
    j = 0;
    k = 0;
    while (k < len)
    {
        c = line[k];
        if (c == '\'' && !in_dq)
        {
            in_sq = !in_sq;
        }
        else if (c == '"' && !in_sq)
        {
            in_dq = !in_dq;
        }
        else
        {
            buffer[j++] = c;
        }
        k++;
    }
    buffer[j] = '\0';
    return buffer;
}

void ft_echo(char *line, t_cmd *env)
{
    char *s;
    int i;
    int flag;
    int n_flag_valid;

    i = 0;
    flag = 0;
    n_flag_valid = 1;

    if (ft_strcmp(env->cmd[0], "echo") == 0)
    {
        i = 4;
        while (line[i] == ' ')
            i++;
        while (ft_strncmp(&line[i], "-n", 2) == 0)
        {
            i += 2;
            while (line[i] == 'n')
                i++;
            if (line[i] != ' ' && line[i] != '\0')
            {
                n_flag_valid = 0;
                break;
            }
            if (line[i] == ' ')
            {
                flag = 1;
                while (line[i] == ' ')
                    i++;
            }
        }
        if (n_flag_valid)
        {
            s = &line[i];
        }
        else
        {
            while (i > 0 && line[i] != '-')
                i--;
            s = &line[i];
        }
        if (s)
        {
            while (*s)
            {
                if (ft_strncmp(s, "$", 1) == 0)
                {
                    s++;
                    search_env(s, env);
                    if (env->env_line != NULL)
                    {
                        s = env->env_line;
                    }
                }

                if (flag == 1 && n_flag_valid)
                {
                    s = expand_quotes(s);
                    ft_putstr_fd(s, 1);
                }
                else
                {
                    s = expand_quotes(s);
                    ft_putendl_fd(s, 1);
                }
                break;
            }
        }
    }
}

void	ft_cd(char *line, t_cmd *token)
{
	int		i;
	char	*cwd;
	char	*path;

	i = 0;
	while ((token->cmd)[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd((token->cmd)[0], 2);
		ft_putstr_fd(": too many arguments\n", 2);
	}
	else
	{
		if (i == 1 || ft_strcmp((token->cmd)[1], "~") == 0)
		{
			path = getenv("HOME");
			if (!path)
			{
				ft_putstr_fd("cd: HOME not set\n", 2);
				return;
			}
		}
		else
			path = (token->cmd)[1];
		
		if (chdir(path) == 0)
		{
			cwd = getcwd(NULL, 0);
			if (cwd)
			{
				ft_setexport("PWD", cwd, token);
				//free(cwd);
			}
			else
				perror("getcwd");
		}
		else
			perror(path);
	}
}

void	ft_exit(t_node **gc)
{
	ft_lstclear(gc);
	exit(1);
}