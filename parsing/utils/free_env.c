#include "../parsing.h"

void	free_env(t_env *shell_env)
{
	t_env	*tmp;

	if (!shell_env)
		return ;
	while (shell_env)
	{
		free_env(shell_env->child);
		tmp = shell_env;
		shell_env = shell_env->next;
		if (tmp->envp)
			free_ptr_str(tmp->envp);
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
}

