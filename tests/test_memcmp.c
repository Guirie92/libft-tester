/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memcmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:40:18 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 20:28:54 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <string.h>
#include "../../libft.h"
#define SIGN_OK(e,g) (((e) == 0 && (g) == 0) || ((e) < 0 && (g) < 0) || ((e) > 0 && (g) > 0))

int group_memcmp(void)
{
    group_start("memcmp");

    /* helper macro: check sign agreement between expected and got */

    /* subtest 1: identical buffers -> zero */
    {
        const char a[] = "same buffer";
        const char b[] = "same buffer";
        int exp = memcmp(a, b, sizeof(a));
        int got = ft_memcmp(a, b, sizeof(a));
        if (SIGN_OK(exp, got)) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
    }

    /* subtest 2: differ at first byte */
    {
        const char a[] = "abc";
        const char b[] = "xbc";
        int exp = memcmp(a, b, 3);
        int got = ft_memcmp(a, b, 3);
        if (SIGN_OK(exp, got)) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
    }

    /* subtest 3: n == 0 should return 0 regardless of contents */
    {
        const char a[] = "hello";
        const char b[] = "world";
        int exp = memcmp(a, b, 0);
        int got = ft_memcmp(a, b, 0);
        if (SIGN_OK(exp, got)) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
    }

    /* subtest 4: embedded nulls (memcmp compares bytes) */
    {
        const char a[] = {'a','\0','x','y'};
        const char b[] = {'a','\0','x','z'};
        int exp = memcmp(a, b, 4);
        int got = ft_memcmp(a, b, 4);
        if (SIGN_OK(exp, got)) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
    }

    /* subtest 5: difference only after n (should be equal) */
    {
        const char a[] = "prefix-A";
        const char b[] = "prefix-B";
        size_t n = 7; /* "prefix-" identical */
        int exp = memcmp(a, b, n);
        int got = ft_memcmp(a, b, n);
        if (SIGN_OK(exp, got)) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
    }

    /* subtest 6: unsigned-byte comparison behavior (>=128) */
    {
        const unsigned char a[] = {0x7F, 0xFF};
        const unsigned char b[] = {0x7F, 0x7E};
        int exp = memcmp(a, b, 2);
        int got = ft_memcmp(a, b, 2);
        if (SIGN_OK(exp, got)) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
    }

    /* subtest 7: large buffer comparison */
    {
        const size_t N = 10000;
        unsigned char *a = (unsigned char *)malloc(N);
        unsigned char *b = (unsigned char *)malloc(N);
        if (!a || !b) {
            /* If allocation fails, mark test as skipped/fail depending on framework.
               We'll fail gracefully with message. */
            SUBTEST_FAILF("diff: allocation failed for large-buffer test");
        } else {
            for (size_t i = 0; i < N; ++i) { a[i] = (unsigned char)(i % 256); b[i] = a[i]; }
            /* make one byte different near the end */
            b[N-1] = (unsigned char)((a[N-1] + 1) & 0xFF);
            int exp = memcmp(a, b, N);
            int got = ft_memcmp(a, b, N);
            if (SIGN_OK(exp, got)) SUBTEST_OK();
            else SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
            free(a);
            free(b);
        }
    }

    return group_finish();
}
