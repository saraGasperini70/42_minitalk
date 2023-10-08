/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgasperi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 09:45:13 by sgasperi          #+#    #+#             */
/*   Updated: 2023/02/20 14:36:47 by sgasperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char str)
{
	return (write (1, &str, 1));
}

char	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		return (ft_putchar('-'));
		return (ft_putchar('2'));
		ft_putnbr(147483648);
	}
	else if (nb < 0)
	{
		return (ft_putchar('-'));
		nb = -nb;
		ft_putnbr(nb);
	}
	else if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
	{
		return (ft_putchar(nb + 48));
	}	
}

char	ft_putnbr_uns(unsigned int nb)
{
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
		ft_putnbr(nb);
	}
	else if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
	{
		ft_putchar(nb + 48);
	}
}

int	ft_putstr(char *str)

{
	int	len;

	len = 0;
	if (!str)
		return (write (1, "(null)", 6));
	while (str[len])
	{
		ft_putchar(str[len]);
		len++;
	}
	return (len);
}

int	ft_putnbr_hex_address(unsigned long nb, const char *map)
{
	int	i;

	i = 0;
	if (nb >= 16)
	{
		i += ft_putnbr_hex(nb / 16, map);
	}
	i += ft_putchar(map[nb % 16]);
	return (i);
}

int	ft_putnbr_hex(unsigned int nb, const char *map)
{
	int	i;

	i = 0;
	if (nb >= 16)
	{
		i += ft_putnbr_hex(nb / 16, map);
	}
	i += ft_putchar(map[nb % 16]);
	return (i);
}

int	ft_putnbr_paddress(unsigned long p, const char *str)
{
	int	i;
    
    i = 2;
	ft_putchar('0');
	ft_putchar('x');
	i += ft_putnbr_hex_address(p, str);
	return(i);
}

