/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:16:29 by fmallist          #+#    #+#             */
/*   Updated: 2020/08/08 17:35:26 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_hash_table		*ht_new_sized(const size_t size_index)
{
	int				base_size;
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
