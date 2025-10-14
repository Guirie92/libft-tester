/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstdelone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:03:37 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 22:22:01 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <stdlib.h>
#include <string.h>
#include "../../libft.h"

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

size_t group_lstdelone(void)
{
	group_start("lstdelone");

    /* subtest 1: NULL list */
    {
        t_list *lst = NULL;
        ft_lstdelone(lst, dummy_del);
        SUBTEST_OK(); // should just return, no crash
    }

    /* subtest 2: normal single node with malloced content */
    {
        t_list *lst = malloc(sizeof(t_list));
        lst->content = malloc(6);
        strcpy(lst->content, "hello");
        lst->next = NULL;

        ft_lstdelone(lst, dummy_del);
        // if no crash, content freed, node freed
        SUBTEST_OK();
    }

    /* subtest 3: content NULL */
    {
        t_list *lst = malloc(sizeof(t_list));
        lst->content = NULL;
        lst->next = NULL;

        ft_lstdelone(lst, dummy_del);
        SUBTEST_OK();
    }

    /* subtest 4: track del function call */
    {
        t_del_tracker *tracker = malloc(sizeof(t_del_tracker));
        tracker->called = 0;
        tracker->last_content = NULL;

        t_list *lst = malloc(sizeof(t_list));
        lst->content = tracker;
        lst->next = NULL;

        ft_lstdelone(lst, tracker_del);

        if (tracker->called == 1 && tracker->last_content == tracker)
            SUBTEST_OK();
        else
            SUBTEST_FAILF("diff: expected del called=1 | got del called=%d", tracker->called);
        free(tracker); // avoid memory leak in test
    }

    /* subtest 5: large content (stress) */
    {
        t_list *lst = malloc(sizeof(t_list));
        char *large = malloc(100000);
        memset(large, 'A', 99999);
        large[99999] = '\0';
        lst->content = large;
        lst->next = NULL;

        ft_lstdelone(lst, dummy_del);
        SUBTEST_OK(); // if freed properly, no crash
    }

    /* subtest 6: struct content */
    {
        typedef struct s_point { int x, y; } t_point;
        t_point *pt = malloc(sizeof(t_point));
        pt->x = 42; pt->y = 24;

        t_list *lst = malloc(sizeof(t_list));
        lst->content = pt;
        lst->next = NULL;

        ft_lstdelone(lst, dummy_del);
        SUBTEST_OK();
    }

    return group_finish();
}
