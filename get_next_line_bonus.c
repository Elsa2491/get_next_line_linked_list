/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:32:17 by eltouma           #+#    #+#             */
/*   Updated: 2023/09/18 16:09:38 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strchr(t_list *node)
{
	int	i;

	if (!node)
		return (0);
	while (node)
	{
		i = 0;
		while (node->content[i] != '\0' && i < BUFFER_SIZE)
		{
			if (node->content[i] == '\n')
				return (1);
			i += 1;
		}
		node = node->next;
	}
	return (0);
}

void	ft_lstadd_back(t_list **list, char *buff, int fd)
{
	t_list	*last_node;
	t_list	*new_node;

	last_node = ft_lstlast(list[fd]);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	if (!last_node)
		list[fd] = new_node;
	else
		last_node->next = new_node;
	new_node->content = buff;
	new_node->next = NULL;
}

void	ft_lstcreate(t_list **list, int fd)
{
	int		read_bytes;
	char	*buff;

	while (!ft_strchr(list[fd]))
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return ;
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (!read_bytes)
		{
			free(buff);
			return ;
		}
		buff[read_bytes] = '\0';
		ft_lstadd_back(list, buff, fd);
	}
}

char	*get_line(t_list *node)
{
	int		str_size;
	char	*line;

	if (!node)
		return (NULL);
	str_size = ft_lstsize(node);
	line = malloc(str_size + 1);
	if (!line)
		return (NULL);
	ft_strcpy(node, line);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*list[1024];
	char			*next_line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	ft_lstcreate(list, fd);
	if (!list[fd])
		return (NULL);
	next_line = get_line(list[fd]);
	ft_lstclean(&list[fd]);
	return (next_line);
}
