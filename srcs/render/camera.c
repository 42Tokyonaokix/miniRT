/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:02:06 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/16 00:06:45 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "render.h"

int	camera_build_basis(t_camera	*camera)
{
	t_vec3	world_up;
	
	ft_bzero(&world_up, sizeof(t_vec3));
	world_up.z = 1;
	camera->forward = vec3_normalize(camera->forward);
	if (vec3_sq(vec3_sub(camera->forward, world_up)) < EPS * EPS)
	{
		world_up.z = 0;
		world_up.y = 1;
	}
	camera->up = vec3_normalize(vec3_ver(world_up, camera->forward));
	camera->right = vec3_normalize(vec3_cross(camera->forward, camera->up));
	return (OK);
}

t_ray	camera_pixel_ray(t_camera camera, int x, int y)
{
	t_vec3	cor_x;
	t_vec3	cor_y;
	double	ndc_x;
	double	ndc_y;
	t_ray	ray;

	ndc_x = ((2 * (x + 0.5) / WIN_W) - 1) * camera_half_w(camera);
	ndc_y = (1 - (2 * (y + 0.5) / WIN_H)) * camera_half_h(camera);
	cor_x = vec3_scale(camera.right, ndc_x);
	cor_y = vec3_scale(camera.up, ndc_y);
	ray.dir = vec3_add(vec3_add(cor_x, cor_y), camera.forward);
	ray.origin = camera.position;
	return (ray);
}

// int	main(int argc, char **argv)
// {
// 	t_camera	camera;
	
// 	ft_bzero(&camera, sizeof(t_camera));
// 	if (argc != 4)
// 		return (ft_putendl_fd("ERROR!", 2), EXIT_FAILURE);
// 	camera.forward.x = ft_atof(argv[1]);
// 	camera.forward.y = ft_atof(argv[2]);
// 	camera.forward.z = ft_atof(argv[3]);
// 	camera.forward = vec3_normalize(camera.forward);
// 	vec3_print(camera.forward, "camera.forward");
// 	camera.position.x = 0;
// 	camera.position.y = 0;
// 	camera.position.z = 0;
// 	camera = camera_build_basis(camera);
// 	vec3_print(camera.up, "camera.up");
// 	vec3_print(camera.right, "camera.right");
// 	return (EXIT_SUCCESS);
// }
