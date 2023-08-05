/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:17:04 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 15:17:17 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	length(int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n)
	{
		n /= 10;
		len ++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*a;
	size_t	i;

	a = ft_calloc((length(n) + 1), sizeof (char));
	if (!a)
		return (NULL);
	i = length(n);
	if (n < 0)
	{
		a[0] = '-';
		n *= -1;
		if (n == -2147483648)
			n = 2147483647;
	}
	if (n == 0)
		a[0] = '0';
	while (n > 0)
	{
		a[i - 1] = n % 10 + 48;
		if (a[0] == '-' && n == 2147483647)
			a[i - 1] = '8';
		n /= 10;
		i--;
	}
	return (a);
}
