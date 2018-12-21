/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoussu <jmoussu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 10:22:26 by lubenard          #+#    #+#             */
/*   Updated: 2018/12/21 14:46:16 by jmoussu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "../libft/libft.h"
# include <fcntl.h>

# include <stdio.h>

# define BUFF 1024

typedef struct	s_coord
{
	int x;
	int y;
}				t_coord;

typedef struct	s_tetrimino
{
	char				**tetrimino;
	char				letter;
	t_coord				c[4];
	t_coord				pos;
	struct s_tetrimino	*prev;
	struct s_tetrimino	*next;
}				t_tetri;

char			**placeone(t_tetri *t, char **map, int size);
/*
**test d'algo a enlever dans version non final
*/
int				remove_p(t_tetri *t, char **map);
int				place(t_tetri *t, char **map, t_coord pmap);
int				placebrut(t_tetri *t, char **map, t_coord pmap);
int				canplace(t_tetri *t, char **map, t_coord pmap);
int				usage(void);
int				error(void);
t_tetri			*make_coord_p(t_tetri *t);
t_tetri			*parsing(char *str);
int				valid_file(char *str);
char			**ini_map(int size, int max);
void			display_map(char **map);
int				verif_tetrimino(char **str);
int				optimize_tetri(char **str);
void			print_all_list(t_tetri *t);
void			print_list(t_tetri *t);

#endif
