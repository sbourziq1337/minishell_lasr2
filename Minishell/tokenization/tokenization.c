/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:40:39 by hfafouri          #+#    #+#             */
/*   Updated: 2024/06/09 17:07:44 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_commands(char *line1, int *i, t_node **gc, t_cmd *token)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (line1[*i])
	{
		while (line1[*i] == ' ' || line1[*i] == '\t')
			(*i)++;
		if (line1[*i] == '>' || line1[*i] == '<')
			break ;
		j = *i;
		if (line1[*i] == '\"')
		{
			(*i)++;
			while (line1[*i] != '\"' && line1[*i])
				(*i)++;
			if (line1[*i] == '\"')
				(*i)++;
		}
		while (line1[*i] && line1[*i] != ' ' && line1[*i] != '\t'
			&& line1[*i] != '>' && line1[*i] != '<')
			(*i)++;
		token->cmd_count++;
	}
	if (token->cmd_count == 0)
	{
		token->cmd = NULL;
		return ;
	}
	token->cmd = gc_malloc(gc, (token->cmd_count + 1) * sizeof(char *));
	*i = 0;
	k = 0;
	while (line1[*i])
	{
		while (line1[*i] == ' ' || line1[*i] == '\t')
			(*i)++;
		if (line1[*i] == '>' || line1[*i] == '<')
			break ;
		j = *i;
		if (line1[*i] == '\"')
		{
			(*i)++;
			while (line1[*i] != '\"' && line1[*i])
				(*i)++;
			if (line1[*i] == '\"')
				(*i)++;
		}
		while (line1[*i] && line1[*i] != ' ' && line1[*i] != '\t'
			&& line1[*i] != '>' && line1[*i] != '<')
				(*i)++;
		token->cmd[k] = gc_malloc(gc, *i - j + 1);
		ft_strcpy(token->cmd[k], &line1[j], *i - j);
		k++;
	}
	token->cmd[k] = NULL;
}

void	tokenisation(void *line, t_node **gc, t_cmd *token)
{
	char *line1;
	int i;

	token->infile = NULL;
	token->outfile = NULL;
	token->heredoc = NULL;
	token->append = NULL;
	token->cmd = NULL;
	token->cmd_count = 0;
	i = 0;
	line1 = ft_strtrim((char *)line, " ", gc);
	while (line1[i])
	{
		while (line1[i] == ' ' || line1[i] == '\t')
			i++;
		if (line1[i] == '>' && line1[i + 1] == '>')
			handle_append(line1, &i, gc, token);
		else if (line1[i] == '>')
			handle_outfile(line1, &i, gc, token);
		else if (line1[i] == '<' && line1[i + 1] == '<')
			handle_heredoc(line1, &i, gc, token);
		else if (line1[i] == '<')
					handle_infile(line1, &i, gc, token);
		else
			parse_commands(line1, &i, gc, token);
	}
	if (token->cmd_count == 0)
	{
		token->cmd = ft_split("", ':', gc);
	}
}
