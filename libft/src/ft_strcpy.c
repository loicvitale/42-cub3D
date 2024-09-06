/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhouyet <jhouyet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:18:53 by jhouyet           #+#    #+#             */
/*   Updated: 2024/02/21 11:20:31 by jhouyet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char	*save;

	save = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (save);
}
