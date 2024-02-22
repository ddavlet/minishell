#include "../execution.h"

// static int rand_simple(void)
// {
//     static unsigned int seed = 0;
//     seed = seed * 1103515245 + 12345;
//     return (seed / 65536) % 32768;
// }

void    assign_id(char *template, int len)
{
    char *chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int num_chars;
    int i;
    int r;

    num_chars = ft_strlen(chars);
    i = 0;
    while (i < len)
    {
        if (template[i] == 'X')
        {
            r = rand_simple() % num_chars;
            template[i] = chars[r];
        }
        i++;
    }
}

int ft_mkstemp(char *template)
{
    int fd = -1;
    int len;

    len = ft_strlen(template);
    if (len < 6 || ft_strncmp(template + (len - 6), "XXXXXX", 6) != 0)
    {
        ft_putstr_fd("Template must end with 'XXXXXX'\n", 2);
        return (-1);
    }
    assign_id(template, len);
    fd = open(template, O_RDWR | O_CREAT | O_EXCL, 0600);
    if (fd == -1)
        return (-1);
    else
	    return (fd);
}
