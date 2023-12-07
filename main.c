/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/27 10:55:36 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/03/02 10:59:32 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdlib.h>
#include"fdf.h"

// static void checkleaks()
// {
// 	system("leaks fdf");
// }

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc == 1 || argc > 2)
	{
		if (argc == 1)
			write(2, "no input file specified\n", 24);
		else
			write(2, "too many arguments\n", 19);
		return (1);
	}
	fdf = (t_fdf *)ft_calloc(1, sizeof(t_fdf));
	if (!fdf)
		return (1);
	get_input(argv[1], fdf);
	fdf->mlx = mlx_init(1000, 800, "FDF", true);
	if (!fdf->mlx)
		return (free_fdf(fdf));
	start_fdf(fdf);
	mlx_image_to_window(fdf->mlx, fdf->img[0], fdf->ox, fdf->oy);
	draw_legend(fdf);
	hooks(fdf);
	free_fdf(fdf);
	return (0);
}
