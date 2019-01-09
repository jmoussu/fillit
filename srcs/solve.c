/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoussu <jmoussu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 10:59:54 by lubenard          #+#    #+#             */
/*   Updated: 2019/01/09 22:28:35 by jmoussu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	**compute_solve(t_coord pmap, t_tetri *t, char **map, int size)
{
	int relaunch;
	int i;
	i = 0;
	relaunch = 0;
	while (1)
	{
		if (t->pos.y == -1)
			pmap.y = 0; // 0 si pos = -1 sinon recuperer pos je supose
		else
			pmap.y = t->pos.y;
		while (pmap.y != size)
		{
			if (t->pos.x == -1)
				pmap.x = 0;
			else
			{
				pmap.x = t->pos.x + 1;
				t->pos.x = -1;
			}
			while (pmap.x != size)
			{
				if (!(place(t, map, pmap)))
				{
					if (t->next == NULL)
						return (map);
					else
					{
						t = t->next;
						relaunch = 1;
						break ;
					}
				}
				pmap.x++;
			}
			if (relaunch == 1)
				break ;
			pmap.x = -1;
			pmap.y++;
		}
		if (relaunch == 1)
		{
			relaunch = 0;
			continue ;
		}
		if (t->letter == 'A' && t->prev == NULL)
		{
			remove_end(t, map);
			t->pos.y = -1; // mettre dans remove_end meme si erreur
			t->pos.x = -1;
			while (i < 20)
				free(map[i++]);
			free(map);
			i = 0;
			map = ini_map(++size, 20);// free map ou leaks NON, SANS BLAGUE
			continue ;
		}
		else if (t->letter != 'A' && t->prev != NULL)
		{
			remove_end(t, map);
			t->pos.y = -1; // mettre dans remove_end meme si erreur
			t->pos.x = -1;
			t = t->prev;
			remove_p(t, map);
		}
		else
			ft_putstr("Wtf\n");
	}
	return (NULL);
}

char	**solve(t_tetri *t)
{
	char	**map;
	int		size;
	t_coord	pmap;
	char	**ret_val;
	size = 2;
	pmap.x = 0;
	pmap.y = 0;
	map = ini_map(size, 20); // free map ou leaks
	ret_val = compute_solve(pmap, t, map, size);
	if (ret_val != NULL)
		return (ret_val);
	ft_putstr("Fin de solve anormal\n");
	return (map);
}

/*
** ------Back Tracking-----
**
** Comment crée la map ?
**		Commencer par une map grande !
**		C'est un tab[][]
**		Remplit avec des point pour indiquer qu'il est vide
**		On lui défini un max avec tous ce qui est au dessu du max est un \0
**
** On veux placer un téri comment verifier que l'on peut?
**		(on vérifie que le tériminos sort pas de la map !
**		-additions des coordonées tab et tétri et verif avec max)
**		On vérifie Qu'il y a des point la ou on veux placer le tériminos
**
** Comment placer les tétriminos ?
**		On place t1[0][0 dans map[0][0]
**		On remplace les # par ABC
**		Puis on place ABC a la place des point
**
** Que faire si ça fonctionne pas ?
**		On avance la pièce et on vérifie jusqua que l'on puisse la placer
**
** Que faire si la pièce peux pas être placer ? Elle est en max max !
**	Si c'est pas la pièce 1 :
**		On retire (place pas) la pièce x puis on avence la pièce x - 1
**		-jusqua quel puisse être placer si elle ne peut pas on continue
**		-avec la pièce x - 1 encore
**	Si c'est la pièce 1 qui est en max max ?
**		Il y a pas de soluce pour cette taille on fait max++
**		On recomence tout map reprend des . on ce replace au début
**
** Comment afficher la map ?
**		on affiche que de tab max en x et y
**
** OPTI compter le nombre total de block root(nombre de carrer)
*/
