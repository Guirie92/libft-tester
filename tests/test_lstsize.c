/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstsize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:03:04 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 22:22:30 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <stdio.h>
#include "../../libft.h"

/* reference implementation */
static int lstsize(t_list *lst)
{
    size_t size;

    if (!lst)
        return 0;
    size = 1;
    while (lst->next)
    {
        size++;
        lst = lst->next;
    }
    return (int)size;
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

size_t group_lstsize(void)
{
	group_start("lstsize");

    /* subtest 1: NULL list -> size 0 */
    {
        t_list *lst = NULL;
        int exp = lstsize(lst);
        int got = ft_lstsize(lst);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
    }

    /* subtest 2: single element -> size 1 */
    {
        int x = 42;
        t_list *lst = mk_node(&x);
        int exp = lstsize(lst);
        int got = ft_lstsize(lst);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
        free(lst);
    }

    /* subtest 3: multiple elements -> size should match number of nodes */
    {
        t_list *lst = NULL;
        for (int i = 0; i < 5; i++)
        {
            int *v = malloc(sizeof(int));
            *v = i;
            append_node(&lst, mk_node(v));
        }
        int exp = lstsize(lst);
        int got = ft_lstsize(lst);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
        /* free */
        while (lst)
        {
            t_list *next = lst->next;
            free(lst->content);
            free(lst);
            lst = next;
        }
    }

    /* subtest 4: long list -> stress test (1000 nodes) */
    {
        t_list *lst = NULL;
        const int N = 1000;
        for (int i = 0; i < N; i++)
            append_node(&lst, mk_node(NULL));
        int exp = lstsize(lst);
        int got = ft_lstsize(lst);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
        free_list(lst);
    }

    /* subtest 5: nodes with shared content pointers (size depends only on nodes) */
    {
        char *shared = "shared";
        t_list *lst = mk_node(shared);
        append_node(&lst, mk_node(shared));
        append_node(&lst, mk_node(shared));
        int exp = lstsize(lst);
        int got = ft_lstsize(lst);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
        free_list(lst);
    }

    return group_finish();
}