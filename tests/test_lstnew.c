/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:02:38 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 20:26:43 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include "../../libft.h"
#include <string.h>
#include <stdlib.h>

/* reference implementation */
static t_list *lstnew(void *content)
{
    t_list *new = malloc(sizeof(t_list));
    if (!new)
        return NULL;
    new->content = content;
    new->next = NULL;
    return new;
}

int group_lstnew(void)
{
	group_start("lstnew");

    /* subtest 1: basic string content */
    {
        char *s = "hello";
        t_list *exp = lstnew(s);
        t_list *got = ft_lstnew(s);

        if (exp && got && exp->content == got->content && got->next == NULL) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p\nexpected->next=%p | got->next=%p",
                           exp ? exp->content : NULL,
                           got ? got->content : NULL,
                           exp ? exp->next : NULL,
                           got ? got->next : NULL);

        free(exp);
        free(got);
    }
	
    /* subtest 2: NULL content */
    {
        t_list *exp = lstnew(NULL);
        t_list *got = ft_lstnew(NULL);

        if (exp && got && exp->content == got->content && got->next == NULL) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p\nexpected->next=%p | got->next=%p",
                           exp ? exp->content : NULL,
                           got ? got->content : NULL,
                           exp ? exp->next : NULL,
                           got ? got->next : NULL);

        free(exp);
        free(got);
    }

    /* subtest 3: integer pointer content */
    {
        int x = 42;
        t_list *exp = lstnew(&x);
        t_list *got = ft_lstnew(&x);

        if (exp && got && exp->content == got->content && got->next == NULL) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p\nexpected->next=%p | got->next=%p",
                           exp ? exp->content : NULL,
                           got ? got->content : NULL,
                           exp ? exp->next : NULL,
                           got ? got->next : NULL);

        free(exp);
        free(got);
    }

    /* subtest 4: struct content */
    {
        struct { int a; char b; } value = {1,'x'};
        t_list *exp = lstnew(&value);
        t_list *got = ft_lstnew(&value);

        if (exp && got && exp->content == got->content && got->next == NULL) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p\nexpected->next=%p | got->next=%p",
                           exp ? exp->content : NULL,
                           got ? got->content : NULL,
                           exp ? exp->next : NULL,
                           got ? got->next : NULL);

        free(exp);
        free(got);
    }

	/* subtest 5: stress test with many nodes */
    {
        const size_t N = 10000;
        t_list **exp_nodes = malloc(sizeof(t_list*) * N);
        t_list **got_nodes = malloc(sizeof(t_list*) * N);
        int dummy_data[N];
        int failed = 0;

        for (size_t i = 0; i < N; i++)
        {
            dummy_data[i] = (int)i;
            exp_nodes[i] = lstnew(&dummy_data[i]);
            got_nodes[i] = ft_lstnew(&dummy_data[i]);

            if (!exp_nodes[i] || !got_nodes[i] ||
                exp_nodes[i]->content != got_nodes[i]->content ||
                got_nodes[i]->next != NULL)
            {
                failed = 1;
                break;
            }
        }

        if (!failed) SUBTEST_OK();
        else SUBTEST_FAILF("stress test failed at some node\n");

        for (size_t i = 0; i < N; i++)
        {
            free(exp_nodes[i]);
            free(got_nodes[i]);
        }
        free(exp_nodes);
        free(got_nodes);
    }

    return group_finish();
}