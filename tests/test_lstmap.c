/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:04:13 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 20:26:13 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include "../../libft.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_list t_list;

static void del_int(void *content)
{
    if (content) free(content);
}

static void *dup_int(void *content)
{
    if (!content) return NULL;
    int *p = malloc(sizeof(int));
    if (!p) return NULL;
    *p = *(int *)content * 2; // example transform: double the value
    return p;
}

static void free_list(t_list *lst)
{
    while (lst)
    {
        t_list *tmp = lst->next;
        free(lst->content);
        free(lst);
        lst = tmp;
    }
}

int group_lstmap(void)
{
	group_start("lstmap");

    /* subtest 1: empty list */
    {
        t_list *res = ft_lstmap(NULL, dup_int, del_int);
        if (res == NULL) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=NULL | got=%p", (void *)res);
    }

    /* subtest 2: single element list */
    {
        int *val = malloc(sizeof(int)); *val = 5;
        t_list node = {val, NULL};
        t_list *res = ft_lstmap(&node, dup_int, del_int);

        if (res && *(int *)res->content == 10 && res->next == NULL) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=10 | got=%d", res ? *(int *)res->content : -1);

        free_list(res);
    }

    /* subtest 3: multiple elements list */
    {
        int *v1 = malloc(sizeof(int)); *v1 = 1;
        int *v2 = malloc(sizeof(int)); *v2 = 2;
        int *v3 = malloc(sizeof(int)); *v3 = 3;
        t_list n3 = {v3, NULL}, n2 = {v2, &n3}, n1 = {v1, &n2};

        t_list *res = ft_lstmap(&n1, dup_int, del_int);

        if (res &&
            res->next && res->next->next && res->next->next->next == NULL &&
            *(int *)res->content == 2 &&
            *(int *)res->next->content == 4 &&
            *(int *)res->next->next->content == 6)
            SUBTEST_OK();
        else
            SUBTEST_FAILF("diff: expected=2,4,6 | got=%d,%d,%d",
                          res ? *(int *)res->content : -1,
                          res && res->next ? *(int *)res->next->content : -1,
                          res && res->next && res->next->next ? *(int *)res->next->next->content : -1);

        free_list(res);
    }

    /* subtest 4: list with NULL content (f must handle NULL safely) */
    {
        t_list n2 = {NULL, NULL}, n1 = {NULL, &n2};
        t_list *res = ft_lstmap(&n1, dup_int, del_int);
        if (res && res->content == NULL && res->next && res->next->content == NULL)
            SUBTEST_OK();
        else
            SUBTEST_FAILF("diff: expected=NULL contents | got=%p,%p",
                          res ? res->content : NULL,
                          res && res->next ? res->next->content : NULL);

        free_list(res);
    }

    /* subtest 5: large list stress test (optional) */
    {
        #define LARGE 10000
        t_list *head = NULL, *prev = NULL;
        for (int i = 0; i < LARGE; i++)
        {
            int *p = malloc(sizeof(int));
            *p = i;
            t_list *node = malloc(sizeof(t_list));
            node->content = p;
            node->next = NULL;
            if (!head) head = node;
            if (prev) prev->next = node;
            prev = node;
        }

        t_list *res = ft_lstmap(head, dup_int, del_int);
        int ok = 1;
        t_list *orig = head, *mapped = res;
        while (orig && mapped)
        {
            if (*(int *)mapped->content != *(int *)orig->content * 2)
            {
                ok = 0;
                break;
            }
            orig = orig->next;
            mapped = mapped->next;
        }
        if (ok && orig == NULL && mapped == NULL) SUBTEST_OK();
        else SUBTEST_FAILF("diff: large list mapping failed");

        free_list(head);
        free_list(res);
    }

    return group_finish();
}
