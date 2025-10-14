/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bzero.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:02:27 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 15:38:05 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <string.h>
#include "../../libft.h"

int group_bzero(void)
{
    group_start("bzero");

    /* subtest 1: basic zeroing */
    {
        char buf1[6] = "hello";
        char buf2[6] = "hello";
        bzero(buf1, 5);
        ft_bzero(buf2, 5);
        if (memcmp(buf1, buf2, 5) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", buf1, buf2);
    }

    /* subtest 2: zero-length should do nothing */
    {
        char buf1[5] = "abcd";
        char buf2[5] = "abcd";
        bzero(buf1, 0);
        ft_bzero(buf2, 0);
        if (memcmp(buf1, buf2, 4) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", buf1, buf2);
    }

    /* subtest 3: empty buffer */
    {
        char buf1[1] = {'X'};
        char buf2[1] = {'X'};
        bzero(buf1, 0);
        ft_bzero(buf2, 0);
        if (memcmp(buf1, buf2, 1) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%02X' | got='%02X'", (unsigned char)buf1[0], (unsigned char)buf2[0]);
    }

    /* subtest 4: very large buffer */
    {
        char buf1[100000];
        char buf2[100000];
        for (size_t i = 0; i < 100000; i++) { buf1[i] = (char)(i % 256); buf2[i] = (char)(i % 256); }
        bzero(buf1, 100000);
        ft_bzero(buf2, 100000);
        if (memcmp(buf1, buf2, 100000) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected first byte='%02X' | got='%02X'", (unsigned char)buf1[0], (unsigned char)buf2[0]);
    }

    /* subtest 5: non-aligned buffer */
    {
        char buf1[10] = "abcdefghi";
        char buf2[10] = "abcdefghi";
        bzero(buf1 + 1, 7);
        ft_bzero(buf2 + 1, 7);
        if (memcmp(buf1, buf2, 10) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", buf1, buf2);
    }

    /* subtest 6: single byte */
    {
        char buf1[1] = {'X'};
        char buf2[1] = {'X'};
        bzero(buf1, 1);
        ft_bzero(buf2, 1);
        if (memcmp(buf1, buf2, 1) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%02X' | got='%02X'", (unsigned char)buf1[0], (unsigned char)buf2[0]);
    }

    return group_finish();
}
