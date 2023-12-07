/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   legend.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 16:28:46 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/02/23 10:27:10 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include"fdf.h"

void	draw_legend(t_fdf *fdf)
{
	fdf->texture[1] = mlx_load_png("./legend.png");
	if (!fdf->texture[1])
	{
		free_fdf(fdf);
		exit(EXIT_FAILURE);
	}
	fdf->img[1] = mlx_texture_to_image(fdf->mlx, fdf->texture[1]);
	if (!fdf->img[1])
	{
		free_fdf(fdf);
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(fdf->mlx, fdf->img[1], fdf->mlx->width
			- fdf->texture[1]->width - 20, (fdf->mlx->height
				- fdf->texture[1]->height) / 2) < 0)
	{
		free_fdf(fdf);
		exit(EXIT_FAILURE);
	}
}
