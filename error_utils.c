/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 14:51:10 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/02/28 14:54:55 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include"fdf.h"

void	del(void *node)
{
	if (node)
		free(node);
	node = NULL;
}

int	free_fdf(t_fdf *fdf)
{
	if (fdf->texture[0] && fdf->texture[0]->pixels)
	{
		free(fdf->texture[0]->pixels);
		free(fdf->texture[0]);
	}
	if (fdf->img[0])
		mlx_delete_image(fdf->mlx, fdf->img[0]);
	if (fdf->texture[1] && fdf->texture[1]->pixels)
	{
		free(fdf->texture[1]->pixels);
		free(fdf->texture[1]);
	}
	if (fdf->img[1])
		mlx_delete_image(fdf->mlx, fdf->img[1]);
	if (fdf->mlx)
		mlx_terminate(fdf->mlx);
	if (fdf->coords)
		ft_lstclear(&(fdf->coords), del);
	free(fdf);
	return (1);
}

void	merror(t_fdf *fdf)
{
	free_fdf(fdf);
	errno = ENOMEM;
	perror("Error");
	exit(EXIT_FAILURE);
}
