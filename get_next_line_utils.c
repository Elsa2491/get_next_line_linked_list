/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:57:18 by eltouma           #+#    #+#             */
/*   Updated: 2023/09/18 15:57:44 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstlast(t_list *node)
{
	if (!node)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	return (node);
}

int	ft_lstsize(t_list *node)
{
	int	i;
	int	j;

	j = 0;
	while (node)
	{
		i = 0;
		while (node->content[i] != '\0')
		{
			if (node->content[i] == '\n')
			{
				j += 1;
				return (j);
			}
			i += 1;
			j += 1;
		}
		node = node->next;
	}
	return (j);
}

void	ft_strcpy(t_list *node, char *line)
{
	int	i;
	int	j;

	j = 0;
	while (node)
	{
		i = 0;
		while (node->content[i] != '\0')
		{
			if (node->content[i] == '\n')
			{
				line[j] = '\n';
				line[j + 1] = '\0';
				return ;
			}
			line[j] = node->content[i];
			j += 1;
			i += 1;
		}
		node = node->next;
	}
	line[j] = '\0';
}

void	ft_dealloc(t_list **list, t_list *node_rest, char *rest)
{
	t_list	*tmp;

	if (!*list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (node_rest->content[0])
		*list = node_rest;
	else
	{
		free(rest);
		free(node_rest);
	}
}

void	ft_lstclean(t_list **list)
{
	t_list	*node_rest;
	t_list	*last_node;
	int		i;
	int		j;
	char	*rest;

	j = 0;
	i = 0;
	if (!*list)
		return ;
	rest = malloc(BUFFER_SIZE + 1);
	node_rest = malloc(sizeof(t_list));
	if (!rest || !node_rest)
		return ;
	last_node = ft_lstlast(*list);
	while (last_node->content[i] != '\0' && last_node->content[i] != '\n')
		i += 1;
	while (last_node->content[i] != '\0' && last_node->content[++i])
		rest[j++] = last_node->content[i];
	rest[j] = '\0';
	node_rest->content = rest;
	node_rest->next = NULL;
	ft_dealloc(list, node_rest, rest);
}
