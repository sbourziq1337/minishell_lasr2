#include "../minishell.h"

static int	ft_count_tokens(const char *s, char c)
{
	int		count;
	int		i;
	int		in_quote;
	char	quote_char;

	count = 0;
	i = 0;
	in_quote = 0;
	quote_char = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			if (in_quote && s[i] == quote_char)
			{
				in_quote = 0;
				quote_char = 0;
			}
			else if (!in_quote)
			{
				in_quote = 1;
				quote_char = s[i];
			}
		}
		else if (s[i] == c && !in_quote)
		{
			count++;
			while (s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (i > 0 && s[i - 1] != c)
		count++;
	return (count);
}

static char	**ft_checknull(char **str, int n)
{
	while (n-- > 0)
		free(str[n]);
	free(str);
	return (NULL);
}

char	**ft_split_qoute(char *s, char c, t_node **gc)
{
	char	**tokens;
	int		i;
	int		n;
	int		start;
	int		in_quote;
	char	quote_char;

	if (!s)
		return (NULL);
	i = 0;
	n = 0;
	in_quote = 0;
	quote_char = 0;
	tokens = (char **)gc_malloc(gc, (ft_count_tokens(s, c) + 1)
			* sizeof(char *));
	if (!tokens)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		start = i;
		while (s[i])
		{
			if (s[i] == '"' || s[i] == '\'')
			{
				if (!in_quote)
				{
					in_quote = 1;
					quote_char = s[i];
				}
				else if (in_quote && s[i] == quote_char)
				{
					in_quote = 0;
					quote_char = 0;
				}
			}
			else if (s[i] == c && !in_quote)
				break ;
			i++;
		}
		tokens[n] = ft_substr(s, start, i - start, gc);
		if (!tokens[n])
			return (ft_checknull(tokens, n));
		n++;
	}
	tokens[n] = NULL;
	return (tokens);
}
