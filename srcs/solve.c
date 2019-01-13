/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoussu <jmoussu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 10:59:54 by lubenard          #+#    #+#             */
/*   Updated: 2019/01/13 05:55:50 by jmoussu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		compute_end(int *r, t_tetri **t, char ***m, int *s)
{
	int	i;

	i = 0;
	if (*r == 1)
	{
		*r = 0;
		return (1);
	}
	if ((*t)->letter == 'A' && (*t)->prev == NULL)
	{
		remove_end(*t, *m);
		while (i < 20)
			free((*m)[i++]);
		free(*m);
		i = 0;
		*m = ini_map(++(*s), 20);
		return (1);
	}
	if ((*t)->letter != 'A' && (*t)->prev != NULL)
	{
		remove_end(*t, *m);
		*t = (*t)->prev;
		remove_p(*t, *m);
	}
	return (0);
}

int		w(t_var *var, t_tetri **t, char ***m, t_coord *pm)
{
	while ((*pm).x != (*var).s)
	{
		if (!(place(*t, *m, *pm)))
		{
			if ((*t)->next == NULL)
				return (1);
			else
			{
				*t = (*t)->next;
				(*var).r = 1;
				return (0);
			}
		}
		(*pm).x++;
	}
	return (0);
}

void	posx(t_tetri **t, t_coord *pm)
{
	if ((*t)->pos.x == -1)
		(*pm).x = 0;
	else
	{
		(*pm).x = (*t)->pos.x + 1;
		(*t)->pos.x = -1;
	}
}

char	**compute_solve(t_coord pm, t_tetri *t, char **m, t_var var)
{
	var.r = 0;
	while (1)
	{
		if (t->pos.y == -1)
			pm.y = 0;
		else
			pm.y = t->pos.y;
		while (pm.y != var.s)
		{
			posx(&t, &pm);
			if (w(&var, &t, &m, &pm) == 1)
				return (m);
			if (var.r == 1)
				break ;
			pm.x = -1;
			pm.y++;
		}
		if (compute_end(&(var.r), &t, &m, &(var.s)) == 1)
			continue ;
	}
	return (NULL);
}

char	**solve(t_tetri *t)
{
	char	**m;
	t_var	var;
	t_coord	pm;
	char	**ret_val;

	var.s = 2;
	pm.x = 0;
	pm.y = 0;
	m = ini_map(var.s, 20);
	ret_val = compute_solve(pm, t, m, var);
	if (ret_val != NULL)
		return (ret_val);
	return (m);
}
