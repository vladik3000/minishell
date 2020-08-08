/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 18:04:59 by fmallist          #+#    #+#             */
/*   Updated: 2020/08/08 17:51:24 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ht_item			g_ht_deleted_item = {NULL, NULL};

void				ht_delete_hash_table(t_hash_table *ht)
{
	size_t		i;
	t_ht_item	*item;

	i = 0;
	item = NULL;
	while (i < ht->size)
	{
		item = ht->items[i];
		if (item != NULL && item != &g_ht_deleted_item)
			ht_delete_item(item);
		i++;
	}
	ft_memdel((void **)&(ht->items));
	ft_memdel((void **)&(ht));
}

int					ht_insert_insertion(t_hash_table *ht, const char *k,
					t_ht_item *item)
{
	t_ht_item	*cur_item;
	int			i;
	int			index;

	index = ht_get_hash(item->key, ht->size, 0);
	i = 1;
	cur_item = ht->items[index];
	while (cur_item != NULL && cur_item != &g_ht_deleted_item)
	{
		if (ft_strequ(cur_item->key, k))
		{
			ht_delete_item(cur_item);
			ht->items[index] = item;
			return (index);
		}
		index = ht_get_hash(item->key, ht->size, i);
		cur_item = ht->items[index];
		i++;
	}
	return (index);
}

char				*ht_search(t_hash_table *ht, const char *key)
{
	int			index;
	t_ht_item	*item;
	int			i;

	i = 1;
	if (ht == NULL)
		return (NULL);
	index = ht_get_hash(key, ht->size, 0);
	item = ht->items[index];
	while (item != NULL)
	{
		if (ft_strequ(item->key, key))
			return (item->value);
		index = ht_get_hash(key, ht->size, i);
		item = ht->items[index];
		i++;
	}
	return (NULL);
}

void				ht_delete_from_table(t_hash_table *ht, const char *key)
{
	int			index;
	t_ht_item	*item;
	int			i;
	int			load;

	load = (ht->count * 100) / ht->size;
	if (load < 10)
		ht_resize(ht, -1);
	index = ht_get_hash(key, ht->size, 0);
	item = ht->items[index];
	i = 1;
	while (item != NULL && item != &g_ht_deleted_item)
	{
		if (ft_strequ(item->key, key))
		{
			ht_delete_item(item);
			ht->items[index] = &g_ht_deleted_item;
		}
		index = ht_get_hash(key, ht->size, i);
		item = ht->items[index];
		i++;
	}
	ht->count--;
}

int					ht_resize(t_hash_table *ht, const int dir)
{
	int				new_size_index;
	t_hash_table	*new_ht;
	t_ht_item		*item;
	int				tmp_size;

	if ((new_size_index = ht->size_index + dir) < HT_INIT_BASE_SIZE)
		return (0);
	if (!(new_ht = ht_new_sized(new_size_index)))
		return (-1);
	tmp_size = -1;
	while (++tmp_size < (int)ht->size)
	{
		item = ht->items[tmp_size];
		if (item != NULL && item != &g_ht_deleted_item)
			if (ht_insert(new_ht, item->key, item->value) == -1)
				return (-1);
	}
	ht_resize_helper(ht, new_ht, tmp_size);
	ht_delete_hash_table(new_ht);
	return (0);
}
