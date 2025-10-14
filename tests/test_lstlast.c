/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstlast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:03:14 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 22:22:10 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../libft.h"
#include <string.h>

/* reference implementation */
static t_list *lstlast(t_list *lst)
{
    if (!lst)
        return (NULL);
    while (lst->next)
        lst = lst->next;
    return (lst);
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

/* Build list with n nodes, content values 0..n-1 (allocated integers) */
static t_list *build_simple_list(size_t n)
{
    t_list *head = NULL;
    for (size_t i = 0; i < n; ++i)
    {
        int *v = malloc(sizeof(int));
        if (!v) { free_list(head); return NULL; }
        *v = (int)i;
        t_list *node = mk_node(v);
        if (!node) { free(v); free_list(head); return NULL; }
        append_node(&head, node);
    }
    return head;
}

static void free_simple_list_and_contents(t_list *lst)
{
    while (lst)
    {
        t_list *next = lst->next;
        free(lst->content);
        free(lst);
        lst = next;
    }
}

size_t group_lstlast(void)
{
	group_start("lstlast");

    /* subtest 1: NULL list -> should return NULL */
    {
        t_list *lst = NULL;
        t_list *exp = lstlast(lst);
        t_list *got = ft_lstlast(lst);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p", (void*)exp, (void*)got);
    }

    /* subtest 2: single element list -> return that node pointer */
    {
        int *v = malloc(sizeof(int));
        *v = 42;
        t_list *node = mk_node(v);
        t_list *exp = lstlast(node);
        t_list *got = ft_lstlast(node);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p\n(expected->content=%d, got->content=%d)",
                          (void*)exp, (void*)got,
                          exp ? *((int*)exp->content) : -1,
                          got ? *((int*)got->content) : -1);
        free(v);
        free(node);
    }

    /* subtest 3: multiple nodes -> last node pointer must be returned */
    {
        t_list *lst = NULL;
        int *a = malloc(sizeof(int)); *a = 1;
        int *b = malloc(sizeof(int)); *b = 2;
        int *c = malloc(sizeof(int)); *c = 3;
        append_node(&lst, mk_node(a));
        append_node(&lst, mk_node(b));
        append_node(&lst, mk_node(c));
        t_list *exp = lstlast(lst);
        t_list *got = ft_lstlast(lst);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p\n(expected->content=%d, got->content=%d)",
                          (void*)exp, (void*)got,
                          exp ? *((int*)exp->content) : -1,
                          got ? *((int*)got->content) : -1);
        free_simple_list_and_contents(lst);
    }

    /* subtest 4: last node has NULL content (ensure pointer equality, not value) */
    {
        t_list *lst = NULL;
        append_node(&lst, mk_node(strdup("first")));
        append_node(&lst, mk_node(NULL)); /* last with NULL content */
        t_list *exp = lstlast(lst);
        t_list *got = ft_lstlast(lst);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p\n(expected content=%p, got content=%p)",
                          (void*)exp, (void*)got, exp ? exp->content : NULL, got ? got->content : NULL);
        /* free */
        free((char*)lst->content);
        free(lst->next); /* node with NULL content */
        free(lst);
    }

    /* subtest 5: long list (stress / performance) - 1000 nodes */
    {
        const size_t N = 1000;
        t_list *lst = build_simple_list(N);
        if (!lst) { SUBTEST_FAILF("setup-failed"); }
        else
        {
            t_list *exp = lstlast(lst);
            t_list *got = ft_lstlast(lst);
            if (exp == got) SUBTEST_OK();
            else SUBTEST_FAILF("diff: expected=%p | got=%p\n(index expected=%d, index got=%d)",
                              (void*)exp, (void*)got,
                              exp ? *((int*)exp->content) : -1,
                              got ? *((int*)got->content) : -1);
            free_simple_list_and_contents(lst);
        }
    }

    /* subtest 6: list where nodes' content pointers point to the same buffer (shared content) */
    {
        char *shared = strdup("shared buffer");
        t_list *lst = NULL;
        append_node(&lst, mk_node(shared));
        append_node(&lst, mk_node(shared));
        /* last node pointer must be the second node (not simply pointer-equality of content) */
        t_list *exp = lstlast(lst);
        t_list *got = ft_lstlast(lst);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p\n(expected content ptr=%p, got content ptr=%p)",
                          (void*)exp, (void*)got, exp ? exp->content : NULL, got ? got->content : NULL);
        free(shared);
        free(lst->next);
        free(lst);
    }

    return group_finish();
}
