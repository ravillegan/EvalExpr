/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   svinkaPeppa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asantiag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 20:19:17 by asantiag          #+#    #+#             */
/*   Updated: 2019/03/17 06:18:19 by asantiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "functions.h"

typedef struct		s_nbr
{
	struct s_nbr	*next;
	int				num;
}					t_nbr;

typedef struct		s_op
{
	struct s_op		*next;
	char			sym;
	int				prior;
}					t_op;

void	op_push(t_op **head_op, char data, int pr)
{
	t_op *tmp;

	tmp = (t_op*)malloc(sizeof(t_op));
	tmp->sym = data;
	tmp->prior = pr;
	tmp->next = (*head_op);
	(*head_op) = tmp;
}

void	nbr_push(t_nbr **head_nbr, int data)
{
	t_nbr *tmp;

	tmp = (t_nbr*)malloc(sizeof(t_nbr));
	tmp->num = data;
	tmp->next = (*head_nbr);
	(*head_nbr) = tmp;
}

int		ft_atoi(char *str, int i)
{
	int res;

	res = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

int calc(int a, int b, char op)
{
	int res;

	if (op == '+')
		res = a + b;
	if (op == '/')
		res = a / b;
	if (op == '*')
		res = a * b;
	if (op == '%')
		res = a % b;
	if (op == '-')
		res = a - b;
	return (res);
}

void	pop_nbr(t_nbr **head_nbr, int val)
{
	t_nbr *prev;

	prev = (*head_nbr);
    (*head_nbr) = (*head_nbr)->next;
    free(prev);
	(*head_nbr)->num = val;
}

void	pop_op(t_op **head_op)
{
	t_op *prev;

	prev = (*head_op);
    (*head_op) = (*head_op)->next;
    free(prev);
}

int		eval_expr(char *str)
{
	t_nbr	*head_nbr;
	t_op	*head_op;
	int		i;
	int 	res;
	int flag;

	i = 0;
	res = 0;
	head_op = 0;
	head_nbr = 0;
	while (str[i])
	{
		/*if (head_nbr->next && head_op->next)
		{
			if (head_op->prior <= head_op->next->prior)
			{
				pop_nbr(&head_nbr, calc(head_nbr->next->num, head_nbr->num, head_op->sym));
				pop_op(&head_op);
			}
		}
		else if (head_nbr->next)
		{
			pop_nbr(&head_nbr, calc(head_nbr->next->num, head_nbr->num, head_op->sym));
			pop_op(&head_op);

		}*/
		flag = 0;
		if (str[i] == ' ')
			i++;
		if ((str[i] == '+' || str[i] == '-') && head_op && head_op->prior == 2)
		{
			pop_nbr(&head_nbr, calc(head_nbr->next->num, head_nbr->num, head_op->sym));
			pop_op(&head_op);
		}
		if (str[i] == '+' || str[i] == '-')
		{
			op_push(&head_op, str[i], 1);
			i++;
		}
		if (str[i] == '/' || str[i] == '*' || str[i] == '%')
		{

			op_push(&head_op, str[i], 2);
			flag = 1;
			i++;
		}
		if (str[i] >= '0' && str[i] <= '9')
			nbr_push(&head_nbr, ft_atoi(str, i));
		while (str[i] >= '0' && str[i] <= '9')
			i++;
		/*if (head_nbr->next && head_op->next)
		{
			if (head_op->prior <= head_op->next->prior)
			{
				pop_nbr(&head_nbr, calc(head_nbr->next->num, head_nbr->num, head_op->sym));
				pop_op(&head_op);
			}
		}*/
		if (head_nbr->next)
		{
			pop_nbr(&head_nbr, calc(head_nbr->next->num, head_nbr->num, head_op->sym));
			pop_op(&head_op);
		}
	}
	res = head_nbr->num;
	return (res);
}

int		main(int ac, char **av)
{
	if (ac > 1)
	{
		ft_putnbr(eval_expr(av[1]));
		ft_putchar('\n');
	}
	return (0);
}
