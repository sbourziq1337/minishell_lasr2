#include "minishell.h"

 t_node	*ft_lstlast(t_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_node	*ft_lstnew(void *ptr)
{
	t_node	*str;

	str = (t_node *)malloc(sizeof(t_node));
	if (str == NULL)
		return (NULL);
	str->data = ptr;
	str->next = NULL;
	return (str);
}

void	ft_lstadd_back(t_node **lst, t_node *new)
{
	t_node	*ptr;

	if (new)
	{
		if (!*lst)
		{
			*lst = new;
			new->next = NULL;
			return ;
		}
		ptr = ft_lstlast(*lst);
		ptr->next = new;
	}
}

void	ft_lstclear(t_node **lst)
{
	t_node	*head;
	t_node	*copy;

	if (lst && *lst)
	{
		head = *lst;
		while (head != NULL)
		{
			copy = head;
			free(head->data);
			head = head->next;
			free(copy);
		}
		*lst = NULL;
	}
}

void	*gc_malloc(t_node **gc, int size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		ft_lstclear(gc);
		exit(1);
	}
	ft_lstadd_back(gc, ft_lstnew(ptr));
	return (ptr);
}