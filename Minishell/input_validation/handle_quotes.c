/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:17:52 by hfafouri          #+#    #+#             */
/*   Updated: 2024/07/05 11:39:26 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	in_single_quote(char *line, int index)
{
	int	i;
	int	in_sq;

	i = 0;
	in_sq = 0;
	while (i < index)
	{
		if (line[i] == '\'' && !in_double_quote(line, i))
		{
			in_sq = !in_sq;
		}
		i++;
	}
	return (in_sq);
}

int	in_double_quote(char *line, int index)
{
	int	i;
	int	in_dq;

	i = 0;
	in_dq = 0;
	while (i < index)
	{
		if (line[i] == '"' && !in_single_quote(line, i))
		{
			in_dq = !in_dq;
		}
		i++;
	}
	return (in_dq);
}

void	handle_quotes(t_cmd *cmd, t_node **gc)
{
	int i;
	int j;
	int len;
	int in_dq;
	int in_sq;
	char c;
	char *buffer;
	char *line;
    i = 0;
    
	while (cmd->cmd[i])
	{
		line = cmd->cmd[i];
		len = ft_strlen(line);
		in_dq = in_double_quote(line, len);
		in_sq = in_single_quote(line, len);
		buffer = (char *)gc_malloc(gc, sizeof(char) * (len + 1));
		if (!buffer)
			return ;
		j = 0;
        int k = 0;
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
			// else if (c == '\\' && in_dq)
			// {
			// 	if (line[k + 1] == '"' || line[k + 1] == '\\' || line[k
			// 		+ 1] == '$')
			// 	{
			// 		buffer[j++] = line[++k];
			// 	}
			// 	else
			// 	{
			// 		buffer[j++] = '\\';
			// 	}
			// }
			else
			{
				buffer[j++] = c;
			}
            k++;
		}
		buffer[j] = '\0';
		cmd->cmd[i] = buffer;
        i++;
	}
}