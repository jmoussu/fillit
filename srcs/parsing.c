/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoussu <jmoussu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 11:01:32 by lubenard          #+#    #+#             */
/*   Updated: 2019/01/13 05:15:07 by jmoussu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_tetri		*new_tetrimino(void)
{
	t_tetri		*list;

	if (!(list = (t_tetri *)malloc(sizeof(t_tetri))))
		return (0);
	if (!(list->tetrimino = (char **)malloc(sizeof(char *) * 4)))
		return (NULL);
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

int			loop_parsing(t_tetri *lkd_list, int i, char *str)
{
	lkd_list->tetrimino[0] = ft_strsub(str, i, 4);
	i = compute_parsing(str, i);
	lkd_list->tetrimino[1] = ft_strsub(str, ++i, 4);
	i = compute_parsing(str, i);
	lkd_list->tetrimino[2] = ft_strsub(str, ++i, 4);
	i = compute_parsing(str, i);
	lkd_list->tetrimino[3] = ft_strsub(str, ++i, 4);
	i = compute_parsing(str, i);
	return (i);
}

void		compute_parsing_2(t_tetri *lkd_list)
{
	optimize_tetri(lkd_list->tetrimino);
	make_coord_p(lkd_list);
	lkd_list->letter = putletter();
}

int			compute(t_tetri *lkd_list, t_tetri *new_element, int i, char *str)
{
	while (str[i])
	{
		i = loop_parsing(lkd_list, i, str);
		i += 2;
		if (verif_tetrimino(lkd_list->tetrimino) == -1)
		{
			if (lkd_list->prev == NULL)
			{
				free_tetri(lkd_list);
				return (-2);
			}
			lkd_list->prev->next = lkd_list;
			return (-1);
		}
		compute_parsing_2(lkd_list);
		if (str[i - 1] != '\0')
		{
			if (!(new_element = new_tetrimino()))
				return (-1);
			lkd_list->next = new_element;
			lkd_list->next->prev = lkd_list;
			lkd_list = new_element;
		}
	}
	return (0);
}

t_tetri		*parsing(char *str)
{
	t_tetri		*lkd_list;
	t_tetri		*new_element;
	int			i;
	t_tetri		*tmp;
	int			j;

	i = 0;
	new_element = NULL;
	if (!(lkd_list = new_tetrimino()))
		return (NULL);
	j = compute(lkd_list, new_element, i, str);
	if (j == -1)
	{
		while (lkd_list)
		{
			tmp = lkd_list->next;
			free_tetri(lkd_list);
			lkd_list = tmp;
		}
		return (NULL);
	}
	else if (j == -2)
		return (NULL);
	ft_strdel(&str);
	return (lkd_list);
}
