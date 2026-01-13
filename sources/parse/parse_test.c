/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auto <auto@localhost>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 16:50:00 by auto              #+#    #+#             */
/*   Updated: 2026/01/13 16:50:00 by auto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "parser.h"

int	main(int argc, char **argv)
{
    t_scene scene;
    const char *filename;
    int status;

    (void)argc;
    if (argv[1] && argv[1][0] != '\0')
        filename = argv[1];
    else
        filename = "scenes/basic_sphere.rt";
    memset(&scene, 0, sizeof(scene));
    status = parse_scene(&scene, filename);
    if (status == SUCCESS)
        printf("parse: SUCCESS\n");
    else
        printf("parse: FAILURE\n");
    return (status == SUCCESS ? 0 : 1);
}
