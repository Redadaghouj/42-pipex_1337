/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 02:08:16 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/22 02:40:38 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	check(char *str, char *to_find, int k)
{
	int	size;
	int	j;

	j = 1;
	size = ft_strlen(to_find);
	while (to_find[j] == str[k] && to_find[j] != '\0')
	{
		j++;
		k++;
	}
	return (j == size);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	k;
	int	found;

	if (*to_find == '\0')
		return (str);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == to_find[0])
		{
			k = i + 1;
			found = check(str, to_find, k);
			if (found)
				return (&str[i]);
		}
		i++;
	}
	return (NULL);
}
