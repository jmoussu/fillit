/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 11:01:32 by lubenard          #+#    #+#             */
/*   Updated: 2018/12/28 11:19:53 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_tetri		*new_tetrimino(void)
{
	t_tetri		*list;

	if (!(list = (t_tetri *)malloc(sizeof(t_tetri))))
		return (0);
	if (!(list->tetrimino = (char **)malloc(sizeof(char) * 5)) || \
		!(list->tetrimino[0] = (char *)malloc(sizeof(char) * 5)) || \
		!(list->tetrimino[1] = (char *)malloc(sizeof(char) * 5)) || \
		!(list->tetrimino[2] = (char *)malloc(sizeof(char) * 5)) || \
		!(list->tetrimino[3] = (char *)malloc(sizeof(char) * 5)))
		return (NULL);
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

char		putletter(void)
{
	static char letter = 'A';

	return (letter++);
}

int			compute(t_tetri *lkd_list, t_tetri *new_element, int i, char *str)
{
	char *test;

	while (str[i])
	{
		test = ft_strsub(str, i, 4);
		ft_strcpy(lkd_list->tetrimino[0], test);
		ft_strdel(&test);
		while (str[i] != '\n')
			i++;
		
		test = ft_strsub(str, ++i, 4);
		ft_strcpy(lkd_list->tetrimino[1], test);
		ft_strdel(&test);
		while (str[i] != '\n')
			i++;
		
		test = ft_strsub(str, ++i, 4);
		ft_strcpy(lkd_list->tetrimino[2], test);
		ft_strdel(&test);
		while (str[i] != '\n')
			i++;
		
		test = ft_strsub(str, ++i, 4);
		ft_strcpy(lkd_list->tetrimino[3], test);
		ft_strdel(&test);
		while (str[i] != '\n')
			i++;
		i += 2;
		if (verif_tetrimino(lkd_list->tetrimino) == -1)
		{
			free(lkd_list->tetrimino[0]);
			free(lkd_list->tetrimino[1]);
			free(lkd_list->tetrimino[2]);
			free(lkd_list->tetrimino[3]);
			lkd_list->prev->next = NULL;
			//free(lkd_list);    //essayer de faire marcher ca
			return (-1);
		}
		optimize_tetri(lkd_list->tetrimino);
		make_coord_p(lkd_list);
		lkd_list->letter = putletter();
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
	t_tetri		*first_element;
	int			i;

	i = 0;
	new_element = NULL;
	if (!(lkd_list = new_tetrimino()))
		return (NULL);
	first_element = lkd_list;
	if (compute(lkd_list, new_element, i, str) == -1)
	{
		while (lkd_list->next != NULL)
		{
			printf("AVANT\nLettre = %c\nlkd_list->tetrimino[0] = %s\nlkd_list->tetrimino[1] = %s\nlkd_list->tetrimino[2] = %s\nlkd_list->tetrimino[3] = %s\nnext = %p\n\n", lkd_list->letter, lkd_list->tetrimino[0], lkd_list->tetrimino[1], lkd_list->tetrimino[2], lkd_list->tetrimino[3], lkd_list->next);
			//free(lkd_list->tetrimino[0]); //erreur de double free, but WTF
			free(lkd_list->tetrimino[1]);
			free(lkd_list->tetrimino[2]);
			free(lkd_list->tetrimino[3]);
			//free(lkd_list->tetrimino);    //Erreurs de invalid next size
			//free(first_element->prev);
			printf("APRES\nLettre = %c\nlkd_list->tetrimino[0] = %s\nlkd_list->tetrimino[1] = %s\nlkd_list->tetrimino[2] = %s\nlkd_list->tetrimino[3] = %s\nnext = %p\n\n", lkd_list->letter, lkd_list->tetrimino[0], lkd_list->tetrimino[1], lkd_list->tetrimino[2], lkd_list->tetrimino[3], lkd_list->next);
			lkd_list = lkd_list->next;
			//free(first_element->prev->prev); error
			//free(lkd_list);             //erreur de double free or corruption
		}
		return (NULL);
	}
	ft_strdel(&str);
	return (first_element);
}
