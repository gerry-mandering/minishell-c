/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:19:23 by minseok2          #+#    #+#             */
/*   Updated: 2023/01/02 21:26:38 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/lexer1.h"

void	quote_close(t_status *status, t_pack *pack)
{
	if (pack->line[pack->index + 1] == '\0' || \
			pack->line[pack->index + 1] == ' ')
		create_token(pack->token_lst, &pack->buffer_lst, T_WORD);
	*status = BRANCH;
	pack->index++;
}
