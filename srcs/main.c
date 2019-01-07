/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 10:49:54 by lubenard          #+#    #+#             */
/*   Updated: 2019/01/07 13:57:25 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	*read_file(char *arg)
{
	char	*str;
	int		fd;

	if (!(str = (char *)malloc(sizeof(char) * BUFF)))
		return (NULL);
	ft_bzero(str, BUFF);
	if ((fd = open(arg, O_RDONLY)) == -1)
	{
		ft_strdel(&str);
		return (NULL);
	}
	if (read(fd, str, BUFF) < 0)
	{
		ft_strdel(&str);
		return (NULL);
	}
	if (close(fd) == -1)
	{
		ft_strdel(&str);
		return (NULL);
	}
	return (str);
}

int		check_params(char argc)
{
	if (argc == 1 || argc > 2)
		return (-1);
	return (0);
}

int		all_error(int argc, char **argv, char *str, t_tetri **t)
{
	if (check_params(argc) == -1)
		return (usage());
	if (!(str = read_file(argv[1])))
		return (error());
	if (valid_file(str) == -1)
		return (error());
	if ((*t = parsing(str)) == NULL)
	{
		ft_strdel(&str);
		return (error());
	}
	return (0);
}

int		main(int argc, char **argv)
{
	char	*str;
	char	**map;
	t_tetri	*t;

	str = NULL;
	if (all_error(argc, argv, str, &t))
		return (-1);
	map = solve(t);
	while (t)
	{
		free_tetri(t);
		t = t->next;
	}
	display_map(map);
	return (0);
}
