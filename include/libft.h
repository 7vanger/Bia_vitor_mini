#ifndef LIBFT_H
# define LIBFT_H
# define BUFFER_SIZE 30

# include <unistd.h>
# include <stdlib.h>
# include "minishell.h" 
# include <stdint.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(const char *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	*ft_strchr(char *s, int c);
char	**ft_split(char *line, char c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *s1);
int		ft_isspace(int c);
char	*ft_ulstr(char *str);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
int		ft_isprint(int c);
int		ft_isalnum(int c);
int		ft_atoi(const char *str);
void	*ft_realloc(void *ptr, size_t size);
//int		ft_isspace(char *cmd);
int		ft_stristr(const char *haystack, const char *needle, size_t len);
char	*ft_itoa(int n);
int	    ft_isdigit(int c);

#endif