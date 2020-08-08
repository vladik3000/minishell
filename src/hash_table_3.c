/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:20:11 by fmallist          #+#    #+#             */
/*   Updated: 2020/08/08 17:36:30 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int					ht_insert(t_hash_table *ht, const char *key,
					const char *value)
{
	t_ht_item		*item;
	int				index;

	if (((ht->count * 100) / ht->size) > 70)
		ht_resize(ht, ht->size_index * 2);
	if (!(item = ht_new_item(key, value)))
		return (-1);
	index = ht_insert_insertion(ht, key, item);
	ht->items[index] = item;
	ht->count++;
	return (0);
}

void				ht_resize_helper(t_hash_table *ht,
					t_hash_table *new_ht, int tmp_size)
{
	t_ht_item	**tmp_items;

	tmp_items = NULL;
	ht->size_index = new_ht->size_index;
	ht->count = new_ht->count;
	tmp_size = ht->size;
	ht->size = new_ht->size;
	new_ht->size = tmp_size;
	tmp_items = ht->items;
	ht->items = new_ht->items;
	new_ht->items = tmp_items;
}
