#include "execution.h"

int create_temp_file(char **template)
{
    *template = "/tmp/cmdtmpXXXXXX"; // This could be made more dynamic
    int fd = mkstemp(*template);
    if (fd == -1)
    {
        perror("mkstemp");
        return -1;
    }
    unlink(*template); // Ensure the file is removed when closed
    return fd;
}

int handle_here_document(const char *delimiter)
{
    char *template;
    int fd;
	
	fd = create_temp_file(&template);
    if (fd == -1)
	{
		perror("mkstemp");
		return -1;
    }
    unlink(template); // Ensure the file is removed when closed
    char *line = readline("%% ");
    while ((line ) != NULL)
    {
        if (strcmp(line, delimiter) == 0)
        {
            free(line);
            break; // Delimiter reached, stop reading input
        }
        write(fd, line, strlen(line)); // Write the line to the file
        write(fd, "\n", 1); // Add newline character after each line
        free(line);
        line = readline("%% ");
    }
    free(line);
    close(fd);
    fd = open(template, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return -1;
    }
    return fd;
}
