/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:03:53 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 20:23:38 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <stdlib.h>
#include <string.h>
#include "../../libft.h"

/* Tracker struct to check if del was called */
typedef struct s_del_tracker
{
    int called;
    void *last_content;
}   t_del_tracker;

static void tracker_del(void *content)
{
    t_del_tracker *tracker = content;
    tracker->called = 1;
    tracker->last_content = content;
}

static void dummy_del(void *content)
{
    free(content);
}

int group_lstclear(void)
{
	group_start("lstclear");

    /* subtest 1: NULL pointer to list */
    {
        t_list **lst = NULL;
        ft_lstclear(lst, dummy_del);
        SUBTEST_OK(); // Should not crash
    }

    /* subtest 2: empty list */
    {
        t_list *lst = NULL;
        ft_lstclear(&lst, dummy_del);
        if (lst == NULL) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=NULL | got=%p", (void*)lst);
    }

    /* subtest 3: single node with malloced content */
    {
        t_list *lst = malloc(sizeof(t_list));
        lst->content = malloc(6);
        strcpy(lst->content, "hello");
        lst->next = NULL;

        ft_lstclear(&lst, dummy_del);
        if (lst == NULL) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=NULL | got=%p", (void*)lst);
    }

    /* subtest 4: multiple nodes with tracker del */
    {
        t_list *n1 = malloc(sizeof(t_list));
        t_list *n2 = malloc(sizeof(t_list));
        t_del_tracker *t1 = malloc(sizeof(t_del_tracker));
        t_del_tracker *t2 = malloc(sizeof(t_del_tracker));
        t1->called = 0; t1->last_content = NULL;
        t2->called = 0; t2->last_content = NULL;

        n1->content = t1; n1->next = n2;
        n2->content = t2; n2->next = NULL;

        t_list *lst = n1;
        ft_lstclear(&lst, tracker_del);

        if (lst == NULL && t1->called && t2->called)
            SUBTEST_OK();
        else
            SUBTEST_FAILF(
                "diff: expected=NULL and both del called=1\n got lst=%p t1=%d t2=%d",
                (void*)lst, t1->called, t2->called
            );

        free(t1); // prevent leak
        free(t2);
    }

    /* subtest 5: node with NULL content */
    {
        t_list *lst = malloc(sizeof(t_list));
        lst->content = NULL;
        lst->next = NULL;

        ft_lstclear(&lst, dummy_del);
        if (lst == NULL) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=NULL | got=%p", (void*)lst);
    }

    /* subtest 6: large list stress test */
    {
        const int N = 1000;
        t_list *lst = NULL;
        t_list *prev = NULL;
        for (int i = 0; i < N; i++)
        {
            t_list *node = malloc(sizeof(t_list));
            node->content = malloc(10);
            memset(node->content, 'A' + (i % 26), 10);
            node->next = NULL;
            if (!lst) lst = node;
            if (prev) prev->next = node;
            prev = node;
        }

        ft_lstclear(&lst, dummy_del);
        if (lst == NULL) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=NULL | got=%p", (void*)lst);
    }

    /* subtest 7: struct content in nodes */
    {
        typedef struct s_point { int x, y; } t_point;
        t_list *lst = malloc(sizeof(t_list));
        t_point *pt = malloc(sizeof(t_point));
        pt->x = 10; pt->y = 20;
        lst->content = pt;
        lst->next = NULL;

        ft_lstclear(&lst, dummy_del);
        if (lst == NULL) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=NULL | got=%p", (void*)lst);
    }

    return group_finish();
}
