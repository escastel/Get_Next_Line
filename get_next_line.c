/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:08:18 by escastel          #+#    #+#             */
/*   Updated: 2023/06/08 13:52:51 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*void	ft_lek(void)
{
	system("leaks -q a.out");
}
 */
static char	*get_piece(char *strg, int fd)
{
	char	*aux;
	int		rtn;

	if (!strg)
	{
		strg = (char *)ft_calloc(1, sizeof(char));
		if (!strg)
			return (NULL);
	}
	rtn = 1;
	aux = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!aux)
		return (free(strg), strg = NULL, NULL);
	while (rtn > 0 && !ft_strchr(aux, '\n'))
	{
		rtn = read(fd, aux, BUFFER_SIZE);
		if (rtn < 0)
			return (free(aux), free(strg), aux = NULL, strg = NULL, NULL);
		aux[rtn] = '\0';
		strg = ft_strjoin(strg, aux);
		if (!strg)
			return (free(strg), free(aux), aux = NULL, strg = NULL, NULL);
	}
	return (free(aux), aux = NULL, strg);
}

static char	*get_line(char	*strg)
{
	char	*line;
	int		i;

	i = 0;
	if (!strg[i])
		return (NULL);
	while (strg[i] && strg[i] != '\n')
		i++;
	line = (char *)ft_calloc((i + 2), sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (strg[i] && strg[i] != '\n')
	{
		line[i] = strg[i];
		i++;
	}
	if (strg[i] && strg[i] == '\n')
		line[i] = '\n';
	line[++i] = '\0';
	return (line);
}

static char	*ft_clean(char *strg)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	while (strg[i] && strg[i] != '\n')
		i++;
	if (strg[i] == '\0')
		return (free(strg), strg = NULL, NULL);
	new_line = (char *)ft_calloc((ft_strlen(strg) - i + 1), sizeof(char));
	if (!new_line)
		return (free(strg), strg = NULL, NULL);
	i++;
	j = 0;
	while (strg[i])
		new_line[j++] = strg[i++];
	new_line[j] = '\0';
	return (free(strg), strg = NULL, new_line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*strg;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
		return (free(strg), strg = NULL, NULL);
	strg = get_piece(strg, fd);
	if (!strg)
		return (free(strg), strg = NULL, NULL);
	line = get_line(strg);
	if (!line)
		return (free(strg), strg = NULL, NULL);
	strg = ft_clean(strg);
	return (line);
}

/* #include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*str;

	atexit(ft_lek);
	fd = open("texto.tx", O_RDONLY);
	str = get_next_line(fd);
	while (str != NULL)
	{
		printf("%s", str);
		str = get_next_line(fd);
	}
	close(fd);
	return (0);
} */
