#include "minishell.h"

char	*ft_substr(char *s, int start, int len, t_node **gc)
{
	int		i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	str = (char *)gc_malloc(gc, (len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s[start] != '\0' && i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

static int	ft_count(char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else if (s[i] == c)
			i++;
	}
	return (count);
}

static char	**ft_checknull(char **str, int n)
{
	while (n > 0)
	{
		free(str[--n]);
	}
	free(str);
	return (0);
}

char	**ft_split(char *s, char c, t_node **gc)
{
	int		i;
	int		n;
	int		j;
	char	**str;

	str = (char **)gc_malloc(gc, (ft_count(s, c) + 1) * sizeof(char *));
	if (str == NULL)
		return (NULL);
	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		j = 0;
		while (s[i] != c && s[i] != '\0' && j++ > -1)
			i++;
		str[n++] = ft_substr(s, i - j, j, gc);
		if (!str[n - 1])
			return (ft_checknull(str, n));
	}
	str[n] = NULL;
	return (str);
}