/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   image_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/27 10:55:36 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/03/02 10:57:53 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<math.h>
#include"fdf.h"

static void	draw_line(t_coord *start, t_coord *end, t_fdf *fdf)
{
	if (abs(end->sy - start->sy) < abs(end->sx - start->sx))
	{
		if (start->sx > end->sx)
			draw_line_low(end, start, fdf);
		else
			draw_line_low(start, end, fdf);
	}
	else
	{
		if (start->sy > end->sy)
			draw_line_high(end, start, fdf);
		else
			draw_line_high(start, end, fdf);
	}
}

static void	draw_x_lines(t_list *coords, t_fdf *fdf)
{
	t_coord	*start;
	t_coord	*end;

	while (coords->next)
	{
		start = (t_coord *)(coords->content);
		coords = coords->next;
		end = (t_coord *)(coords->content);
		draw_line(start, end, fdf);
		if (coords->next && ((t_coord *)(coords->next->content))->y != end->y)
			coords = coords->next;
	}
}

static void	draw_y_lines(t_list *coords, t_fdf *fdf)
{
	t_list	*temp;
	t_coord	*start;
	t_coord	*end;

	while (coords->next)
	{
		start = (t_coord *)(coords->content);
		coords = coords->next;
		temp = coords;
		while (temp->next && ((t_coord *)(temp->content))->x != start->x)
			temp = temp->next;
		end = (t_coord *)(temp->content);
		if (start->y == end->y)
			break ;
		draw_line(start, end, fdf);
	}
}

void	init_dimensions(t_list *coords, int extremes[], int *width, int *height)
{
	extremes[0] = ((t_coord *)(coords->content))->sx;
	extremes[1] = ((t_coord *)(coords->content))->sy;
	extremes[2] = ((t_coord *)(coords->content))->sx;
	extremes[3] = ((t_coord *)(coords->content))->sy;
	coords = coords->next;
	while (coords)
	{
		if (((t_coord *)(coords->content))->sx < extremes[0])
			extremes[0] = ((t_coord *)(coords->content))->sx;
		if (((t_coord *)(coords->content))->sx > extremes[2])
			extremes[2] = ((t_coord *)(coords->content))->sx;
		if (((t_coord *)(coords->content))->sy < extremes[1])
			extremes[1] = ((t_coord *)(coords->content))->sy;
		if (((t_coord *)(coords->content))->sy > extremes[3])
			extremes[3] = ((t_coord *)(coords->content))->sy;
		coords = coords->next;
	}
	*width = (extremes[2] - extremes[0]) + 1;
	*height = (extremes[3] - extremes[1]) + 1;
}

mlx_image_t	*generate_image(t_fdf *fdf)
{
	int	width;
	int	height;
	int	extremes[4];

	init_dimensions(fdf->coords, extremes, &width, &height);
	if (width <= 0 || height <= 0)
		return (NULL);
	fdf->ox = extremes[0];
	fdf->oy = extremes[1];
	fdf->texture[0] = (mlx_texture_t *)malloc(sizeof(mlx_texture_t));
	if (!fdf->texture[0])
		merror(fdf);
	fdf->texture[0]->height = height;
	fdf->texture[0]->width = width;
	fdf->texture[0]->bytes_per_pixel = 4;
	fdf->texture[0]->pixels = (uint8_t *)ft_calloc(width * height * 4,
			sizeof(uint8_t));
	if (!fdf->texture[0]->pixels)
		merror(fdf);
	draw_x_lines(fdf->coords, fdf);
	draw_y_lines(fdf->coords, fdf);
	return (mlx_texture_to_image(fdf->mlx, fdf->texture[0]));
}
