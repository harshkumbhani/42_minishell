/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_prototypes.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:56:18 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/12 15:01:03 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_PROTOTYPES_H
# define FREE_PROTOTYPES_H

# include "structs.h"

void	free_env_linked_list(t_env	*head);
void	free_env_node(t_env *node);
void	free_env_array(char **envp);

#endif