/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:25:55 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/10 17:08:11 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	else if (len > s_len - start)
		len = s_len - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[len] = '\0';
	return (substr);
}

// int	main(void)
// {
// 	char	*result;
// 	int		test_num;

// 	test_num = 1;
// 	// テストケース1：通常の部分文字列取得
// 	result = ft_substr("Hello, World!", 7, 5);
// 	printf("Test %d: %s\n", test_num++, result); // 期待結果: "World"
// 	free(result);
// 	// テストケース2：start が文字列の長さを超える場合
// 	result = ft_substr("Hello, World!", 20, 5);
// 	printf("Test %d: %s\n", test_num++, result); // 期待結果: "" (空の文字列)
// 	free(result);
// 	// テストケース3：len が残りの文字数を超える場合
// 	result = ft_substr("Hello, World!", 7, 50);
// 	printf("Test %d: %s\n", test_num++, result); // 期待結果: "World!"
// 	free(result);
// 	// テストケース4：len が 0 の場合
// 	result = ft_substr("Hello, World!", 5, 0);
// 	printf("Test %d: %s\n", test_num++, result); // 期待結果: "" (空の文字列)
// 	free(result);
// 	// テストケース5：空文字列からの部分文字列取得
// 	result = ft_substr("", 0, 5);
// 	printf("Test %d: %s\n", test_num++, result); // 期待結果: "" (空の文字列)
// 	free(result);
// 	return (0);
// }
