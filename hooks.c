/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/27 10:55:36 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/03/02 10:29:47 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"fdf.h"

static void	update_image_rot(t_fdf *fdf, int x, int y, int z)
{
	fdf->rot_x += x;
	fdf->rot_y += y;
	fdf->rot_z += z;
	rot_map(fdf, fdf->rot_x, fdf->rot_y, fdf->rot_z);
	translate_map(fdf, fdf->trans_x, fdf->trans_y);
	delete_prev_img(fdf);
	create_new_image(fdf);
}

static void	rotation(t_fdf *fdf)
{
	int	x;
	int	y;
	int	z;

	x = 0;
	y = 0;
	z = 0;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		y += 2;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		y -= 2;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
		x += 2;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
		x -= 2;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_PAGE_UP))
		z += 2;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_PAGE_DOWN))
		z -= 2;
	if (x != 0 || y != 0 || z != 0)
		update_image_rot(fdf, x, y, z);
}

static void	update_translation(t_fdf *fdf, int x, int y)
{
	fdf->trans_x += x;
	fdf->trans_y += y;
	translate_map(fdf, x, y);
	delete_prev_img(fdf);
	create_new_image(fdf);
}

void	keyhook(void *param)
{
	t_fdf	*fdf;
	int		trans[2];

	trans[0] = 0;
	trans[1] = 0;
	fdf = (t_fdf *)param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		close_fdf(fdf);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_HOME))
	{
		delete_prev_img(fdf);
		set_start_view(fdf);
		create_new_image(fdf);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
		trans[1] -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		trans[1] += 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		trans[0] -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		trans[0] += 5;
	if (trans[0] != 0 || trans[1] != 0)
		update_translation(fdf, trans[0], trans[1]);
	rotation(fdf);
}

void	scrollhook(double xdelta, double ydelta, void *param)
{
	t_fdf	*fdf;
	int		zoom;

	fdf = (t_fdf *)param;
	xdelta = 0;
	zoom = 0;
	if (ydelta > 0)
		zoom += 2;
	else if (ydelta < 0 && fdf->zoom >= 2)
		zoom -= 2;
	if (zoom != 0)
	{
		fdf->zoom += zoom;
		scale_map(fdf, fdf->zoom);
		rot_map(fdf, fdf->rot_x, fdf->rot_y, fdf->rot_z);
		translate_map(fdf, fdf->trans_x, fdf->trans_y);
		delete_prev_img(fdf);
		create_new_image(fdf);
	}
}
