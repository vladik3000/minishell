/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_funcs_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 18:17:01 by fmallist          #+#    #+#             */
/*   Updated: 2020/02/08 20:06:07 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_tree			*ft_tree_create_node(void *item)
{
	t_tree *newnode;

	if (!(newnode = (t_tree *)malloc(sizeof(t_tree))))
		return (NULL);
	newnode->item = item;
	newnode->left = NULL;
	newnode->right = NULL;
	return (newnode);
}

int				ft_tree_insert(t_tree **root,
			void *item, int (*cmp)(void *, void *))
{
	t_tree *newnode;
	t_tree *current;
	t_tree *parent;

	if (!root || !cmp || !(newnode = ft_tree_create_node(item)))
		return (-1);
	if (!(*root))
	{
		*root = newnode;
		return (0);
	}
	current = *root;
	parent = NULL;
	while (current != NULL)
	{
		parent = current;
		current = (cmp(item, current->item) ? current->right : current->left);
	}
	if (cmp(item, parent->item))
		parent->right = newnode;
	else
		parent->left = newnode;
	return (0);
}

void			ft_tree_delete(t_tree *root)
{
	if (!root)
		return ;
	ft_tree_delete(root->left);
	ft_tree_delete(root->right);
	free(root->item);
	root->item = NULL;
	free(root);
	root = NULL;
}

uint64_t		ft_tree_count_nodes(const t_tree *root)
{
	uint64_t res;

	if (!root)
		return (0);
	res = 1;
	if (root->left != NULL)
	{
		res += ft_tree_count_nodes(root->left);
	}
	if (root->right != NULL)
	{
		res += ft_tree_count_nodes(root->right);
	}
	return (res);
}
