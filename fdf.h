/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/30 10:25:31 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/03/02 10:50:46 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include"./libft/libft.h"
# include"./MLX42/include/MLX42/MLX42.h"

typedef struct s_coord{
	int		x;
	int		y;
	double	z;
	int		sx;
	int		sy;
}	t_coord;

typedef struct s_fdf{
	mlx_t			*mlx;
	mlx_image_t		*img[2];
	mlx_texture_t	*texture[2];
	t_list			*coords;
	double			trans_x;
	double			trans_y;
	double			rot_x;
	double			rot_y;
	double			rot_z;
	double			zoom;
	int				ox;
	int				oy;
}	t_fdf;

void		del(void *node);
int			parse_input(int fd, t_list **coords);
int			atoi_overflow(char *str, double *num);
int			get_input(char *file, t_fdf *fdf);
void		hooks(t_fdf *fdf);
void		close_fdf(t_fdf *fdf);
void		delete_prev_img(t_fdf *fdf);
void		create_new_image(t_fdf *fdf);
void		start_fdf(t_fdf *fdf);
void		draw_legend(t_fdf *fdf);
void		set_start_view(t_fdf *fdf);
void		scale_map(t_fdf *fdf, int zoom);
void		rot_map(t_fdf *fdf, int x, int y, int z);
void		translate_map(t_fdf *fdf, int trans_x, int trans_y);
mlx_image_t	*generate_image(t_fdf *fdf);
void		draw_line_low(t_coord *start, t_coord *end, t_fdf *fdf);
void		draw_line_high(t_coord *start, t_coord *end, t_fdf *fdf);
void		keyhook(void *param);
void		scrollhook(double xdelta, double ydelta, void *param);
int			free_fdf(t_fdf *fdf);
void		merror(t_fdf *fdf);

#endif