/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strncmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:31:00 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 22:23:52 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <string.h>
#include "../../libft.h"

size_t group_strncmp(void)
{
    group_start("strncmp");

    /* subtest 1: basic equal */
    {
        const char *s1 = "hello";
        const char *s2 = "hello";
        int exp = strncmp(s1, s2, 6);
        int got = ft_strncmp(s1, s2, 6);
        if ((exp == 0 && got == 0) || (exp < 0 && got < 0) || (exp > 0 && got > 0))
            SUBTEST_OK();
        else
            SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
    }

    /* subtest 2: differ at first char */
    {
        const char *s1 = "abc";
        const char *s2 = "xbc";
        int exp = strncmp(s1, s2, 3);
        int got = ft_strncmp(s1, s2, 3);
        if ((exp == 0 && got == 0) || (exp < 0 && got < 0) || (exp > 0 && got > 0))
            SUBTEST_OK();
        else
            SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
    }

    /* subtest 3: n == 0 should always return 0 */
    {
        const char *s1 = "abc";
        const char *s2 = "zzz";
        int exp = strncmp(s1, s2, 0);
        int got = ft_strncmp(s1, s2, 0);
        if ((exp == 0 && got == 0) || (exp < 0 && got < 0) || (exp > 0 && got > 0))
            SUBTEST_OK();
        else
            SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
    }

    /* subtest 4: difference occurs after n (should be equal) */
    {
        const char *s1 = "same-prefix-AX";
        const char *s2 = "same-prefix-BY";
        size_t n = 12; /* first 12 chars equal ("same-prefix-") */
        int exp = strncmp(s1, s2, n);
        int got = ft_strncmp(s1, s2, n);
        if ((exp == 0 && got == 0) || (exp < 0 && got < 0) || (exp > 0 && got > 0))
            SUBTEST_OK();
        else
            SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
    }

    /* subtest 5: embedded null in one string */
    {
        const char s1[6] = {'a', 'b', '\0', 'x', 'y', '\0'};
        const char s2[6] = {'a', 'b', '\0', 'z', 'z', '\0'};
        int exp = strncmp(s1, s2, 6);
        int got = ft_strncmp(s1, s2, 6);
        if ((exp == 0 && got == 0) || (exp < 0 && got < 0) || (exp > 0 && got > 0))
            SUBTEST_OK();
        else
            SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
    }

    /* subtest 6: n larger than both strings (compare full strings) */
    {
        const char *s1 = "short";
        const char *s2 = "shorter";
        int exp = strncmp(s1, s2, 100);
        int got = ft_strncmp(s1, s2, 100);
        if ((exp == 0 && got == 0) || (exp < 0 && got < 0) || (exp > 0 && got > 0))
            SUBTEST_OK();
        else
            SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
    }

    /* subtest 7: multibyte/UTF-8 bytes (strncmp compares bytes) */
    {
        const char *s1 = "éå漢"; /* multi-byte UTF-8 bytes */
        const char *s2 = "éå鳥";
        size_t n = strlen("éå"); /* ensure we test both equal prefix and differing tail */
        int exp_prefix = strncmp(s1, s2, n);
        int got_prefix = ft_strncmp(s1, s2, n);
        if ((exp_prefix == 0 && got_prefix == 0) || (exp_prefix < 0 && got_prefix < 0) || (exp_prefix > 0 && got_prefix > 0))
        {
            /* now compare enough bytes to include the differing UTF-8 characters */
            size_t n2 = 10;
            int exp2 = strncmp(s1, s2, n2);
            int got2 = ft_strncmp(s1, s2, n2);
            if ((exp2 == 0 && got2 == 0) || (exp2 < 0 && got2 < 0) || (exp2 > 0 && got2 > 0))
                SUBTEST_OK();
            else
                SUBTEST_FAILF("diff: expected=%d | got=%d", exp2, got2);
        }
        else
            SUBTEST_FAILF("diff: expected=%d | got=%d", exp_prefix, got_prefix);
    }

    /* subtest 8: unsigned-byte comparison (values >= 128) */
    {
        /* bytes: 0xFF (255) vs 0x7F (127) */
        const char s1[] = "\xff";
        const char s2[] = "\x7f";
        int exp = strncmp(s1, s2, 1);
        int got = ft_strncmp(s1, s2, 1);
        /* strncmp does unsigned char conversion before subtracting; check sign agreement */
        if ((exp == 0 && got == 0) || (exp < 0 && got < 0) || (exp > 0 && got > 0))
            SUBTEST_OK();
        else
            SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
    }

    /* subtest 9: case sensitivity */
    {
        const char *s1 = "Apple";
        const char *s2 = "apple";
        int exp = strncmp(s1, s2, 1); /* 'A' vs 'a' differs on first byte */
        int got = ft_strncmp(s1, s2, 1);
        if ((exp == 0 && got == 0) || (exp < 0 && got < 0) || (exp > 0 && got > 0))
            SUBTEST_OK();
        else
            SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
    }

    return group_finish();
}
