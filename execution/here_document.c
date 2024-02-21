#include "execution.h"

int handle_here_document(const char *delimiter)
{
    char *template;
    int fd;
	
    template = "/tmp/cmdtmpXXXXXX";
	fd = mkstemp(template);
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
            // Check if the line is the delimiter
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
