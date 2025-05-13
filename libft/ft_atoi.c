/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:07:53 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/11 21:03:48 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			n;
	long long	result;

	i = 0;
	n = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (str[i] - '0') + (result * 10);
		if ((long long)(result * n) >= (long long)LONG_MAX)
			return ((int)LONG_MAX);
		if ((long long)LONG_MIN >= (long long)result * n)
			return ((int)LONG_MIN);
		i++;
	}
	return ((int)(result * n));
}
// int	main(void)
// {
// 	int ft_result;
// 	int std_result;

// 	// テストケース
// 	const char *test_cases[] = {
// 		"123",                  // 通常の正の数
// 		"-123",                 // 通常の負の数
// 		"0",                    // ゼロ
// 		"+456",                 // 正の数（+付き）
// 		"   789",               // 先頭に空白
// 		"2147483647",           // INT_MAX
// 		"-2147483648",          // INT_MIN
// 		"9223372036854775807",  // LONG_MAX
// 		"-9223372036854775808", // LONG_MIN
// 		"9223372036854775809",  // LONG_MAX + 1（オーバーフロー）
// 		"-9223372036854775810", // LONG_MIN - 1（アンダーフロー）
// 		"  + 42",               // 無効な形式（+の後にスペース）
// 		"abc123",               // 無効な形式（数字の前に文字）
// 		"123abc",               // 無効な形式（数字の後に文字）
// 		NULL                    // 配列の終端
// 	};
// 	// 各テストケースで ft_atoi と標準 atoi の結果を比較
// 	for (int i = 0; test_cases[i] != NULL; i++)
// 	{
// 		ft_result = ft_atoi(test_cases[i]);
// 		std_result = atoi(test_cases[i]);
// 		printf("テストケース: \"%s\"\n", test_cases[i]);
// 		printf("  ft_atoi: %d\n", ft_result);
// 		printf("  atoi   : %d\n", std_result);
// 		if (ft_result == std_result)
// 		{
// 			printf("  結果 : PASS\n");
// 		}
// 		else
// 		{
// 			printf("  結果 : FAIL\n");
// 		}
// 		printf("-----------------------\n");
// 	}

// 	return (0);
// }