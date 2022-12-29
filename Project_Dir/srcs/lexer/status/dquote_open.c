/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote_open.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:18:47 by minseok2          #+#    #+#             */
/*   Updated: 2022/12/29 22:15:31 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/lexer1.h"

void	dquote_open(t_status *status, t_data *data, char **line, t_list *buffer_lst)
{
	if (**line == '\0')
		*status = ERROR; //quote 에러 dquote 에러 나눌 것인지
	else if (**line == '$')
		expand(status, data, line, buffer_lst);
	else if (**line == '\"')
	{
		*status = DQUOTE_CLOSE;
		(*line)++;
	}
	else
		lst_append(buffer_lst, new_node(*line));
}
