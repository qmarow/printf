#ifndef PRINTF_H
# define PRINT_H

# include <unistd.h>
# include <stdlib.h>

typedef struct		s_mod
{
	int				accuracy;
	int				width;
	int				flag_for_width;
	int				flag_for_accu;
	char			flag;
	char			specifier;
}					t_mod;

int			ft_atoi(char *str);
int			ft_isdigit(int ch);
void		*ft_memset(void *destimation, int c, size_t n);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strdup(const char *src);
char		*ft_strjoin(char *s1, char *s2, int flag);
size_t		ft_strlen(const char *s);
char		*ft_strnstr(const char *s1, const char *s2, size_t len);
int			ft_printf(const char *format, ...);

#endif