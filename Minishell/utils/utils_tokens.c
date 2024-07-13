/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:56:05 by hfafouri          #+#    #+#             */
/*   Updated: 2024/05/28 16:05:30 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_append(char *line1, int *i, t_node **gc, t_cmd *token)
{
    char *word;
    int j;

    *i += 2;
    while (line1[*i] == ' ' || line1[*i] == '\t')
        (*i)++;
    if (line1[*i] != '>' && line1[*i] != '<' && line1[*i])
    {
        j = *i;
        while (line1[*i] && line1[*i] != ' ' && line1[*i] != '\t' && line1[*i] != '>' && line1[*i] != '<')
            (*i)++;
        word = gc_malloc(gc, *i - j + 1);
        ft_strcpy(word, &line1[j], *i - j);
        ft_lstadd_back(&token->append, ft_lstnew(word));
    }
}

void handle_outfile(char *line1, int *i, t_node **gc, t_cmd *token)
{
    char *word;
    int j;

    (*i)++;
    while (line1[*i] == ' ' || line1[*i] == '\t')
        (*i)++;
    if (line1[*i] != '>' && line1[*i] != '<' && line1[*i])
    {
        j = *i;
        while (line1[*i] && line1[*i] != ' ' && line1[*i] != '\t' && line1[*i] != '>' && line1[*i] != '<')
            (*i)++;
        word = gc_malloc(gc, *i - j + 1);
        ft_strcpy(word, &line1[j], *i - j);
        ft_lstadd_back(&token->outfile, ft_lstnew(word));
    }
}

void handle_heredoc(char *line1, int *i, t_node **gc, t_cmd *token)
{
    char *word;
    int j;

    *i += 2;
    while (line1[*i] == ' ' || line1[*i] == '\t')
        (*i)++;
    if (line1[*i] != '>' && line1[*i] != '<' && line1[*i])
    {
        j = *i;
        while (line1[*i] && line1[*i] != ' ' && line1[*i] != '\t' && line1[*i] != '>' && line1[*i] != '<')
            (*i)++;
        word = gc_malloc(gc, *i - j + 1);
        ft_strcpy(word, &line1[j], *i - j);
        ft_lstadd_back(&token->heredoc, ft_lstnew(word));
    }
}

void handle_infile(char *line1, int *i, t_node **gc, t_cmd *token)
{
    char *word;
    int j;

    (*i)++;
    while (line1[*i] == ' ' || line1[*i] == '\t')
        (*i)++;
    if (line1[*i] != '>' && line1[*i] != '<' && line1[*i])
    {
        j = *i;
        while (line1[*i] && line1[*i] != ' ' && line1[*i] != '\t' && line1[*i] != '>' && line1[*i] != '<')
            (*i)++;
        word = gc_malloc(gc, *i - j + 1);
        ft_strcpy(word, &line1[j], *i - j);
        ft_lstadd_back(&token->infile, ft_lstnew(word));
    }
}