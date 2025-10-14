/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:50:08 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 20:40:36 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <string.h>
#include "../../libft.h"

int group_memset(void)
{
    group_start("memset");

    /* subtest 1: basic fill */
    {
        char d1[6], d2[6];
        memset(d1, 'A', 5);
        ft_memset(d2, 'A', 5);
        d1[5] = '\0';
        d2[5] = '\0';
        if (memcmp(d1, d2, 6) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", d1, d2);
    }

    /* subtest 2: n == 0 should not modify */
    {
		char d1[5] = {'X','X','X','X','X'};
        char d2[5] = {'X','X','X','X','X'};
		size_t n = 0;
        memset(d1, 'A', n);
        ft_memset(d2, 'A', n);
        if (memcmp(d1, d2, 5) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", d1, d2);
    }

    /* subtest 3: fill entire buffer */
    {
        char d1[10], d2[10];
        memset(d1, 0xFF, sizeof(d1));
        ft_memset(d2, 0xFF, sizeof(d2));
        if (memcmp(d1, d2, sizeof(d1)) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected full 0xFF buffer | got different content");
    }

    /* subtest 4: very large buffer */
    {
        char d1[100000], d2[100000];
        memset(d1, 'x', 100000);
        ft_memset(d2, 'x', 100000);
        if (memcmp(d1, d2, 100000) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: large buffer mismatch");
    }

    /* subtest 5: single byte */
    {
        char d1[1] = {0}, d2[1] = {0};
        memset(d1, 'z', 1);
        ft_memset(d2, 'z', 1);
        if (memcmp(d1, d2, 1) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%c' | got='%c'", d1[0], d2[0]);
    }

    /* subtest 6: zero-length on garbage */
    {
        char d1[5] = {'a','b','c','d','e'};
        char d2[5] = {'a','b','c','d','e'};
		size_t n = 0;
        memset(d1, 'X', n);
        ft_memset(d2, 'X', n);
        if (memcmp(d1, d2, 5) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: zero-length on garbage mismatch");
    }

    /* subtest 7: partial fill */
    {
        char d1[10] = "abcdefghij";
        char d2[10] = "abcdefghij";
        memset(d1 + 3, '*', 4);
        ft_memset(d2 + 3, '*', 4);
        if (memcmp(d1, d2, 10) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", d1, d2);
    }

    /* subtest 8: non-char type buffer */
    {
        int d1[5], d2[5];
        memset(d1, 0, sizeof(d1));
        ft_memset(d2, 0, sizeof(d2));
        if (memcmp(d1, d2, sizeof(d1)) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: int array zeroing mismatch");
    }

    /* subtest 9: memset with non-ASCII value */
    {
        unsigned char d1[5], d2[5];
        memset(d1, 200, 5);
        ft_memset(d2, 200, 5);
        if (memcmp(d1, d2, 5) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected bytes 200 | got different content");
    }

    /* subtest 10: memset with overlapping memory (valid case) */
    {
        char d1[10] = "abcdefgh";
        char d2[10] = "abcdefgh";
        memset(d1 + 2, 'X', 5);
        ft_memset(d2 + 2, 'X', 5);
        if (memcmp(d1, d2, 10) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'\n(overlap fill)", d1, d2);
    }

    return group_finish();
}
