#ifndef PRINTF_H
# define PRINTF_H

# include <unistd.h>
#include <stdarg.h>
# include <stdlib.h>

typedef struct		s_mod
{
	int				ac;
	int				w;
	int				f_f_w;
	int				f_f_ac;
	char			flag;
	int				minus;
	char			sp;
}					t_mod;

int			ft_atoi(char *str);
int			ft_isdigit(int ch);
void		*ft_memset(void *destimation, int c, size_t n);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strdup(const char *src);
char		*ft_strjoin(char *s1, char *s2, int flag);
size_t		ft_strlen(char *s);
char		*ft_strnstr(const char *s1, const char *s2, size_t len);
int			ft_printf(const char *format, ...);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strchr(char *str, int ch);
int		 	parce(const char *format, va_list argptr, int *i);
int			ft_obrabotchik(t_mod inf_mod, va_list argptr);
char		*ft_obrabotchik_for_s(t_mod inf_mod, char *str, int flag);
int			ft_handler(t_mod inf_mod, va_list argptr);
char		*perevorot(char *str);
char		*ft_accu_for_s(t_mod inf_mod, char *dup_str);
char		*new_str(t_mod inf_mod, va_list argptr, int *flag);
char		*ft_accuracy(t_mod inf_mod, char *str, char *dup_str, int *minus);
char		*ft_width(char flag, int width, char *str);
char		*perevorot(char *str);
char		*ft_perevod(va_list argptr, t_mod inf_mod, int sis_ch);
char		*int_diu(va_list argptr, char sp);
char		*handler_for_i_d2(t_mod *inf_mod, char *str, int *number);

#endif