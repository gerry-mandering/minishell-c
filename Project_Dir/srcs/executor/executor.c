/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junlee2 <junlee2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:19:28 by junlee2           #+#    #+#             */
/*   Updated: 2023/01/03 13:36:02 by junlee2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

/*
 * 파이프 없음 && 빌트인 : no fork()
 */

int	check_and_exec_single_builtin(t_data *data)
{
	t_proc_data		*proc_data;
	char			*key;
	t_builtin_fp	bt_fp;

	proc_data = list_peek_first_content(&data->proc_data_list);
	key = list_peek_first_content(&proc_data->cmd_list);
	bt_fp = builtin_find(&data->builtin_list, key);
	if (list_size(&data->proc_data_list) == 1 && bt_fp != NULL)
	{
		return (1);
	}
	return (0);
}

void	wait_child(t_data *data)
{
	t_node	*pid_node;

	pid_node = list_peek_first_node(&data->pid_list);
	while (pid_node != NULL)
	{
		waitpid(*(pid_t *)pid_node->content, &g_last_exit_status, 0);
		pid_node = pid_node->next;
	}
}

pid_t	do_fork(t_data *data, t_proc_data *proc_data)
{
	pid_t		pid;
	int			pip[2];
	int			pipe_stat;
	static int	prev_read_end = -1;

	if (prev_read_end != -1)
		close(prev_read_end);
	pipe_stat = pipe(pip);
	if (pipe_stat != 0)
	{
		wait_child(data);
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
		execute_child(data, proc_data, pip, prev_read_end);
	prev_read_end = pip[0];
	close(pip[1]);
	return (pid);
}

void	make_child(t_data *data)
{
	t_node	*proc_node;
	pid_t	*pid;

	proc_node = list_peek_first_node(&data->proc_data_list);
	while (proc_node->next != NULL)
	{
		pid = ft_calloc(1, sizeof(pid_t));
		*pid = do_fork(data, proc_node->content);
		list_append(&data->pid_list, (void *)pid);
		proc_node = proc_node->next;
	}
}

void	executor(t_data *data)
{
	if (check_and_exec_single_builtin(data))
		return ;
	make_child(data);
	wait_child(data);
}
