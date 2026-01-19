/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 17:27:54 by idridi            #+#    #+#             */
/*   Updated: 2026/01/16 17:09:49 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void free_textures(t_data *d)
{
    if (d->tex_no.img)
        mlx_destroy_image(d->mlx, d->tex_no.img);
    if (d->tex_so.img)
        mlx_destroy_image(d->mlx, d->tex_so.img);
    if (d->tex_we.img)
        mlx_destroy_image(d->mlx, d->tex_we.img);
    if (d->tex_ea.img)
        mlx_destroy_image(d->mlx, d->tex_ea.img);
}

void put_pixel(t_data *d, int x, int y, int color)
{
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    if (!d || !d->addr)
        return;
    *(int *)(d->addr + y * d->sl + x * (d->bpp / 8)) = color;
}

void draw_textured_column(t_data *d, t_ray *ray, int x)
{
    t_texture *tex;
    double step;
    double tex_pos;
    int tex_y;
    int y;
    int color;
    
    // Sélectionne la texture appropriée
    tex = select_texture(d, ray);
    
    // Calcul du pas vertical dans la texture
    step = (double)tex->height / (double)ray->line_height;
    
    // Position de départ dans la texture
    tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
    
    // Dessine le plafond
    y = 0;
    while (y < ray->draw_start)
    {
        put_pixel(d, x, y, d->scene.ceil.value);
        y++;
    }
    
    // Dessine le mur texturé
    y = ray->draw_start;
    while (y <= ray->draw_end)
    {
        // Calcule la coordonnée Y dans la texture
        tex_y = (int)tex_pos;
        
        // Sécurité (clamp)
        if (tex_y < 0)
            tex_y = 0;
        if (tex_y >= tex->height)
            tex_y = tex->height - 1;
        
        // Avance dans la texture
        tex_pos += step;
        
        // Récupère la couleur du pixel de texture
        color = get_texture_color(tex, ray->tex_x, tex_y);
        
        // Dessine le pixel

        put_pixel(d, x, y, color);
        
        y++;
    }
    
    // Dessine le sol
    while (y < HEIGHT)
    {
        put_pixel(d, x, y, d->scene.floor.value);
        y++;
    }
}

void calculate_texture_x(t_data *d, t_ray *ray)
{
    double wall_x;
    
    // Calcule le point d'impact exact
    if (ray->side == 0)
        wall_x = d->py + ray->perp_wall_dist * ray->ray_dir_y;
    else
        wall_x = d->px + ray->perp_wall_dist * ray->ray_dir_x;
    
    // Partie fractionnaire seulement
    wall_x -= floor(wall_x);
    
    // Convertit en coordonnée de texture
    ray->tex_x = (int)(wall_x * 64.0);  // Suppose texture 64x64
    
    // Inverse si nécessaire pour éviter l'effet miroir
    if ((ray->side == 0 && ray->ray_dir_x > 0) ||
        (ray->side == 1 && ray->ray_dir_y < 0))
        ray->tex_x = 63 - ray->tex_x;  // 64 - 1 - tex_x
}

t_texture *select_texture(t_data *d, t_ray *ray)
{
    if (ray->side == 0)  // Mur vertical (NS)
    {
        if (ray->step_x > 0)
            return &d->tex_ea;  // Face Est (on vient de l'ouest)
        else
            return &d->tex_we;  // Face Ouest (on vient de l'est)
    }
    else  // Mur horizontal (EW)
    {
        if (ray->step_y > 0)
            return &d->tex_so;  // Face Sud (on vient du nord)
        else
            return &d->tex_no;  // Face Nord (on vient du sud)
    }
}

int get_texture_color(t_texture *tex, int x, int y)
{
    if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
        return 0;
    
    return *(int *)(tex->data + y * tex->size_line + x * (tex->bpp / 8));
}

int load_texture(t_data *d, t_texture *tex, char *path)
{
    tex->img = mlx_xpm_file_to_image(d->mlx, path, &tex->width, &tex->height);
    if (!tex->img)
    {
        printf("Error\nFailed to load texture: %s\n", path);
        return 0;
    }
    tex->data = mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_line, &tex->endian);
    return 1;
}

int load_all_textures(t_data *d)
{
    if (!load_texture(d, &d->tex_no, d->scene.tex.no))
        return 0;
    if (!load_texture(d, &d->tex_so, d->scene.tex.so))
        return 0;
    if (!load_texture(d, &d->tex_we, d->scene.tex.we))
        return 0;
    if (!load_texture(d, &d->tex_ea, d->scene.tex.ea))
        return 0;
    return 1;
}

int rotate(double *dx, double *dy, double angle)
{
    double old_dx = *dx;
    *dx = old_dx * cos(angle) - (*dy) * sin(angle);
    *dy = old_dx * sin(angle) + (*dy) * cos(angle);
    return 0;
}

void calculate_wall_height(t_ray *ray)
{
    // Hauteur de la ligne à dessiner
    ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
    
    // Calcule début et fin de la ligne
    ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    
    ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
    if (ray->draw_end >= HEIGHT)
        ray->draw_end = HEIGHT - 1;
}

void perform_dda(t_data *d, t_ray *ray)
{
    ray->hit = 0;
    
    // Avance dans la grille jusqu'à toucher un mur
    while (ray->hit == 0)
    {
        // Avance dans la direction la plus proche
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0; // Mur vertical (NS)
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1; // Mur horizontal (EW)
        }
        
        // Vérifie si on a touché un mur
        if (ray->map_x < 0 || ray->map_y < 0 
            || ray->map_y >= d->scene.map.height
            || ray->map_x >= (int)ft_strlen(d->scene.map.grid[ray->map_y]))
            ray->hit = 1; // Hors limites = mur
        else if (d->scene.map.grid[ray->map_y][ray->map_x] == '1')
            ray->hit = 1; // Mur trouvé
    }
    
    // Calcule la distance perpendiculaire (évite l'effet fish-eye)
    if (ray->side == 0)
        ray->perp_wall_dist = (ray->map_x - d->px / TILE_SIZE + (1 - ray->step_x) / 2) / ray->ray_dir_x;
    else
        ray->perp_wall_dist = (ray->map_y - d->py / TILE_SIZE + (1 - ray->step_y) / 2) / ray->ray_dir_y;
}

void cast_ray(t_data *d, t_ray *ray, int x)
{
    // 1. Position dans le plan caméra (-1 à gauche, +1 à droite)
    ray->camera_x = 2 * x / (double)WIDTH - 1;
    
    // 2. Direction du rayon
    ray->ray_dir_x = d->dx + d->plane_x * ray->camera_x;
    ray->ray_dir_y = d->dy + d->plane_y * ray->camera_x;
    
    // 3. Position de départ dans la grille
    ray->map_x = (int)(d->px / TILE_SIZE);
    ray->map_y = (int)(d->py / TILE_SIZE);
    
    // 4. Distance entre chaque intersection avec les lignes de la grille
    ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
    ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
    
    // 5. Direction du pas et distance initiale
    if (ray->ray_dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = ((d->px / TILE_SIZE) - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - (d->px / TILE_SIZE)) * ray->delta_dist_x;
    }
    
    if (ray->ray_dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = ((d->py / TILE_SIZE) - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - (d->py / TILE_SIZE)) * ray->delta_dist_y;
    }
}

void draw_3d_view(t_data *d)
{
    t_ray ray;
    int x;
    
    x = 0;
    while (x < WIDTH)
    {
        // Lance le rayon
        cast_ray(d, &ray, x);
        perform_dda(d, &ray);
        calculate_wall_height(&ray);
        
        // ✨ NOUVELLE FONCTION : calcule la colonne de texture
        calculate_texture_x(d, &ray);
        
        // ✨ NOUVELLE FONCTION : dessine avec textures
        draw_textured_column(d, &ray, x);
        
        x++;
    }
}

void draw(t_data *d)
{
    // Dessine la vue 3D
    draw_3d_view(d);
    
    // Affiche l'image
    mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
}

int key_press(int keycode, t_data *d)
{
    double move_speed = 0.1;  // En unités de grille, pas en pixels
    double rot_speed = 0.05;
    
    if (keycode == 65307) // ESC
        exit(0);

    if (keycode == 119 || keycode == 115)  // w ou s
    {
        double new_x = d->scene.px + d->scene.px * move_speed;
        double new_y = d->scene.py + d->scene.py * move_speed;

        // ✅ VÉRIFIER LES LIMITES AVANT D'ACCÉDER À LA GRILLE
        int map_x = (int)(new_x / TILE_SIZE);
        int map_y = (int)(new_y / TILE_SIZE);
        
        // Vérifier que les indices sont dans les limites
        if (map_x >= 0 && map_x < d->scene.map.width &&
            map_y >= 0 && map_y < d->scene.map.height &&
            d->scene.map.grid[map_y][map_x] != '1')
        {
            d->scene.px = new_x;
            d->scene.py = new_y;
        }
    }
    if (keycode == 65361) // Flèche gauche
    {
        rotate(&d->dy, &d->dx, rot_speed);
        rotate(&d->plane_y, &d->plane_x, rot_speed);
    }
    
    if (keycode == 65363) // Flèche droite
    {
        rotate(&d->dy, &d->dx, -rot_speed);
        rotate(&d->plane_y, &d->plane_x, -rot_speed);
    }
    
    draw(d);
    return 0;
}

int close_window()
{
    exit(0);
}

int init_data(t_data *d/*, t_scene *s*/)
{
    d->mlx = mlx_init();
    d->win = mlx_new_window(d->mlx, WIDTH, HEIGHT, "MLX Player");

    d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
    d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->sl, &d->endian);

    draw(d);

    mlx_hook(d->win, 2, 1L << 0, key_press, d);
    mlx_hook(d->win, 17, 0, close_window, NULL);

    mlx_loop(d->mlx);
    return 0;
}