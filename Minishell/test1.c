
// #include "minishell.h"


// char	*ft_substr1(char *s, int start, int len, t_node **gc)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	str = (char *)malloc((len + 1) * sizeof(char));
// 	if (str == NULL)
// 		return (NULL);
// 	while (s[start] != '\0' && i < len)
// 	{
// 		str[i] = s[start];
// 		i++;
// 		start++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

// int ft_strlen_untile_char(char *str, char c)
// {
//     int i;

//     i = 0;
//     while(str[i] != '\0')
//     {
//         if(str[i] == c)
//             break ;
//         i++;
//     }
//     return (i);
// }
// t_env *init_env_list(char **envp) {
//     t_env *head = NULL;
//     t_env *new_node;
//     char *name;
//     char *value;
//     char *env_copy;
//     int i = 0;

//     while (envp[i] != NULL) {
//         env_copy = strdup(envp[i]);
//         if (!env_copy)
//             return NULL;

//         name = ft_substr1(env_copy, 0, ft_strlen_untile_char(env_copy, '='), NULL);
//         value = strchr(env_copy, '=');

//         new_node = malloc(sizeof(t_env));
//         if (!new_node) {
//             free(env_copy);
//             return NULL;
//         }

//         new_node->name = strdup(name);
//         new_node->value = strdup(value);
//         new_node->next = head;
//         head = new_node;

//         free(env_copy);
//         i++;
//     }
//     return head;
// }

// int main(int argc, char **argv, char **envp) {
//     t_env *env_list = init_env_list(envp);
//     t_env *temp = env_list;

//     while (temp != NULL) {
//         printf("Name: %s\n", temp->name);
//         temp = temp->next;
//     }

//     temp = env_list;
//     while (temp != NULL) {
//         t_env *next = temp->next;
//         free(temp->name);
//         free(temp->value);
//         free(temp);
//         temp = next;
//     }

//     return 0;
// }
