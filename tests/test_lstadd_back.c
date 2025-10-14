/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:03:26 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 20:23:04 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../libft.h"

/* reference implementation */
static void lstadd_back(t_list **lst, t_list *new)
{
    t_list *temp;

    if (!lst)
        return;
    if (!*lst)
    {
        *lst = new;
        return;
    }
    temp = *lst;
    while (temp->next)
        temp = temp->next;
    temp->next = new;
}

static t_list *mk_node(void *content)
{
    t_list *n = malloc(sizeof(t_list));
    if (!n) return NULL;
    n->content = content;
    n->next = NULL;
    return n;
}

static void append_node(t_list **lst, t_list *node)
{
    if (!lst || !node) return;
    if (!*lst)
    {
        *lst = node;
        return;
    }
    t_list *it = *lst;
    while (it->next)
        it = it->next;
    it->next = node;
}

static void free_list(t_list *lst)
{
    while (lst)
    {
        t_list *next = lst->next;
        free(lst);
        lst = next;
    }
}

static int cmp_lists(t_list *a, t_list *b)
{
    while (a && b)
    {
        if (a->content != b->content)
            return 0;
        a = a->next;
        b = b->next;
    }
    return a == NULL && b == NULL;
}

int group_lstadd_back(void)
{
	group_start("lstadd_back");

    /* subtest 1: NULL list pointer, new node non-NULL -> should do nothing */
    {
        t_list *new_node = mk_node((void*)42);
        ft_lstadd_back(NULL, new_node); /* should not crash */
        SUBTEST_OK();
        free(new_node);
    }

    /* subtest 2: *lst == NULL, new node non-NULL -> list should point to new_node */
    {
        t_list *lst = NULL;
        t_list *exp = NULL;

        t_list *n1 = mk_node((void*)100);
        t_list *n2 = mk_node((void*)100); /* separate node for expected list */

        ft_lstadd_back(&lst, n1);
        lstadd_back(&exp, n2);

        if (cmp_lists(lst, exp)) SUBTEST_OK();
        else SUBTEST_FAILF("diff: lists mismatch");

        free_list(lst);
        free_list(exp);
    }

    /* subtest 3: multiple nodes, append new node -> last node should match reference */
    {
        t_list *lst = NULL;
        t_list *exp = NULL;

        /* build initial lists with separate nodes */
        for (int i = 1; i <= 3; i++)
        {
            append_node(&lst, mk_node((void*)(long)i));
            append_node(&exp, mk_node((void*)(long)i));
        }

        /* new nodes to append */
        t_list *new_ft = mk_node((void*)99);
        t_list *new_ref = mk_node((void*)99);

        ft_lstadd_back(&lst, new_ft);
        lstadd_back(&exp, new_ref);

        if (cmp_lists(lst, exp)) SUBTEST_OK();
        else SUBTEST_FAILF("diff: lists mismatch");

        free_list(lst);
        free_list(exp);
    }

    /* subtest 4: new node NULL -> list should remain unchanged */
    {
        t_list *lst = mk_node((void*)123);
        t_list *exp = mk_node((void*)123);

        ft_lstadd_back(&lst, NULL);
        lstadd_back(&exp, NULL);

        if (cmp_lists(lst, exp)) SUBTEST_OK();
        else SUBTEST_FAILF("diff: lists mismatch");

        free_list(lst);
        free_list(exp);
    }

    /* subtest 5: long list -> append at end */
    {
        t_list *lst = NULL;
        t_list *exp = NULL;
        const int N = 1000;

        for (int i = 0; i < N; i++)
        {
            append_node(&lst, mk_node((void*)(long)i));
            append_node(&exp, mk_node((void*)(long)i));
        }

        t_list *new_ft = mk_node((void*)9999);
        t_list *new_ref = mk_node((void*)9999);

        ft_lstadd_back(&lst, new_ft);
        lstadd_back(&exp, new_ref);

        if (cmp_lists(lst, exp)) SUBTEST_OK();
        else SUBTEST_FAILF("diff: lists mismatch");

        free_list(lst);
        free_list(exp);
    }

    return group_finish();
}