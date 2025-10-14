/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:58:28 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 16:16:33 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "../../libft.h"

int group_atoi(void)
{

	group_start("atoi");

    /* subtest 1: basic positive */
    {
        const char *s = "42";
        int exp = atoi(s);
        int got = ft_atoi(s);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
    }

    /* subtest 2: leading whitespace and negative */
    {
        const char *s = "   -42";
        int exp = atoi(s);
        int got = ft_atoi(s);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
    }

    /* subtest 3: plus sign */
    {
        const char *s = "+123";
        int exp = atoi(s);
        int got = ft_atoi(s);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
    }

    /* subtest 4: non-digit at start and trailing chars */
    {
        const char *s1 = "words123";
        const char *s2 = "123words";
        int exp1 = atoi(s1);
        int got1 = ft_atoi(s1);
        int exp2 = atoi(s2);
        int got2 = ft_atoi(s2);
        if (exp1 == got1 && exp2 == got2) SUBTEST_OK();
        else
        {
            if (exp1 != got1) SUBTEST_FAILF("diff: expected=%d | got=%d\nfor input='%s'", exp1, got1, s1);
            else SUBTEST_FAILF("diff: expected=%d | got=%d\nfor input='%s'", exp2, got2, s2);
        }
    }

    /* subtest 5: only sign (no digits) */
    {
        const char *s1 = "-";
        const char *s2 = "+";
        int exp1 = atoi(s1);
        int got1 = ft_atoi(s1);
        int exp2 = atoi(s2);
        int got2 = ft_atoi(s2);
        if (exp1 == got1 && exp2 == got2) SUBTEST_OK();
        else
        {
            if (exp1 != got1) SUBTEST_FAILF("diff: expected=%d | got=%d\nfor input='%s'", exp1, got1, s1);
            else SUBTEST_FAILF("diff: expected=%d | got=%d\nfor input='%s'", exp2, got2, s2);
        }
    }

    /* subtest 6: leading zeros and embedded non-digits */
    {
        const char *s = "0000123abc";
        int exp = atoi(s);
        int got = ft_atoi(s);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
    }

    /* subtest 7: empty string */
    {
        const char *s = "";
        int exp = atoi(s);
        int got = ft_atoi(s);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%d | got=%d", exp, got);
    }

    /* subtest 8: whitespace variety */
    {
        const char *s = "\t\n\v\f\r  -0012abc34";
        int exp = atoi(s);
        int got = ft_atoi(s);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%d | got=%d\n(input contains assorted whitespace)", exp, got);
    }

    /* subtest 9: INT_MAX and INT_MIN */
    {
        char smax[32], smin[32];
        snprintf(smax, sizeof(smax), "%d", INT_MAX);
        snprintf(smin, sizeof(smin), "%d", INT_MIN);
        int exp1 = atoi(smax);
        int got1 = ft_atoi(smax);
        int exp2 = atoi(smin);
        int got2 = ft_atoi(smin);
        if (exp1 == got1 && exp2 == got2) SUBTEST_OK();
        else
        {
            if (exp1 != got1) SUBTEST_FAILF("diff: expected=%d | got=%d\nfor input='%s'", exp1, got1, smax);
            else SUBTEST_FAILF("diff: expected=%d | got=%d\nfor input='%s'", exp2, got2, smin);
        }
    }
	
	/* subtest 10: overflow-ish values (implementation-defined behavior may differ) */
    {
        /* these may produce implementation-defined results in standard C; we still compare against libc atoi */
        const char *s1 = "2147483648";   /* INT_MAX + 1 */
        const char *s2 = "-2147483649";  /* INT_MIN - 1 */
        int exp1 = atoi(s1);
        int got1 = ft_atoi(s1);
        int exp2 = atoi(s2);
        int got2 = ft_atoi(s2);
        if (exp1 == got1 && exp2 == got2) SUBTEST_OK();
        else
        {
            if (exp1 != got1) SUBTEST_FAILF("diff: expected=%d | got=%d\n(input='%s')\nNote: overflow behavior may be implementation-defined.", exp1, got1, s1);
            else SUBTEST_FAILF("diff: expected=%d | got=%d\n(input='%s')\nNote: overflow behavior may be implementation-defined.", exp2, got2, s2);
        }
    }

    return group_finish();
}
