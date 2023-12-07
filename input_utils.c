/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/30 10:40:20 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/02/28 13:25:31 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<math.h>
#include"fdf.h"

void	scale_map(t_fdf *fdf, int zoom)
{
	t_list	*coords;
	t_coord	*coord;

	coords = fdf->coords;
	while (coords)
	{
		coord = (t_coord *)(coords->content);
		coord->sx = coord->x * zoom;
		coord->sy = coord->y * zoom;
		coords = coords->next;
	}
}

static double	deg_to_rad(int degrees)
{
	if (degrees >= 360)
		degrees -= ((degrees / 360) * 360);
	return (degrees * (M_PI / 180.0));
}

static void	rotate_coord(t_coord *coord, double angles[], int zoom)
{
	double	cosy;
	double	cosz;
	double	sinx;
	double	siny;
	double	sinz;

	cosz = cos(angles[2]);
	cosy = cos(angles[1]);
	sinx = sin(angles[0]);
	siny = sin(angles[1]);
	sinz = sin(angles[2]);
	coord->sx = (cosz * cos(angles[0]) * coord->x * zoom) + (((cosz * sinx
					* siny) - (sinz * cosy)) * coord->y * zoom) + (((cosz
					* sinx * cosy) + (sinz * siny)) * coord->z * zoom);
	coord->sy = (sinz * cos(angles[0]) * coord->x * zoom) + (((sinz * sinx
					* siny) + (cosz * cosy)) * coord->y * zoom) + (((sinz
					* sinx * cosy) - (cosz * siny)) * coord->z * zoom);
}

void	rot_map(t_fdf *fdf, int x, int y, int z)
{
	t_list	*coords;
	t_coord	*coord;
	double	angles[3];

	angles[0] = deg_to_rad(x);
	angles[1] = deg_to_rad(y);
	angles[2] = deg_to_rad(z);
	coords = fdf->coords;
	while (coords)
	{
		coord = (t_coord *)(coords->content);
		rotate_coord(coord, angles, fdf->zoom);
		coords = coords->next;
	}
}

void	translate_map(t_fdf *fdf, int trans_x, int trans_y)
{
	t_list	*coords;
	t_coord	*coord;

	coords = fdf->coords;
	while (coords)
	{
		coord = (t_coord *)(coords->content);
		coord->sx += trans_x;
		coord->sy += trans_y;
		coords = coords->next;
	}
}
