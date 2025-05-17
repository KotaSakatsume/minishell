/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:21:46 by kosakats          #+#    #+#             */
/*   Updated: 2025/05/17 16:07:11 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strndup(const char *s, size_t n)
{
	size_t len = strnlen(s, n);  // 実際にコピーする長さを計算
	char *dup = malloc(len + 1); // 終端文字分を含む領域を確保
	if (!dup)
	{
		return (NULL); // メモリ確保失敗時
	}
	memcpy(dup, s, len); // 必要な文字をコピー
	dup[len] = '\0';     // ヌル文字で終端
	return (dup);
}
#include <stdio.h>

// int	main(void)
// {
// 	const char	*original = "Hello, World!";
// 	char		*copy;

// 	copy = ft_strndup(original, 5);
// 	if (copy)
// 	{
// 		printf("Copied string: %s\n", copy); // "Hello" と表示される
// 		free(copy);                          // メモリを解放
// 	}
// 	else
// 	{
// 		printf("Memory allocation failed.\n");
// 	}
// 	return (0);
// }
