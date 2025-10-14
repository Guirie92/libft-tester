/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memmove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:12:36 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 22:22:45 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <string.h>
#include "../../libft.h"

size_t group_memmove(void)
{
    group_start("memmove");

    /* subtest 1: basic copy */
    {
        char src[] = "abcdef";
        char d1[10] = {0}, d2[10] = {0};
        memmove(d1, src, 6);
        ft_memmove(d2, src, 6);
        if (memcmp(d1, d2, 6) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", d1, d2);
    }

    /* subtest 2: n == 0 should not touch destination */
    {
        char src[] = "abc";
        char d1[4] = {'X','X','X','\0'}, d2[4] = {'X','X','X','\0'};
        memmove(d1, src, 0);
        ft_memmove(d2, src, 0);
        if (memcmp(d1, d2, 4) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", d1, d2);
    }

    /* subtest 3: overlapping memory (dst < src) */
    {
        char buf1[10] = "123456789";
        char buf2[10] = "123456789";
        memmove(buf1, buf1 + 2, 5);   // safe for memmove
        ft_memmove(buf2, buf2 + 2, 5);
        if (memcmp(buf1, buf2, 10) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'\n(overlap dst<src)", buf1, buf2);
    }

    /* subtest 4: overlapping memory (dst > src) */
    {
        char buf1[10] = "abcdefghi";
        char buf2[10] = "abcdefghi";
        memmove(buf1 + 2, buf1, 5);
        ft_memmove(buf2 + 2, buf2, 5);
        if (memcmp(buf1, buf2, 10) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'\n(overlap dst>src)", buf1, buf2);
    }

    /* subtest 5: very large copy */
    {
        char src[100000];
        char d1[100000], d2[100000];
        for (size_t i = 0; i < 100000; i++) src[i] = (char)(i % 256);
        memmove(d1, src, 100000);
        ft_memmove(d2, src, 100000);
        if (memcmp(d1, d2, 100000) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: large copy mismatch");
    }

    /* subtest 6: integers */
    {
        int src[5] = {1,2,3,4,5};
        int d1[5], d2[5];
        memmove(d1, src, sizeof(src));
        ft_memmove(d2, src, sizeof(src));
        if (memcmp(d1, d2, sizeof(src)) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: int array copy mismatch");
    }

    /* subtest 7: struct copy */
    {
        struct { int x; char y; } src[2] = {{1,'a'}, {2,'b'}};
        struct { int x; char y; } d1[2], d2[2];
        memmove(d1, src, sizeof(src));
        ft_memmove(d2, src, sizeof(src));
        if (memcmp(d1, d2, sizeof(src)) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: struct array copy mismatch");
    }

    /* subtest 8: non-aligned pointers */
    {
        char buffer[10] = "abcdefghi";
        char d1[10], d2[10];
        memmove(d1, buffer + 1, 7);
        ft_memmove(d2, buffer + 1, 7);
        if (memcmp(d1, d2, 7) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: non-aligned copy mismatch");
    }

    /* subtest 9: copy one byte */
    {
        char d1[2] = {0}, d2[2] = {0};
        char src[] = "x";
        memmove(d1, src, 1);
        ft_memmove(d2, src, 1);
        if (memcmp(d1, d2, 1) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: 1-byte copy mismatch");
    }

    return group_finish();
}
