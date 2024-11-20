/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:00:19 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/11 20:50:16 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// #include <stdio.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

// int	main(void)
// {
// 	t_list	*head;
// 	t_list	*last;
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
// 	// テストケース1: 3つのノードを持つリストの最後のノードを確認
// 	last = ft_lstlast(head);
// 	printf("テストケース1: 期待結果: %d, 実際の結果: %d\n", content3, *(int *)last->content);
// 	// テストケース2: 空のリスト（NULLポインタ）を渡した場合
// 	last = ft_lstlast(NULL);
// 	printf("テストケース2: 期待結果: (NULL), 実際の結果: %s\n", last ? "データあり" : "(NULL)");
// 	// メモリの解放
// 	free(head->next->next);
// 	free(head->next);
// 	free(head);
// 	return (0);
// }
