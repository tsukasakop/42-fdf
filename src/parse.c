/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 09:21:46 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/26 22:51:25 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_memory.h"
#include "libft.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_isdigits(const unsigned char *s)
{
	if (*s == '\0')
		return (false);
	if (*s == '+' || *s == '-')
		s++;
	while (ft_isdigit(*s))
		s++;
	return (*s == '\0');
}

char	**mm_split(t_memory_manager *mm, char *s, char c)
{
	char	**p;
	size_t	i;

	i = 0;
	p = ft_split(s, c);
	ft_mmadd(mm, p);
	while (p[i] != NULL)
		ft_mmadd(mm, p[i++]);
	return (p);
}

bool	parse_fdf(t_model *m, int fd, t_memory_manager *mm)
{
	int		i;
	int		j;
	char	*line;
	char	**cur;

	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		j = -1;
		cur = mm_split(mm, line, ' ');
		while (cur[++j] != NULL)
		{
			if (cur[j][0] == '\n')
				break ;
			if (!ft_isdigits((const unsigned char *)cur[j]))
				return (false);
			m->p[i][j] = (t_point){j, i, ft_atoi(cur[j]), m->p[i][j].color = 0xffffffff};
		}
		line = get_next_line(fd);
		i++;
	}
	m->x_len = i;
	m->y_len = j;
	return (true);
}

t_model	*get_model(char *fname)
{
	t_model				*m;
	t_memory_manager	*mm;
	int					fd;

	if (fname == NULL)
		return (NULL);
	fd = open(fname, O_RDONLY);
	if (fd == -1)
		return (NULL);
	m = (t_model *)ft_g_mmmalloc(sizeof(t_model));
	mm = ft_mmnew();
	if (!parse_fdf(m, fd, mm))
		return (NULL);
	ft_mmfree(mm);
	close(fd);
	return (m);
}
