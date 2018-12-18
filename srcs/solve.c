/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoussu <jmoussu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 10:59:54 by lubenard          #+#    #+#             */
/*   Updated: 2018/12/18 15:11:20 by jmoussu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Mission 0 crée la map et l'afficher avec des point !
**
** Mission 1 Placer 1 tériminos dans la map et l'afficher a la bonne taille
**		besoin de recupere les coordone des 4 block
*/

char **placeone(char **blockt, char **map, int size)
{
	int		i;
	int		j;
	char	**newmap;

	newmap = map;
	j = 0;
	while(j != 4)
	{
		i = 0;
		while (i != 4)
		{
			if (blockt[j][i] == '#')
			{
				if (newmap[j][i] == '.')
				{
					newmap[j][i] = 'A';
				}
				else
				{
					size++;
					ft_putstr("recusivité\n");
					map = ini_map(size, 90);
					return(placeone(blockt, map, size));
				}
			}
			i++;
		}
		j++;
	}
	return (newmap);
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
