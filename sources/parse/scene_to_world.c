/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_to_world.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 by anpayot           #+#    #+#             */
/*   Updated: 2026/01/13 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
	Convert parsed scene to world for rendering
*/
t_world	scene_to_world(t_scene *scene, unsigned int window_dimensions[2])
{
	t_world			world;
	t_lightening	lightening;

	world.camera = create_camera(window_dimensions,
			scene->cam_spec.position,
			scene->cam_spec.orientation,
			(unsigned int)scene->cam_spec.fov);
	lightening.lights = scene->lights;
	lightening.lights_count = scene->light_count;
	lightening.ambient = scene->ambient.color;
	world.lightening = lightening;
	world.objects = scene->objects;
	return (world);
}
