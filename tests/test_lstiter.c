/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstiter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:04:04 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 22:22:05 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include "../../libft.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_list t_list;

/* reference lstiter to compare against */
static void lstiter(t_list *lst, void (*f)(void *))
{
    while (lst)
    {
        f(lst->content);
        lst = lst->next;
    }
}

static void increment_int(void *content)
{
    if (!content) return;
    int *p = (int *)content;
    (*p)++;
}

static void uppercase(void *content)
{
    if (!content) return;
    char *s = (char *)content;
    for (size_t i = 0; s[i]; i++)
        if (s[i] >= 'a' && s[i] <= 'z') s[i] -= 32;
}

static int compare_int_lists(t_list *l1, t_list *l2)
{
    while (l1 && l2)
    {
        if (*(int *)l1->content != *(int *)l2->content)
            return 0;
        l1 = l1->next;
        l2 = l2->next;
    }
    return l1 == NULL && l2 == NULL;
}

static void free_str_list(t_list *lst)
{
    while (lst)
    {
        free(lst->content);
        lst = lst->next;
    }
}

size_t group_lstiter(void)
{
	group_start("lstiter");

    /* subtest 1: empty list */
    {
        t_list *lst1 = NULL;
        t_list *lst2 = NULL;
        ft_lstiter(lst1, increment_int);
        lstiter(lst2, increment_int);
        SUBTEST_OK(); // empty list should not crash
    }

    /* subtest 2: single element int list */
    {
        int a1 = 1, a2 = 1;
        t_list l1 = {&a1, NULL};
        t_list l2 = {&a2, NULL};
        ft_lstiter(&l1, increment_int);
        lstiter(&l2, increment_int);
        if (a1 == a2) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%d | got=%d", a2, a1);
    }

    /* subtest 3: multiple elements int list */
    {
        int v1[] = {1,2,3}, v2[] = {1,2,3};
        t_list n3 = {&v1[2], NULL}, n2 = {&v1[1], &n3}, n1 = {&v1[0], &n2};
        t_list m3 = {&v2[2], NULL}, m2 = {&v2[1], &m3}, m1 = {&v2[0], &m2};
        ft_lstiter(&n1, increment_int);
        lstiter(&m1, increment_int);
        if (compare_int_lists(&n1, &m1)) SUBTEST_OK();
        else SUBTEST_FAILF("diff: list values differ after increment");
    }

    /* subtest 4: list with NULL content */
    {
        t_list n2 = {NULL, NULL}, n1 = {NULL, &n2};
        t_list m2 = {NULL, NULL}, m1 = {NULL, &m2};
        ft_lstiter(&n1, increment_int);
        lstiter(&m1, increment_int);
        SUBTEST_OK(); // should not crash
    }

    /* subtest 5: list of strings with in-place modification */
    {
        char *s1 = strdup("abc"), *s2 = strdup("def"), *s3 = strdup("ghi");
        char *t1 = strdup("abc"), *t2 = strdup("def"), *t3 = strdup("ghi");
        t_list n3 = {s3, NULL}, n2 = {s2, &n3}, n1 = {s1, &n2};
        t_list m3 = {t3, NULL}, m2 = {t2, &m3}, m1 = {t1, &m2};

        ft_lstiter(&n1, uppercase);
        lstiter(&m1, uppercase);

        if (strcmp((char *)n1.content, (char *)m1.content) == 0 &&
            strcmp((char *)n2.content, (char *)m2.content) == 0 &&
            strcmp((char *)n3.content, (char *)m3.content) == 0)
            SUBTEST_OK();
        else
            SUBTEST_FAILF("diff: expected=%s,%s,%s | got=%s,%s,%s",
                          (char *)m1.content, (char *)m2.content, (char *)m3.content,
                          (char *)n1.content, (char *)n2.content, (char *)n3.content);

        free_str_list(&n1);
        free_str_list(&m1);
    }

    return group_finish();
}
