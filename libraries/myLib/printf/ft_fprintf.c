/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:42:34 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/26 12:51:10 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	f_strlen(char *s)
{
	int	i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

static int	fput_string(char *s, int fd)
{
	int	len;

	len = 0;
	if (s == NULL)
		s = "(null)";
	if (write(fd, s, f_strlen(s)) < 0)
		return (-1);
	len += f_strlen(s);
	return (len);
}

static int	format_type(char c, va_list ap, int *len, int fd)
{
	int	temp_len;

	temp_len = 0;
	if (c == 's')
		temp_len = fput_string(va_arg(ap, char *), fd);
	else
		temp_len = 0;
	*len += temp_len;
	return (0);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	int		len;
	char	*str;
	va_list	ap;

	len = 0;
	str = (char *)format;
	va_start(ap, format);
	while (*str)
	{
		if (*str == '%')
		{
			if (*(str + 1) && (format_type(*(++str), ap, &len, fd) < 0))
				return (-1);
		}
		else
		{
			if (write(fd, str, 1) < 0)
				return (-1);
			len++;
		}
		str++;
	}
	va_end(ap);
	return (len);
}
