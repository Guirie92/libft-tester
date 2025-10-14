/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_calloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:58:39 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 20:16:15 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "../../libft.h"

int group_calloc(void)
{
	group_start("calloc");

    /* subtest 1: basic zeroed bytes (10 bytes) */
    {
        size_t nmemb = 10, size = 1;
        void *exp = calloc(nmemb, size);
        void *got = ft_calloc(nmemb, size);
        if (!exp && !got)
        {
            /* both returned NULL (rare) */
            SUBTEST_OK();
        }
        else if (exp && got)
        {
            if (memcmp(exp, got, nmemb * size) == 0) SUBTEST_OK();
            else SUBTEST_FAILF("diff: expected byte=%d | got byte=%d",
                              ((unsigned char*)exp)[0], ((unsigned char*)got)[0]);
        }
        else
        {
            /* one NULL and the other not -> mismatch */
            SUBTEST_FAILF("diff: expected=%p | got=%p", exp, got);
        }
        free(exp);
        free(got);
    }

    /* subtest 2: calloc for ints (nmemb * sizeof(int)) */
    {
        size_t nmemb = 5, size = sizeof(int);
        int *a = calloc(nmemb, size);
        int *b = ft_calloc(nmemb, size);
        if (!a && !b) SUBTEST_OK();
        else if (a && b)
        {
            if (memcmp(a, b, nmemb * size) == 0) SUBTEST_OK();
            else
            {
                /* find first differing byte for clearer message */
                size_t i;
                unsigned char *ua = (unsigned char*)a;
                unsigned char *ub = (unsigned char*)b;
                for (i = 0; i < nmemb * size; ++i) if (ua[i] != ub[i]) break;
                SUBTEST_FAILF("diff: expected byte=%u | got byte=%u\nfirst diff at idx=%zu",
                              (unsigned)ua[i], (unsigned)ub[i], i);
            }
        }
        else SUBTEST_FAILF("diff: expected=%p | got=%p", a, b);
        free(a);
        free(b);
    }

    /* subtest 3: large allocation (100000 bytes) */
    {
        size_t nmemb = 100000, size = 1;
        void *a = calloc(nmemb, size);
        void *b = ft_calloc(nmemb, size);
        if (!a && !b) SUBTEST_OK();
        else if (a && b)
        {
            if (memcmp(a, b, nmemb * size) == 0) SUBTEST_OK();
            else SUBTEST_FAILF("diff: expected byte=%d | got=%d",
                              ((unsigned char*)a)[0], ((unsigned char*)b)[0]);
        }
        else SUBTEST_FAILF("diff: expected=%p | got=%p", a, b);
        free(a);
        free(b);
    }

    /* subtest 4: nmemb == 0 or size == 0 (implementation-defined; we require same behavior as libc) */
    {
        void *a = calloc(0, 10);
        void *b = ft_calloc(0, 10);
        if (!a && !b)
        {
            SUBTEST_OK();
        }
        else if (a && b)
        {
            /* both non-NULL: consider OK (we don't assume how many bytes are usable) */
            SUBTEST_OK();
        }
        else
        {
            SUBTEST_FAILF("diff: expected=%p | got=%p (one returned NULL, the other didn't)", a, b);
        }
        free(a);
        free(b);
    }

    /* subtest 5: calloc with nmemb*size producing small non-zero pattern check */
    {
        size_t nmemb = 3, size = 3;
        unsigned char *a = calloc(nmemb, size);
        unsigned char *b = ft_calloc(nmemb, size);
        if (!a && !b) { SUBTEST_OK(); }
        else if (a && b)
        {
            /* verify all bytes are zero (explicit check) */
            size_t i, total = nmemb * size;
            int ok = 1;
            for (i = 0; i < total; ++i)
            {
                if (a[i] != 0 || b[i] != 0) { ok = 0; break; }
            }
            if (ok) SUBTEST_OK();
            else SUBTEST_FAILF("diff: expected byte=%u | got byte=%u at idx=%zu", (unsigned)a[i], (unsigned)b[i], i);
        }
        else SUBTEST_FAILF("diff: expected=%p | got=%p", a, b);
        free(a);
        free(b);
    }

    return group_finish();
}
