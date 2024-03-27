#include "parsing2.h"

t_cmd   **parse_line(const char *line)
{
    t_token *tokens;

    tokens = tokenizer(line);
    
}