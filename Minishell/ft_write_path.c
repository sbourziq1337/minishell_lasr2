#include "minishell.h"

int	ft_strlen(char *s1)
{
	int	i;

	i = 0;
	if(s1 == NULL)
		return(0);
	while (s1[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(t_node **gc, char *s1)
{
	int		i;
	char	*str;

	if(!s1)
		return(NULL);
	str = gc_malloc(gc, ft_strlen(s1) * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	ft_loops(char *str, char *s1, int i)
{
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
}

static void	ft_loops2(char *str, char *s2, int count, int i)
{
	while (s2[i] != '\0')
	{
		str[count + i] = s2[i];
		i++;
	}
}

char	*ft_strjoin(t_node **gc, char  *s1, char  *s2)
{
	int		i;
	int		count;
	char	*str;
	int		len;

	i = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(gc, s2));
	else
		count = ft_strlen(s1);
	if (s2 == NULL)
		return (ft_strdup(gc, s1));
	else
		len = ft_strlen(s2);
	str = (char *)gc_malloc(gc, count + len + 1);
	if (str == NULL)
		return (NULL);
	ft_loops(str, s1, i);
	i = 0;
	ft_loops2(str, s2, count, i);
	str[count + len] = '\0';
	return (str);
}
