#include "stdio.h"
#include "parsing2.h"

int main(void)
{
    const char  *line = "export a''rg'=''ech''o '2'";
    t_token     *tokens = tokenizer(line);

    while (tokens)
    {
        printf("literal: '%s'\n", tokens->literal);
        tokens = tokens->next;
    }
}