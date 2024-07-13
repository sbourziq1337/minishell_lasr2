#include "minishell.h"

char	*ft_strchr_hlber(char *s, int c, int *n)
{
	int	i;

	i = 0;
    *n = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
            (*n)++;
        else if((s[i] != (char)c) && ((*n) != 0))
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (s);
}

char	*ft_check_space(char *av, t_node **gc)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (av[i] != '\0')
		i++;
	str = (char *)gc_malloc(gc, (i + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '/';
    j = 0;
	i = 1;
	while (av[j] != '\0')
	{
		str[i] = av[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}