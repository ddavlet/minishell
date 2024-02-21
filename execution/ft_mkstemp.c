#include "execution.h"

int ft_mkstemp(char *template)
{
    char *chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int		num_chars = ft_strlen(chars);
    int len = ft_strlen(template);
    int fd = -1;
    if (len < 6 || ft_strncmp(&template[len - 6], "XXXXXX", 6) != 0)
    {
        ft_putstr_fd("Template must end with 'XXXXXX'\n", 2);
        return (-1);
    }
	int attempt = 0;
    while (attempt < 1000)
	{
		int i = 0;
        while (i < 6)
		{
            int r = rand_simple() % num_chars;
            template[len - 6 + i] = chars[r];
			i++;
		}
		attempt++;
	}
    fd = open(template, O_RDWR | O_CREAT | O_EXCL, 0600);
    if (fd != -1)
        return fd;
	return (-1);
}