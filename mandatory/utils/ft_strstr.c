/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 02:08:16 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/26 03:39:20 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	check(char *str, char *to_find, int i)
{
	int	size;
	int	j;

	j = 1;
	size = ft_strlen(to_find);
	while (to_find[j] == str[i] && to_find[j] != '\0')
	{
		j++;
		i++;
	}
	return (j == size);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	found;

	if (*to_find == '\0')
		return (str);
	if (str[0] != '\0')
	{
		if (str[0] == to_find[0])
		{
			found = check(str, to_find, 1);
			if (found)
				return (&str[0]);
		}
	}
	return (NULL);
}
