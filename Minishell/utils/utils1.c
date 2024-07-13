/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:56:03 by hfafouri          #+#    #+#             */
/*   Updated: 2024/05/28 16:02:01 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_strcpy(char *s1, char *s2, int len)
{
    int i;

    i = 0;
    while (s2[i] && len > 0)
    {
        s1[i] = s2[i];
        i++;
        len--;
    }
    s1[i] = '\0';
    return s1;
}
static char check(const char *set, char c)
{
    while (*set && c != *set)
        set++;
    return (c == *set);
}

char *ft_strtrim(char *s1, char *set, t_node **gc)
{
    size_t first;
    size_t last;

    if (!s1 || !set)
        return ("");
    first = 0;
    last = ft_strlen((char *)s1);
    while (first < last && check(set, s1[first]))
        first++;
    if (first == last)
        return ("");
    while (last > 0 && check(set, s1[last - 1]))
        last--;
    return (ft_substr(s1, first, last - first, gc));
}
