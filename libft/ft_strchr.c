/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:23:01 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/10 21:17:57 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if ((char)c == '\0')
		return ((char *)s);
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	*result;

// 	// テストケース1：'o'が文字列内に最初に現れる場合
// 	result = strchr("Hello, World!", 'o');
// 	printf("Test 1: %s\n", result); // 期待結果: "o, World!"
// 	// テストケース2：文字列内に'z'が存在しない場合
// 	result = strchr("Hello, World!", 'z');
// 	printf("Test 2: %s\n", result); // 期待結果: (NULL)
// 	// テストケース3：文字列内の先頭文字を探す場合
// 	result = strchr("Hello, World!", 'H');
// 	printf("Test 3: %s\n", result); // 期待結果: "Hello, World!"
// 	// テストケース4：文字列内に複数回現れる文字
// 	result = strchr("Hello, Hello!", 'l');
// 	printf("Test 4: %s\n", result); // 期待結果: "llo, Hello!"
// 	// テストケース5：文字列の終端文字'\0'を探す場合
// 	result = strchr("Hello, World!", '\0');
// 	printf("Test 5: %s\n", result); // 期待結果: "" (文字列の終わり)
// 	return (0);
// }
