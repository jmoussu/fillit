/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 13:26:51 by lubenard          #+#    #+#             */
/*   Updated: 2019/01/12 13:46:33 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		usage(void)
{
	ft_putstr("usage: ./fillit source_file\n");
	return (-1);
}

int		error(void)
{
	ft_putstr("error\n");
	return (-1);
}

char	putletter(void)
{
	static char letter = 'A';

	return (letter++);
}

int		compute_parsing(char *str, int i)
{
	while (str[i] != '\n' && str[i])
		i++;
	return (i);
}
