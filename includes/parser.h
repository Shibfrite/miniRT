/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 10:00:00 by anpayot           #+#    #+#             */
/*   Updated: 2026/01/13 09:57:40 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minirt.h"
# include "get_next_line.h"

//-------------Error messages-------------
# define ERR_USAGE		"Usage: ./miniRT <scene.rt>"
# define ERR_EXTENSION	"File must have .rt extension"
# define ERR_OPEN		"Cannot open file"
# define ERR_READ		"Failed to read file"
# define ERR_MEMORY		"Memory allocation failed"
# define ERR_UNKNOWN_ID	"Unknown identifier in .rt file"
# define ERR_DUPLICATE_CAMERA "Camera already defined"
# define ERR_DUPLICATE_AMBIENT "Ambient light already defined"
# define ERR_MISSING_CAMERA "Missing camera (C)"
# define ERR_MISSING_AMBIENT "Missing ambient light (A)"
# define ERR_MISSING_LIGHT "Missing light (L)"
# define ERR_MISSING_OBJECT "Scene must contain at least one object"
# define ERR_TOO_MANY_OBJECTS "Too many objects in scene"
# define ERR_TOO_MANY_LIGHTS "Too many lights in scene"
# define ERR_INVALID_TOKEN_COUNT "Invalid number of tokens"
# define ERR_INVALID_VALUE "Invalid value in line"

//-------------Element identifiers in .rt files-------------
// ID	Position		Direction		Param1		Param2		Color		(Type)

// A	0.2				255,255,255		-			-			-			(ambient)
// C	-50,0,20		0,0,1			70			-			-			(camera)
// L	-40,50,0		-				0.6			-			-			(light)
// sp	0,0,20			-				20			-			255,0,0		(sphere)
// pl	0,0,-10			0,1,0			-			-			0,0,225		(plane)
// cy	50,0,20.6		0,0,1			14.2		21.42		10,0,255	(cylinder)


//-------------Parsing functions-------------
int			parse_scene(t_scene *scene, const char *filename);
int			check_file_extension(const char *filename);
int			parse_error(const char *msg);
const char	*skip_spaces(const char *str);
int			is_empty_or_comment(const char *line);
char		**split_whitespace(const char *line);
void		free_tokens(char **tokens);
t_world		scene_to_world(t_scene *scene, unsigned int window_dimensions[2]);

int			parse_ambient(t_scene *scene, char **tokens);
int			parse_camera(t_scene *scene, char **tokens);
int			parse_light(t_scene *scene, char **tokens);
int			parse_sphere(t_scene *scene, char **tokens);
int			parse_plane(t_scene *scene, char **tokens);
int			parse_cylinder(t_scene *scene, char **tokens);

//-------------Parsing helpers-------------
int		parse_double_token(const char *s, double *out);
int		parse_int_range(const char *s, int min, int max, int *out);
int		parse_vec3(const char *s, t_vec3 *out);
int		parse_normalized_vec3(const char *s, t_vec3 *out);
int		parse_color(const char *s, t_color3 *out);

#endif
