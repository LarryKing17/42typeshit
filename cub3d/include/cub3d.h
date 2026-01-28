/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:50:47 by zvalenti          #+#    #+#             */
/*   Updated: 2026/01/28 17:31:45 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define TILE_SIZE 64
# define WIDTH 1200
# define HEIGHT 800

# include "gnl.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
	int			value;
}				t_color;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
}				t_map;

typedef struct s_texture
{
	void		*img;
	char		*data;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;
}				t_texture;

typedef struct s_textures
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
}				t_textures;

typedef struct s_scene
{
	t_textures	tex;
	t_color		floor;
	t_color		ceil;
	t_map		map;
	double		px;
	double		py;
	double		dx;
	double		dy;
}				t_scene;

typedef struct s_tp
{
	double		step;
	double		start;
	double		tex_pos;
	int			tex_y;
	int			y;
	int			color;
}				t_tp;

typedef struct s_ray
{
	double	camera_x; // Position x dans le plan camera (-1 à 1)
	double	ray_dir_x; // Direction du rayon
	double	ray_dir_y;
	int		map_x; // Position dans la grille
	int		map_y;
	double	side_dist_x; // Distance jusqu'au prochain côté x
	double	side_dist_y; // Distance jusqu'au prochain côté y
	double	delta_dist_x; // Distance entre chaque côté x
	double	delta_dist_y; // Distance entre chaque côté y
	int		step_x; // Direction du pas (-1 ou 1)
	int		step_y;
	int		hit; // Mur touché ?
	int		side; // Côté touché (0=NS, 1=EW)
	double	perp_wall_dist; // Distance perpendiculaire au mur
	int		line_height; // Hauteur de la ligne à dessiner
	int		draw_start;
	int		draw_end;
	int		tex_x;
}				t_ray;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			sl;
	int			endian;

	double		px;
	double		py;
	double		dx;
	double		dy;

	double		plane_x;
	double		plane_y;
	double		dir_x;
	double		dir_y;
	int			i;
	int			j;
	double		ray_x;
	double		ray_y;
	double		angle;
	double		fov;
	double		step;

	t_map		map;

	t_scene		scene;
	t_ray		ray;
	t_texture	tex_no;
	t_texture	tex_so;
	t_texture	tex_we;
	t_texture	tex_ea;
}				t_data;

// PARSING
char			**read_file(char *path);
int				parse_cub(char *path, t_scene *s);
int				parse_color(char *line, t_color *c);
int				parse_map(char **lines, int start, t_scene *s);
void			find_player(t_scene *s);
int				is_map_line(char *l);
int				check_closed(t_scene *s);
int				check_file_extension(char *path);

int				parse_texture(char *line, t_scene *s);

// UTILS
int				is_empty_line(char *s);
void			free_split(char **tab);
int				ft_strtab_len(char **tab);
void			free_strtab(char **tab);
void			exit_error(t_scene *s, char **lines, char *msg);
void			free_scene(t_scene *s);
char			*skip_spaces(char *s);

void			ft_free_tab(char **tab);

char			**read_file(char *path);
int				parse_cub(char *path, t_scene *s);
int				parse_color(char *line, t_color *c);
int				parse_map(char **lines, int i, t_scene *s);
void			find_player(t_scene *s);
int				is_map_line(char *l);
int				check_closed(t_scene *s);

int				parse_texture(char *line, t_scene *s);

// UTILS
int				is_empty_line(char *s);
void			free_split(char **tab);
int				ft_strtab_len(char **tab);

void			ft_free_tab(char **tab);

void			put_pixel(t_data *d, int x, int y, int color);
void			draw(t_data *d);
int				key_press(int keycode, t_data *d);
int				close_window(void *param);
int				init_data(t_data *d);
int				rotate(double *y, double *x, double angle);
// RAYCASTING
void			draw_3d_view(t_data *d);
void			calculate_wall_height(t_ray *ray);
t_texture		*get_texture(t_data *d, t_ray *ray);
int				get_texture_color(t_texture *tex, int x, int y);
int				load_texture(t_data *d, t_texture *tex, char *path);
int				load_all_textures(t_data *d);
t_texture		*get_texture(t_data *d, t_ray *ray);
t_texture		*select_texture(t_data *d, t_ray *ray);
void			calculate_texture_x(t_data *d, t_ray *ray);
void			perform_dda(t_data *d, t_ray *ray);
void			cast_ray(t_data *d, t_ray *ray, int x);
void			key_handler(t_data *d, int col, int row);
void			rot_press(int keycode, t_data *d);
void			draw_textured_column(t_data *d, t_ray *ray, int x);
void			right_strafe(t_data *d, double move_speed);
void			left_strafe(t_data *d, double move_speed);

#endif