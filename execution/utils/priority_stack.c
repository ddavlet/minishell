
#include "../execution.h"

int	cmds_size(void **cmds)
{
	int	size;

	size = 0;
	while (cmds[size])
		size++;
	return (size);
}

t_logic_op	*initialize_priority_stack(t_cmd **cmds)
{
	t_logic_op	*priority_stack;

	if (!cmds)
		return (NULL);
	priority_stack = (t_logic_op *)ft_calloc(cmds_size((void **)cmds),
			sizeof(t_logic_op));
	if (!priority_stack)
		return (NULL);
	priority_stack = ft_memset(priority_stack, 0, cmds_size((void **)cmds));
	if (!priority_stack)
	{
		free(priority_stack);
		return (NULL);
	}
	return (priority_stack);
}

t_logic_op	*push_stack(t_logic_op *priority_stack, t_logic_op op)
{
	t_logic_op	prev;
	t_logic_op	next;
	int			i;

	prev = priority_stack[0];
	priority_stack[0] = op;
	i = 1;
	while (prev != NONE)
	{
		next = priority_stack[i];
		priority_stack[i] = prev;
		prev = next;
		i++;
	}
	return (priority_stack);
}

t_logic_op	pop_stack(t_logic_op *priority_stack)
{
	t_logic_op	op;
	t_logic_op	next;
	t_logic_op	prev;
	int			i;

	op = priority_stack[0];
	i = 0;
	while (priority_stack[i] != NONE)
	{
		next = priority_stack[i + 1];
		priority_stack[i] = next;
		i++;
	}
	return (op);
}

// int	main(void)
// {
// 	ft_printf("Test initialize_priority_stack\n");
// 	t_cmd	**cmds;
// 	t_logic_op	*priority_stack;

// 	cmds = mockup_three_cmds();
// 	priority_stack = initialize_priority_stack(cmds);
// 	if (!priority_stack)
// 	{
// 		ft_printf("Error\n");
// 		return (1);
// 	}
// 	int i = 0;
// 	while (priority_stack[i] != NONE)
// 	{
// 		ft_printf("priority_stack[%d]: %d\n", i, priority_stack[i]);
// 		i++;
// 	}
// 	ft_printf("priority_stack[0]: %d\n", priority_stack[0]);

// 	ft_printf("Test push_stack\n");
// 	priority_stack = push_stack(priority_stack, LOGIC_OR);
// 	if (!priority_stack)
// 	{
// 		ft_printf("Error\n");
// 		return (1);
// 	}
// 	i = 0;
// 	while (priority_stack[i] != NONE)
// 	{
// 		ft_printf("priority_stack[%d]: %d\n", i, priority_stack[i]);
// 		i++;
// 	}
// 	ft_printf("priority_stack[0]: %d\n", priority_stack[0]);

// 	ft_printf("Test pop_stack\n");

// 	t_logic_op	op;
// 	op = pop_stack(priority_stack);
// 	if (op == NONE)
// 	{
// 		ft_printf("Error\n");
// 		return (1);
// 	}
// 	ft_printf("op: %d\n", op);
// 	i = 0;
// 	while (priority_stack[i] != NONE)
// 	{
// 		ft_printf("priority_stack[%d]: %d\n", i, priority_stack[i]);
// 		i++;
// 	}
// 	ft_printf("priority_stack[0]: %d\n", priority_stack[0]);
// 	return (0);
// }