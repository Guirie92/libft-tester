/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_itoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:01:05 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 16:43:07 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include "../../libft.h"

int group_itoa(void)
{
	group_start("itoa");

    /* subtest 1: zero */
    {
        int n = 0;
        char exp[64];
        snprintf(exp, sizeof(exp), "%d", n);
        char *got = ft_itoa(n);
        if (!got) { SUBTEST_FAILF("diff: expected=%s | got=(null)\nreturned NULL", exp); }
        else if (strcmp(exp, got) == 0) { SUBTEST_OK(); }
        else { SUBTEST_FAILF("diff: expected=%s | got=%s\nlen_expected=%zu len_got=%zu", exp, got, strlen(exp), strlen(got)); }
        free(got);
    }

    /* subtest 2: small positive */
    {
        int n = 42;
        char exp[64];
        snprintf(exp, sizeof(exp), "%d", n);
        char *got = ft_itoa(n);
        if (!got) { SUBTEST_FAILF("diff: expected=%s | got=(null)\nreturned NULL", exp); }
        else if (strcmp(exp, got) == 0) { SUBTEST_OK(); }
        else { SUBTEST_FAILF("diff: expected=%s | got=%s\nlen_expected=%zu len_got=%zu", exp, got, strlen(exp), strlen(got)); }
        free(got);
    }

    /* subtest 3: small negative */
    {
        int n = -42;
        char exp[64];
        snprintf(exp, sizeof(exp), "%d", n);
        char *got = ft_itoa(n);
        if (!got) { SUBTEST_FAILF("diff: expected=%s | got=(null)\nreturned NULL", exp); }
        else if (strcmp(exp, got) == 0) { SUBTEST_OK(); }
        else { SUBTEST_FAILF("diff: expected=%s | got=%s\nlen_expected=%zu len_got=%zu", exp, got, strlen(exp), strlen(got)); }
        free(got);
    }

    /* subtest 4: INT_MAX */
    {
        int n = INT_MAX; /* 2147483647 */
        char exp[64];
        snprintf(exp, sizeof(exp), "%d", n);
        char *got = ft_itoa(n);
        if (!got) { SUBTEST_FAILF("diff: expected=%s | got=(null)\nreturned NULL", exp); }
        else if (strcmp(exp, got) == 0) { SUBTEST_OK(); }
        else { SUBTEST_FAILF("diff: expected=%s | got=%s\nlen_expected=%zu len_got=%zu", exp, got, strlen(exp), strlen(got)); }
        free(got);
    }

    /* subtest 5: INT_MIN (classic edge case) */
    {
        int n = INT_MIN; /* -2147483648 */
        char exp[64];
        snprintf(exp, sizeof(exp), "%d", n);
        char *got = ft_itoa(n);
        if (!got) { SUBTEST_FAILF("diff: expected=%s | got=(null)\nreturned NULL", exp); }
        else if (strcmp(exp, got) == 0) { SUBTEST_OK(); }
        else { SUBTEST_FAILF("diff: expected=%s | got=%s\nlen_expected=%zu len_got=%zu", exp, got, strlen(exp), strlen(got)); }
        free(got);
    }

    /* subtest 6: several random-ish values (deterministic list) */
    {
        int cases[] = { 1, -1, 123456789, -123456789, 1000000000, -1000000000 };
        size_t ncases = sizeof(cases) / sizeof(cases[0]);
        for (size_t i = 0; i < ncases; ++i)
        {
            int v = cases[i];
            char exp[64];
            snprintf(exp, sizeof(exp), "%d", v);
            char *got = ft_itoa(v);
            if (!got) { SUBTEST_FAILF("diff: expected=%s | got=(null)\nreturned NULL (case index %zu)", exp, i); }
            else if (strcmp(exp, got) == 0) { SUBTEST_OK(); }
            else { SUBTEST_FAILF("diff: expected=%s | got=%s\nlen_expected=%zu len_got=%zu (case index %zu)", exp, got, strlen(exp), strlen(got), i); }
            free(got);
        }
    }

    /* subtest 7: repeated calls produce valid independent strings */
    {
        int a = 12345;
        int b = -67890;
        char exp_a[64], exp_b[64];
        snprintf(exp_a, sizeof(exp_a), "%d", a);
        snprintf(exp_b, sizeof(exp_b), "%d", b);
        char *ga = ft_itoa(a);
        char *gb = ft_itoa(b);
        if (!ga || !gb) {
            SUBTEST_FAILF("diff: expected=%s | got=(null)\none of the calls returned NULL", exp_a);
        } else if (strcmp(ga, exp_a) != 0) {
            SUBTEST_FAILF("diff: expected=%s | got=%s\nfirst call mismatch", exp_a, ga);
        } else if (strcmp(gb, exp_b) != 0) {
            SUBTEST_FAILF("diff: expected=%s | got=%s\nsecond call mismatch", exp_b, gb);
        } else if (ga == gb) { /* very unlikely but check independence */
            SUBTEST_FAILF("diff: expected different pointers | got same pointer (%p)", (void*)ga);
        } else {
            SUBTEST_OK();
        }
        free(ga);
        free(gb);
    }

    return group_finish();
}