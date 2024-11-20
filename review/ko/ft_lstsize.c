/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:58:40 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/11 20:48:27 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

// #include <stdio.h>

// // リストの新しいノードを作成するためのヘルパー関数
// t_list	*ft_lstnew(void *content)
// {
// 	t_list	*new_node;

// 	new_node = (t_list *)malloc(sizeof(t_list));
// 	if (!new_node)
// 		return (NULL);
// 	new_node->content = content;
// 	new_node->next = NULL;
// 	return (new_node);
// }

// int	main(void)
// {
// 	t_list	*head;
// 	int		content1;
// 	int		content2;
// 	int		content3;

// 	head = NULL;
// 	content1 = 42;
// 	content2 = 84;
// 	content3 = 126;
// 	// ノードを作成してリストに追加
// 	head = ft_lstnew(&content1);
// 	head->next = ft_lstnew(&content2);
// 	head->next->next = ft_lstnew(&content3);
// 	// テストケース1: 3つのノードを持つリストのサイズを確認
// 	printf("テストケース1: 期待結果: 3, 実際の結果: %d\n", ft_lstsize(head));
// 	// テストケース2: 空のリスト（NULLポインタ）を渡した場合
// 	printf("テストケース2: 期待結果: 0, 実際の結果: %d\n", ft_lstsize(NULL));
// 	// メモリの解放
// 	free(head->next->next);
// 	free(head->next);
// 	free(head);
// 	return (0);
// }
