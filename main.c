/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:15:30 by adidion           #+#    #+#             */
/*   Updated: 2022/01/06 17:50:31 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void ft_print(char **tab)
{
	int i = -1, j;
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
			write(1, &tab[i][j], 1);
		write(1, "\n", 1);
	}
}

int ft_free(char **tab, int r)
{
	int i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (r);
}

int main(int ac, char **av)
{
	if (ac != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	FILE *file;
	if ((file = fopen(av[1], "r")) == NULL)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	int width;
	int height;
	char bck_ch;
	if (3 != fscanf(file, "%d %d %c \n", &width, &height, &bck_ch) || width <= 0 || height <= 0 || width > 300 || height > 300)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	char **tab;
	int i = -1, j = -1;
	tab = calloc(height + 1, sizeof(char *));
	while (++i < height)
	{
		tab[i] = calloc(width + 1, sizeof(char));
		memset(tab[i], bck_ch, width);
	}

	char circle, c;
	float x, y, radius;
	int ret;
	while (-1 != (ret = fscanf(file, "%c %f %f %f %c \n", &circle, &x, &y, &radius, &c)))
	{
		if (ret != 5 || radius <= 0 || (circle != 'c' && circle != 'C'))
		{
			write(1, "Error: Operation file corrupted\n", 32);
			return (ft_free(tab, 1));
		}
		i = -1;
		while (tab[++i])
		{
			j = -1;
			while (tab[i][++j])
			{
				if (circle == 'c')
				{
					if (radius >= sqrt((j - x) * (j - x) + (i - y) * (i - y)) && radius - 1.0000 < sqrt((j - x) * (j - x) + (i - y) * (i - y)))
						tab[i][j] = c;;
				}
				if (circle == 'C')
				{
					if (radius >= sqrt((j - x) * (j - x) + (i - y) * (i - y)))
						tab[i][j] = c;
				}
			}
		}
	}
	ft_print(tab);
	return (ft_free(tab, 0));
}
