/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 22:53:25 by dguy-caz          #+#    #+#             */
/*   Updated: 2017/06/16 22:53:27 by dguy-caz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../minilibx_macos/mlx.h"
# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <stdio.h>

typedef struct			s_matrix4x4
{
	double				m[4][4];
}						t_matrix4x4;

typedef struct			s_matrix4x1
{
	double				m[4][1];
}						t_matrix4x1;

typedef struct			s_vector
{
	double				x;
	double				y;
	double				z;
}						t_vector;

typedef struct			s_color
{
	double				b;
	double				g;
	double				r;
}						t_color;

typedef struct			s_camera
{
	t_vector			origin;
	t_vector			lookat;
	t_vector			up;
	t_vector			x_vector;
	t_vector			y_vector;
	t_vector			z_vector;
	double				viewplane_width;
	double				viewplane_height;
	double				viewplane_distance;
	double				*matrix;
	t_vector			rayon;
}						t_camera;

typedef struct			s_plane
{
	t_vector			point;
	t_vector			normal;
	t_color				color;
	t_vector			node;
	t_vector			node_normal;
	double				brightness;
	int					id;
	struct s_plane		*next;
}						t_plane;

typedef struct			s_cone
{
	t_vector			vertex;
	t_vector			axis;
	double				tangent;
	double				length_max;
	t_color				color;
	t_vector			node;
	t_vector			node_normal;
	double				brightness;
	int					id;
	struct s_cone		*next;
}						t_cone;

typedef struct			s_cylinder
{
	t_vector			center;
	double				radius;
	t_vector			axis;
	double				length_max;
	t_color				color;
	t_vector			node;
	t_vector			node_normal;
	double				brightness;
	int					id;
	struct s_cylinder	*next;
}						t_cylinder;

typedef struct			s_sphere
{
	t_vector			center;
	double				radius;
	t_color				color;
	t_vector			node;
	t_vector			node_normal;
	double				brightness;
	int					id;
	struct s_sphere		*next;
}						t_sphere;

typedef struct			s_light
{
	t_vector			origin;
	t_vector			rayon;
	double				angle;
	t_color				color;
	int					id;
	struct s_light		*next;
}						t_light;

typedef struct			s_get_light
{
	int					light_blocked;
	t_vector			tmp_angle;
	t_color				color_to_add;
	t_color				tmp_color_to_add;
	t_light				*tmp_light;
	t_vector			view_rayon;
	t_vector			ray_normal;
}						t_get_light;

typedef struct			s_object
{
	t_sphere			*start_sphere;
	t_cylinder			*start_cylinder;
	t_plane				*start_plane;
	t_cone				*start_cone;
	t_light				*start_light;
}						t_object;

typedef struct			s_pixel
{
	int					x;
	int					y;
	int					tmpx;
	int					tmpy;
	t_vector			viewplane_point;
	t_vector			tmp_vp_pointx;
	t_vector			tmp_vp_pointy;
}						t_pixel;

typedef struct			s_poly
{
	double				tmp1;
	double				tmp2;
	double				tmp3;
	double				a;
	double				b;
	double				c;
	double				d;
	double				e;
	double				f;
	double				p;
	double				q;
	double				r;
	double				x;
	double				y;
	double				z;
	double				ad;
	double				bd;
	double				s;
	double				s1;
	double				s2;
	double				s3;
	double				s4;
	double				discriminant;
	double				length;
	t_vector			cone_rayon;
	t_vector			cylinder_rayon;
	t_vector			sphere_rayon;
	t_vector			plan_rayon;
	t_vector			tmp_node_normal;
	double				radian_x;
	double				radian_y;
	double				radian_z;
}						t_poly;

typedef struct			s_mlx
{
	void				*win_ptr;
	void				*mlx_ptr;
	void				*img_ptr;
	unsigned char		*data;
	int					l_size;
	int					bpp;
	int					endian;
}						t_mlx;

typedef struct			s_datas
{
	t_camera			camera;
	t_vector			viewplane_point_up_left;
	t_vector			current_origin;
	t_vector			current_rayon;
	t_color				current_color;
	t_vector			current_node;
	t_vector			current_node_normal;
	t_vector			current_node_normal_fuck;
	t_color				color_finale;
	double				brightness;
	int					window_width;
	int					window_height;
	int					id_sphere;
	int					id_cylinder;
	int					id_cone;
	int					id_plane;
	double				distance_light_object;
	double				distance;
	double				solution;
	t_matrix4x4			rotation_matrix;
	t_matrix4x4			translation_matrix;
	t_matrix4x4			matrix_camera_system;
	t_matrix4x1			matrix_camera_origin;
	double				move_x;
	double				move_y;
	double				move_z;
	double				rotate_x;
	double				rotate_y;
	double				rotate_z;
	double				x1;
	double				y1;
	double				z1;
	int					aa_flag;
	int					pixelize;
	t_object			*objects;
	t_mlx				mlx;
}						t_datas;

typedef struct			s_anti_a
{
	int					x;
	int					y;
	int					sample;
	double				x1;
	double				y1;
	t_color				aaclr;
	t_vector			viewplane_point;
	t_vector			tmp_vp_pointx;
	t_vector			tmp_vp_pointy;
}						t_anti_a;

int						tab_count(char **tab);
void					ft_kill(char *str);
void					ft_help(void);
void					ft_print_err(int argc);
void					display_window(t_datas *d, t_object *object);
int						plane_intersection(t_datas *d, t_plane *plane);
int						cone_intersection(t_datas *d, t_cone *cone);
int						sphere_intersection(t_datas *d, t_sphere *sphere);
int						cylinder_intersection(t_datas *d, t_cylinder *cylinder);
int						polygone_solutions(t_datas *d, t_poly *p);
void					ray_tracer(t_datas *d);
int						proper_exit(t_datas *d);
void					reset_mov_rotate(t_datas *d);
void					inputs(int keycode, t_datas *d);
int						key_functions(int keycode, t_datas *d);
t_vector				set_vector(double x, double y, double z);
double					magnitude(t_vector *a);
t_vector				normalize(t_vector *a);
double					dot_product(t_vector *a, t_vector *b);
t_vector				v_v_add(t_vector *a, t_vector *b);
t_vector				v_v_subs(t_vector *a, t_vector *b);
t_vector				v_v_mult(t_vector *a, t_vector *b);
t_vector				v_double_add(t_vector *a, double b);
t_vector				v_double_subs(t_vector *a, double b);
t_vector				v_double_mult(t_vector *a, double b);
t_vector				v_double_div(t_vector *a, double b);
t_color					set_color(double b, double g, double r);
void					print_color(t_color *color, t_datas *d, int x, int y);
t_color					normalize_color(t_color *a);
double					magnitude_color(t_color *a);
t_color					c_c_mult(t_color *a, t_color *b);
t_color					c_c_add(t_color *a, t_color *b);
t_color					c_double_mult(t_color *a, double b);
void					get_color(t_datas *d, t_object *object);
double					get_specular(t_light *light, t_vector *view,
						t_vector *node);
void					light_intensity(t_get_light *v, t_datas *d);
void					get_intersection(t_datas *d, t_object *object);
int						check_if_light_is_blocked(t_datas *d,
						int *light_blocked, t_object *object);
void					blocked_by_a_plane(t_datas *d, int *light_blocked,
						t_object *object);
void					blocked_by_a_cylinder(t_datas *d, int *light_blocked,
						t_object *object);
void					blocked_by_a_sphere(t_datas *d, int *light_blocked,
						t_object *object);
t_sphere				*add_new_sphere(t_object *object, t_sphere *new_sphere);
t_cone					*add_new_cone(t_object *object, t_cone *new_cone);
t_cylinder				*add_new_cylinder(t_object *object,
						t_cylinder *new_cylinder);
t_plane					*add_new_plane(t_object *object, t_plane *new_plane);
t_light					*add_new_light(t_object *object, t_light *new_light);
void					create_environment(t_datas *d, char *line);
void					create_sphere(t_object *object, char *line);
void					create_cone(t_object *object, char *line);
void					create_cylinder(t_object *object, char *line);
void					create_plane(t_object *object, char *line);
void					create_light(t_object *object, char *line);
int						parsing(t_datas *d, t_object *object, char *src_file);
void					init_camera(t_datas *d);
void					camera_transformation(t_datas *d);
t_color					c_double_add(t_color *a, double b);
double					degree_to_radian(double degree_angle);
t_matrix4x4				m4x4_m4x4_mult(t_matrix4x4 *camera_matrix,
						t_matrix4x4 *rotation);
void					matrix_4x4_to_vectors(t_vector *a, t_vector *b,
						t_vector *c, t_matrix4x4 *matrix);
t_matrix4x4				matrix_camera_system(t_vector *a, t_vector *b,
						t_vector *c);
void					rotation_matrix(t_matrix4x4 *rotation, t_poly *p);
t_matrix4x4				rotation(double degree_x, double degree_y,
						double degree_z);
t_matrix4x1				m4x4_m4x1_mult_reduced(t_matrix4x4 *translation,
						t_matrix4x1 *matrix);
void					matrix_4x1_to_vectors(t_vector *a, t_matrix4x1 *matrix);
t_matrix4x1				matrix_camera_origin(t_vector *a);
void					update_system_translation(t_datas *d, t_matrix4x4 *rot);
t_matrix4x4				translation(t_datas *d, t_matrix4x4 *rot);
void					viewplane_transformation(t_datas *d);
t_pixel					pixel_vp_init(t_pixel *pxl, t_datas *d);
void					pixel_tracer(t_datas *d, int sample);
void					aa_tracer(t_datas *d, int sample);
t_anti_a				antialias_loop_init(t_anti_a *anti, t_datas *d,
						int sample);
void					anti_aliasing_clr_merge(t_color *anti, t_color *clr);
t_color					c_double_div(t_color *a, double b);
void					init_transformations(t_datas *d);
void					register_cylinder(t_datas *d, t_cylinder *tmp_cylinder,
						int *printable);
void					register_cone(t_datas *d, t_cone *tmp_cone,
						int *printable);
void					register_sphere(t_datas *d, t_sphere *tmp_sphere,
						int *printable);
void					register_plane(t_datas *d, t_plane *tmp_plane,
						int *printable);

#endif
