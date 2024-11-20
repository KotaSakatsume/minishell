/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:55:55 by kosakats          #+#    #+#             */
/*   Updated: 2024/11/11 20:48:15 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

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
// 	t_list	*new_node1;
// 	t_list	*new_node2;
// 	int		content1;
// 	int		content2;

// 	head = NULL;
// 	content1 = 42;
// 	content2 = 84;
// 	// 新しいノードを作成
// 	new_node1 = ft_lstnew(&content1);
// 	new_node2 = ft_lstnew(&content2);
// 	// テスト1: 空のリストに最初のノードを追加
// 	ft_lstadd_front(&head, new_node1);
// 	if (head == new_node1 && *(int *)(head->content) == 42
// 		&& head->next == NULL)
// 		printf("テスト1成功: 空のリストにノードを追加しました\n");
// 	else
// 		printf("テスト1失敗\n");
// 	// テスト2: リストの先頭に新しいノードを追加
// 	ft_lstadd_front(&head, new_node2);
// 	if (head == new_node2 && *(int *)(head->content) == 84
// 		&& head->next == new_node1)
// 		printf("テスト2成功: リストの先頭に新しいノードを追加しました\n");
// 	else
// 		printf("テスト2失敗\n");
// 	// メモリの解放
// 	free(new_node1);
// 	free(new_node2);
// 	return (0);
// }
