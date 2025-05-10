/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:11:02 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/10 10:55:37 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
// static void	to_upper(unsigned int i, char *c)
// {
// 	if (i % 2 == 1 && *c >= 'a' && *c <= 'z')
// 	{
// 		*c -= 32;
// 	}
// }

// int	main(void)
// {
// 	char	str[] = "hello world";

// 	ft_striteri(str, to_upper);
// 	printf("%s\n", str);
// 	return (0);
// }
