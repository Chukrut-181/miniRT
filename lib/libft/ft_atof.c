/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:28:39 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/29 12:19:50 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Converts a string representation of a doubleing-point number to a double.
 *
 * The function iterates through the input string, handling an optional
 * leading sign ('-'). It accumulates the integer part of the number
 * and then handles the fractional part after a decimal point ('.').
 * The final double value is calculated by dividing the accumulated number
 * by the appropriate power of 10 based on the number of digits after
 * the decimal point and applying the sign.
 *
 * @param n A pointer to the null-terminated string representing the double.
 * @return The doubleing-point number represented by the input string.
 */

double	ft_atof(char *n)
{
	int		i;
	int		j;
	double	nb;
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
	while (n[i] && n[i] != '\n')
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
