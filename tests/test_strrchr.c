/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strrchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:33:59 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 20:47:42 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <string.h>
#include "../../libft.h"

int group_strrchr(void)
{
    group_start("strrchr");

    /* subtest 1: basic search */
    {
        const char *s = "hello world";
        int c = 'o';
        const char *exp = strrchr(s, c);
        const char *got = ft_strrchr(s, c);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", exp, got);
    }

    /* subtest 2: character not found */
    {
        const char *s = "hello";
        int c = 'x';
        const char *exp = strrchr(s, c);
        const char *got = ft_strrchr(s, c);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", exp, got);
    }

    /* subtest 3: empty string */
    {
        const char *s = "";
        int c = 'a';
        const char *exp = strrchr(s, c);
        const char *got = ft_strrchr(s, c);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", exp, got);
    }

    /* subtest 4: search for null terminator */
    {
        const char *s = "hello";
        int c = '\0';
        const char *exp = strrchr(s, c);
        const char *got = ft_strrchr(s, c);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%p' | got='%p'\n", (void*)exp, (void*)got);
    }

    /* subtest 5: last character match */
    {
        const char *s = "abcabc";
        int c = 'a';
        const char *exp = strrchr(s, c);
        const char *got = ft_strrchr(s, c);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", exp, got);
    }

    /* subtest 6: multibyte characters (search by byte) */
    {
        const char *s = "éå漢é";
        int c = (unsigned char)0xC3; // first byte of 'é'
        const char *exp = strrchr(s, c);
        const char *got = ft_strrchr(s, c);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", exp, got);
    }

	/* subtest 7: embedded null byte */
    {
        const char s[7] = {'a','b','\0','c','d','c','\0'};
        int c = 'c';
        const char *exp = strrchr(s, c);
        const char *got = ft_strrchr(s, c);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%p' | got='%p'\n", (void*)exp, (void*)got);
    }

	/* subtest 8: very long string */
    {
        char s[100000];
        for (size_t i = 0; i < 99999; i++) s[i] = 'x';
        s[99999] = '\0';
        int c = 'x';
        const char *exp = strrchr(s, c);
        const char *got = ft_strrchr(s, c);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%p' | got='%p'\n", (void*)exp, (void*)got);
    }

    return group_finish();
}
