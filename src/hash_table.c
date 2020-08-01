/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 18:04:59 by fmallist          #+#    #+#             */
/*   Updated: 2020/03/15 18:08:30 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ht_item g_ht_deleted_item = {NULL, NULL};

int					ht_hash(const char *s, const int a, const int m)
{
	size_t		i;
	long		hash;
	size_t		len;

	hash = 0;
	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		hash += (long)ft_pow(a, len - (i + 1)) * s[i];
		hash = hash % m;
		i++;
	}
	return ((int)hash);
}

int					ht_get_hash(const char *s,
					const int num_buckets, const int attempt)
{
	int hash_a;
	int hash_b;

	hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
	hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
	return ((hash_a + (attempt * (hash_b + 1))) % num_buckets);
}

t_ht_item			*ht_new_item(const char *k, const char *v)
{
	t_ht_item *new_item;

	if (!(new_item = ft_memalloc(sizeof(t_ht_item))))
		return (NULL);
	if (!(new_item->key = ft_strdup(k)))
		return (NULL);
	if (!(new_item->value = ft_strdup(v)))
		return (NULL);
	return (new_item);
}

void				ht_delete_item(t_ht_item *item)
{
	ft_memdel((void **)&(item->key));
	ft_memdel((void **)&(item->value));
	ft_memdel((void **)(&item));
}

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

t_hash_table		*ht_new_sized(const size_t size_index)
{
	int				base_size;
	int				i;
	int				j;
	t_hash_table	*ht;

	if (size_index == 0)
		return (NULL);
	if (!(ht = ft_memalloc(sizeof(t_hash_table))))
		return (NULL);
	ht->size_index = size_index;
	base_size = 50 << ht->size_index;
	ht->size = ft_next_prime(base_size);
	ht->count = 0;
	if (!(ht->items = ft_memalloc(sizeof(t_ht_item *) * ht->size)))
		return (NULL);
	return (ht);
}

static int			ht_insert_insertion(t_hash_table *ht, const char *k,
					const char *v, t_ht_item *item)
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

int					ht_insert(t_hash_table *ht, const char *key,
					const char *value)
{
	t_ht_item		*item;
	int				index;
	t_ht_item		*cur_item;
	int				i;

	if (((ht->count * 100) / ht->size) > 70)
		ht_resize(ht, ht->size_index * 2);
	if (!(item = ht_new_item(key, value)))
		return (-1);
	index = ht_insert_insertion(ht, key, value, item);
	ht->items[index] = item;
	ht->count++;
	return (0);
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
	while (++tmp_size < ht->size)
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
