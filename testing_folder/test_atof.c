/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_atof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:10:52 by igchurru          #+#    #+#             */
/*   Updated: 2025/04/08 11:28:54 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

float	ft_atof(char *n)
{
	int		i;
	int		j;
	float	nb;
	int		m;

	i = 0;
	nb = 0;
	m = 1;
	j = 1;
	if (n[i] == '-')
	{
		m = -m;
		i++;
	}
	while (n[i])
	{
		if (j > 1 && n[i - 1] != '.')
			j *= 10;
		if (n[i] == '.')
			j *= 10;
		else
			nb = nb * 10 + (n[i] - 48);
		i++;
	}
	return (m * nb / j);
}
	int main(void)
{
	char	*test = "4552.55\n";
	float	result;
	float	control;

	result = ft_atof(test);
	control = atof(test);
	printf("Test result: %f\n", result);
	printf("Atof values: %f\n", control);
	return (0);
}
/* cc -Wall -Wextra -Werror test_atof.c && ./a.out  */