#include "../parsing.h"

static int	remove_envvar(t_env	*shell_env, const char *name)
{
	t_env	*child;

	child = shell_env->child;
	if (!name)
		return (1);
	while (child)
	{
		if (child->letter == *name && *(name + 1))
		{
			child = child->child;
			name++;
		}
		else if (child->letter == *name && !*(name + 1))
		{
			if (child->exists == true)
			{
				free(child->content);
				child->exists = false;
				return (0);
			}
		}
		else
			child = child->next;
	}
	return (1);
}

int	unset_envvar(t_env *shell_env, const char *to_find)
{
	if (remove_envvar(shell_env, to_find))
		return (1);
	else
	{
		free_ptr_str(shell_env->envp);
		shell_env->envp = init_envv(shell_env);
	}
	return (0);
}
