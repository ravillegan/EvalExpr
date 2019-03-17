/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asantiag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:14:37 by asantiag          #+#    #+#             */
/*   Updated: 2019/03/17 01:34:02 by asantiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void	ft_putnbr(int nb)
{
	int index;
	int minint;

	index = 0;
	minint = -2147483648;
	if (nb < 0)
	{
		if (nb == minint)
			index = 1;
		ft_putchar('-');
		nb = (nb + index) * (-1);
	}
	if (nb / 10 == 0)
	{
		ft_putchar('0' + nb);
	}
	else
	{
		ft_putnbr(nb / 10);
		ft_putchar('0' + nb % 10 + index);
	}
}
