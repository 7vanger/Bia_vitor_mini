/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopes <vlopes@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:14:34 by vlopes            #+#    #+#             */
/*   Updated: 2023/07/12 15:14:47 by vlopes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc (count * size);
	if (count == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	if (!ptr)
		return (NULL);
	ft_memset (ptr, '\0', count * size);
	return (ptr);
}
