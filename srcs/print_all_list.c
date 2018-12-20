/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoussu <jmoussu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 17:39:03 by jmoussu           #+#    #+#             */
/*   Updated: 2018/12/20 16:59:05 by jmoussu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	print_list(t_tetri *t)
{
	if (t->next == NULL)
		ft_putstr("\nLAST TETRIMINOS\n");
	else
		ft_putstr("\nNEW NEW TETRIMINOS\n");
	ft_putstr("Le Char **:\n");
	ft_putstr(t->tetrimino[0]);
	ft_putchar('\n');
	ft_putstr(t->tetrimino[1]);
	ft_putchar('\n');
	ft_putstr(t->tetrimino[2]);
	ft_putchar('\n');
	ft_putstr(t->tetrimino[3]);
	ft_putchar('\n');
	ft_putstr("Les 4 coordonées\n");
	ft_putnbr(t->c[0].x);
	ft_putchar('\t');
	ft_putnbr(t->c[0].y);
	ft_putchar('\n');
	ft_putnbr(t->c[1].x);
	ft_putchar('\t');
	ft_putnbr(t->c[1].y);
	ft_putchar('\n');
	ft_putnbr(t->c[2].x);
	ft_putchar('\t');
	ft_putnbr(t->c[2].y);
	ft_putchar('\n');
	ft_putnbr(t->c[3].x);
	ft_putchar('\t');
	ft_putnbr(t->c[3].y);
	ft_putchar('\n');
	ft_putstr("La position\n");
	ft_putnbr(t->pos.x);
	ft_putchar('\t');
	ft_putnbr(t->pos.y);
	ft_putchar('\n');
	ft_putstr("La lettre\n");
	ft_putnbr(t->letter);
	ft_putchar('\n');
}

void	print_all_list(t_tetri *t)
{
	int i;

	i = 0;
	ft_putstr("\nDEBUT DE LA LISTE\n");
	while (t->next != NULL)
	{
		i++;
		print_list(t);
		t = t->next;
	}
	i++;
	print_list(t);
	ft_putstr("Le nombre de pièce de la liste est egale à : ");
	ft_putnbr(i);
	ft_putchar('\n');
	while (t->prev != NULL)
		t = t->prev;
}
