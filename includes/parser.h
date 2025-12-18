/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpayot <anpayot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 10:00:00 by anpayot           #+#    #+#             */
/*   Updated: 2025/12/19 00:30:42 by anpayot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minirt.h"

//-------------Error messages-------------
# define ERR_USAGE		"Usage: ./miniRT <scene.rt>"
# define ERR_EXTENSION	"Error: File must have .rt extension"
# define ERR_OPEN		"Error: Cannot open file"

//-------------Element identifiers in .rt files-------------
// ID	Position		Direction		Param1		Param2		Color		(Type)

// A	0.2				255,255,255		-			-			-			(ambient)
// C	-50,0,20		0,0,1			70			-			-			(camera)
// L	-40,50,0		-				0.6			-			-			(light)
// sp	0,0,20			-				20			-			255,0,0		(sphere)
// pl	0,0,-10			0,1,0			-			-			0,0,225		(plane)
// cy	50,0,20.6		0,0,1			14.2		21.42		10,0,255	(cylinder)


//-------------Parsing functions-------------
int		parse_scene(char *filename);
int		check_file_extension(char *filename);
int		parse_error(char *msg);
char	*skip_whitespace(char *str);
int		is_empty_or_comment(char *line);

#endif
