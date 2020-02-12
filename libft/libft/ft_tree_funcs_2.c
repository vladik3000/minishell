/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_funcs_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 17:48:20 by fmallist          #+#    #+#             */
/*   Updated: 2020/02/01 17:53:47 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tree_apply_infix(t_tree *root, void (*applyf)(void *))
{
	if (!root)
		return ;
	ft_tree_apply_infix(root->left, applyf);
	applyf(root->item);
	ft_tree_apply_infix(root->right, applyf);
}

void	ft_tree_apply_infix_options(t_tree *root, void *options,
		void (*applyf)(void *, void *))
{
	if (!root)
		return ;
	ft_tree_apply_infix_options(root->left, options, applyf);
	applyf(root->item, options);
	ft_tree_apply_infix_options(root->right, options, applyf);
}
