/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:50:49 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/11 20:48:23 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
// 	t_list	*node1;
// 	int		content1;
// 	t_list	*node2;

// 	content1 = 42;
// 	// テスト1: 整数データを持つノードを作成
// 	node1 = ft_lstnew(&content1);
// 	if (node1 && *(int *)(node1->content) == 42 && node1->next == NULL)
// 		printf("テスト1成功: ノードが正しく作成されました\n");
// 	else
// 		printf("テスト1失敗\n");
// 	// テスト2: NULLデータでノードを作成
// 	node2 = ft_lstnew(NULL);
// 	if (node2 && node2->content == NULL && node2->next == NULL)
// 		printf("テスト2成功: NULLデータでノードが正しく作成されました\n");
// 	else
// 		printf("テスト2失敗\n");
// 	// メモリの解放
// 	free(node1);
// 	free(node2);
// 	return (0);
// }
