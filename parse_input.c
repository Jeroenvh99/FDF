/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/30 10:40:20 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/03/02 10:49:46 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include<errno.h>
#include"fdf.h"

static int	split_length(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		++i;
	return (i);
}

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		++i;
	}
	free(split);
}

static void	free_input(char **coord_info, char *line, t_list **coords)
{
	if (coord_info)
		free_split(coord_info);
	if (line)
		free(line);
	if (coords)
		ft_lstclear(coords, del);
}

static int	process_coords(int y, char **coord_info, t_list **coords)
{
	t_coord	*coord;
	int		x;
	int		linelength;
	int		overflow;

	x = 0;
	linelength = split_length(coord_info);
	while (coord_info[x] && coord_info[x][0] != '\n')
	{
		coord = (t_coord *)malloc(sizeof(t_coord));
		if (!coord)
			return (0);
		coord->x = x;
		coord->y = y;
		overflow = atoi_overflow(coord_info[x], &coord->z);
		if (!overflow)
			return (0);
		ft_lstadd_back(coords, ft_lstnew(coord));
		++x;
	}
	return (1);
}

int	parse_input(int fd, t_list **coords)
{
	int		y;
	char	*line;
	char	**coord_info;

	line = get_next_line(fd);
	y = 0;
	while (line)
	{
		coord_info = ft_split(line, ' ');
		if (!coord_info)
		{
			free_input(NULL, line, coords);
			return (0);
		}
		if (!process_coords(y, coord_info, coords))
		{
			free_input(coord_info, line, coords);
			return (0);
		}
		free_input(coord_info, line, NULL);
		line = get_next_line(fd);
		++y;
	}
	return (1);
}
