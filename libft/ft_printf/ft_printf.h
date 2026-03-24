/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdon <rbourdon@student.42paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:20:56 by rbourdon          #+#    #+#             */
/*   Updated: 2025/12/13 14:00:08 by rbourdon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft.h"

typedef struct s_format
{
	char		type;
	int			left_align;
	int			sign;
	int			width;
	int			zero_spaces;
	int			htag;
	int			space;
	int			precision;
	int			prec_len;
	int			len_hex;
	char		*ret_hex;
	int			diff_prec_len;
	int			diff_width_prec;
	int			percent;
	int			sign_done;
}				t_format;

int		ft_printf(const char *s, ...);
int		ft_print_char(int c, t_format *format);
int		ft_print_string(char *s, t_format *format);
int		ft_print_pointer(unsigned long nb, t_format *format);
int		ft_print_integer(int nb, t_format *format);
int		ft_print_uinteger(unsigned int nb, t_format *format);
int		ft_converter_lower_hex(unsigned int nb, char *s);
int		ft_converter_upper_hex(unsigned int nb, char *s);
void	ft_reinit_format(t_format *format);
void	ft_spaces_filler(int n);
int		ft_max_len(int len1, int len2, int len3);
void	ft_zero_filler(int n);
void	ft_print_sign(int nb);
int		ft_read_format(const char *s, t_format *format, va_list ap);
int		ft_work_sender(va_list ap, t_format *format);
int		ft_get_first_flag(const char *s, t_format *format);
int		ft_integer_size(int nb);
int		ft_width_star(char c, t_format *format, va_list ap);
int		ft_prec_star(char c, t_format *format, va_list ap);
void	ft_special_putnbr_fd(t_format *format, int n, int fd);
int		ft_sign(int nb);
void	ft_print_integer_laligned(int nb, int len, t_format *format);
void	ft_print_integer_normal(int nb, int len, t_format *format);
void	ft_print_uinteger_laligned(unsigned int nb, int len, t_format *format);
void	ft_print_uinteger_normal(unsigned int nb, int len, t_format *format);
int		ft_print_lower_hex(unsigned int nb, t_format *format);
int		ft_print_upper_hex(unsigned int nb, t_format *format);
void	ft_print_lhex_laligned(unsigned int nb, int i, t_format *format);
void	ft_print_lhex_normal(unsigned int nb, int i, t_format *format);
void	ft_print_uhex_laligned(unsigned int nb, int i, t_format *format);
void	ft_print_uhex_normal(unsigned int nb, int i, t_format *format);
int		ft_min_len(int len1, int len2);
void	ft_print_pointer_laligned(char *s, int len, t_format *format, int i);
void	ft_print_pointer_normal(char *s, int len, t_format *format, int i);
int		ft_print_percent(void);
void	ft_print_string_laligned(int len, char *s, t_format *format, int *i);
void	ft_print_string_normal(int len, char *s, t_format *format, int *i);
int		ft_print_string_null(t_format *format);
int		ft_print_string_null_lalign(t_format *format);
int		ft_print_string_null_normal(t_format *format);
int		ft_diff_or_zero(int len1, int len2);
void	ft_print_integer_normal_noprec(int nb, int len, t_format *format);
int		ft_max(int len1, int len2);
void	ft_print_uinteger_normal_noprec(int len, t_format *format);
void	ft_special_putuint_fd(t_format *format, unsigned int nb, int fd);
int		ft_uint_size(unsigned int nb);
void	ft_htag_handler(t_format *format);
void	ft_htag_handler_lhex_laligned(t_format *format);
void	ft_hex_spaces_handler(t_format *format);
void	ft_htag_handler_uhex_laligned(t_format *format);
int		ft_print_string_nil_normal(t_format *format);
int		ft_print_string_nil_lalign(t_format *format);
int		ft_lconverter_lower_hex(unsigned long nb, char *s);
void	ft_spaceflag_handler(t_format *format, int nb);
int		ft_spaceflag_return_handler(t_format *format, int nb, int len);
void	ft_print_integer_helper(t_format *format, int *len, int nb);

#endif
