/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 02:05:56 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/03/24 02:46:16 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	else if (!s1 && s2)
		return (ft_strdup(s2));
	else if (s1 && !s2)
		return (ft_strdup(s1));
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	str[i++] = '/';
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
