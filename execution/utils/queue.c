#include "../execution.h"

t_queue	*initialize_queue(t_executor *exec)
{
	t_queue	*queue;
    int     pipe_count;
    t_pipe  *pipe;

    pipe_count = count_pipes(exec, false);
    queue = (t_queue *)ft_calloc(pipe_count, sizeof(t_queue));
    if (!queue)
        return NULL;
    while (pipe_count)
    {
        pipe = create_pipe();
        enqueue_pipe(queue, pipe);
    }
    queue->front = NULL;
    queue->rear = NULL;
	return queue;
}

int	enqueue_pipe(t_queue *queue, t_pipe *pipe)
{
	t_node	*new_node;

	if (!queue || !pipe)
		return (0);
	new_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!new_node)
		return (0);
	new_node->pipe = pipe;
	if (!queue->front)
		queue->front = new_node;
	else
		queue->rear->next = new_node;
	queue->rear = new_node;
	return (1);
}

t_pipe	*dequeue_pipe(t_queue *queue)
{
	t_node	*node;
	t_pipe	*pipe;

	if (!queue || !queue->front)
		return (NULL);
	node = queue->front;
	pipe = node->pipe;
	queue->front = node->next;
	free(node);
	return (pipe);
}

void	free_queue(t_queue *queue)
{
	t_node	*node;
	t_node	*next;

	if (!queue)
		return ;
	node = queue->front;
	while (node)
	{
		next = node->next;
		free(node->pipe->pipe_fd);
		free(node->pipe->read);
		free(node->pipe->write);
		free(node->pipe);
		free(node);
		node = next;
	}
	free(queue);
}

