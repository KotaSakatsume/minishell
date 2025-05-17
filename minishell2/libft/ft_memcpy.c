/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:49:42 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/10 21:15:09 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return ((char *)dest);
	if ((char *)dest == NULL || (char *)src == NULL)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

// int	main(void)
// {
// 	// char	str1[20] = ;
// 	// char	str2[20] = ;
// 	printf("%s\n", ft_memcpy("wwwwwwww", "aaaaaaa", 5));
// 	return (0);
// }

// int	main(void)
// {
// 	// Test case 1: Normal memory copy
// 	char src1[] = "Hello, World!";
// 	char dest1[20];                        // コピー先の配列
// 	memcpy(dest1, src1, strlen(src1) + 1); // +1 は NULL 終端もコピーするため
// 	printf("Test 1: %s\n", dest1);         // 期待結果: "Hello, World!"

// 	// Test case 2: Copy with overlap (src と dest が一部重なる場合)
// 	char str2[] = "Overlapping test";
// 	memcpy(str2 + 5, str2, 8);    // "Overlap" 部分を後ろにコピー
// 	printf("Test 2: %s\n", str2); // 期待結果: "OverOverlapping test"

// 	// Test case 3: Memory copy with zero length (コピーするバイト数が 0)
// 	char src3[] = "This will not copy.";
// 	char dest3[20];
// 	memcpy(dest3, src3, 0);
// 	printf("Test 3: %s\n", dest3); // 期待結果: "" (dest3は空のままで何もコピーされない)

// 	// Test case 4: Copying an empty string
// 	char src4[] = "";
// 	char dest4[10];
// 	memcpy(dest4, src4, strlen(src4) + 1); // 空文字列でもNULLをコピーする
// 	printf("Test 4: %s\n", dest4);         // 期待結果: "" (空文字列)

// 	// Test case 5: Copy a part of an array
// 	char src5[] = "Short copy test";
// 	char dest5[10];
// 	memcpy(dest5, src5, 5);        // 最初の5文字だけコピー
// 	dest5[5] = '\0';               // NULL 終端を追加
// 	printf("Test 5: %s\n", dest5); // 期待結果: "Short" (5文字だけコピー)

// 	// Test case 6: Copying more than the size of destination array
// 	char src6[] = "Too much data!";
// 	char dest6[10];
// 	memcpy(dest6, src6, sizeof(dest6) - 1); // dest6 のサイズ 9 バイト分コピー
// 	dest6[9] = '\0';                        // NULL 終端を追加
// 	printf("Test 6: %s\n", dest6);          // 期待結果: "Too much "

// 	return (0);
// }