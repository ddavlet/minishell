#include "../execution.h"

static void process_reading(int fd, const char *delimiter)
{
    char *line;
    
    line = readline("\"> ");
    while ((line ) != NULL)
    {
        if (strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        write(fd, line, strlen(line));
        write(fd, "\n", 1);
        free(line);
        line = readline("\"> ");
    }
    free(line);
}

int handle_here_document(const char *delimiter)
{
    int fd;
    char *template;

    template = "/tmp/cmdtmpXXXXXX";
    fd = ft_mkstemp(template);
    if (fd == -1)
	{
		perror("mkstemp");
		return -1;
    }
    unlink(template);
    process_reading(fd, delimiter);
    close(fd);
    fd = open(template, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return -1;
    }
    return fd;
}
