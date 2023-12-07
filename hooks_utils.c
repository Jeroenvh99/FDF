/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/23 12:01:29 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/02/28 14:47:38 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include"fdf.h"

void	close_fdf(t_fdf *fdf)
{
	mlx_close_window(fdf->mlx);
	free_fdf(fdf);
	exit(EXIT_SUCCESS);
}

void	delete_prev_img(t_fdf *fdf)
{
	if (!fdf->img[0])
		return ;
	mlx_delete_image(fdf->mlx, fdf->img[0]);
	fdf->img[0] = NULL;
	free(fdf->texture[0]->pixels);
	fdf->texture[0]->pixels = NULL;
	free(fdf->texture[0]);
	fdf->texture[0] = NULL;
}

void	create_new_image(t_fdf *fdf)
{
	fdf->img[0] = generate_image(fdf);
	if (!fdf->img[0])
		return ;
	mlx_image_to_window(fdf->mlx, fdf->img[0], fdf->ox, fdf->oy);
}
