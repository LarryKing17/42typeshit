/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvalenti <zvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:45:16 by zvalenti          #+#    #+#             */
/*   Updated: 2025/12/11 15:45:19 by zvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

int	main(int argc, char **argv)
{
    t_config	cfg;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <map.cub>\n", argv[0]);
        return (1);
    }
    if (parse_file(argv[1], &cfg) != 0)
    {
        fprintf(stderr, "Parsing failed.\n");
        return (1);
    }
    printf("Parsing OK!\n");
    free_config(&cfg);
    return (0);
}