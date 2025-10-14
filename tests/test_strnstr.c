/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strnstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:53:23 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 20:47:37 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <bsd/string.h>
#include "../../libft.h"

int group_strnstr(void)
{
    group_start("strnstr");

    /* subtest 1: basic found in middle */
    {
        const char *hay = "this is a haystack";
        const char *need = "hay";
        const void *exp = strnstr(hay, need, strlen(hay));
        const void *got = ft_strnstr(hay, need, strlen(hay));
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p", exp, got);
    }

    /* subtest 2: not found within n */
    {
        const char *hay = "abcdefg";
        const char *need = "def";
        size_t n = 3; /* only "abc" searched */
        const void *exp = strnstr(hay, need, n);
        const void *got = ft_strnstr(hay, need, n);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p\n(note: n=%zu)", exp, got, n);
    }

    /* subtest 3: empty needle -> return haystack (even if n == 0) */
    {
        const char *hay = "whatever";
        const char *need = "";
        const void *exp = strnstr(hay, need, 0);
        const void *got = ft_strnstr(hay, need, 0);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p", exp, got);
    }

    /* subtest 4: needle longer than haystack (should not be found) */
    {
        const char *hay = "short";
        const char *need = "shorterneedle";
        const void *exp = strnstr(hay, need, 100);
        const void *got = ft_strnstr(hay, need, 100);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p", exp, got);
    }

    /* subtest 5: needle at the very end but n excludes the match */
    {
        const char *hay = "findme_at_end";
        const char *need = "end";
        size_t n = strlen(hay) - 1; /* leave off final 'd' so "end" doesn't fully fit */
        const void *exp = strnstr(hay, need, n);
        const void *got = ft_strnstr(hay, need, n);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p\n(note: n=%zu)", exp, got, n);
    }

    /* subtest 6: haystack empty */
    {
        const char *hay = "";
        const char *need = "a";
        const void *exp = strnstr(hay, need, 1);
        const void *got = ft_strnstr(hay, need, 1);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p", exp, got);
    }

    /* subtest 7: embedded '\\0' in haystack (should not match past the '\\0') */
    {
        const char hay[8] = {'a', 'b', '\0', 'c', 'd', 'e', 'f', '\0'};
        const char *need = "cde";
        const void *exp = strnstr(hay, need, 8);
        const void *got = ft_strnstr(hay, need, 8);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p", exp, got);
    }

    /* subtest 8: multibyte UTF-8 bytes (byte-wise search) */
    {
        const char *hay = "préfix漢tail";
        const char *need = "漢";
        /* search enough bytes to include the multibyte character */
        size_t n = strlen(hay);
        const void *exp = strnstr(hay, need, n);
        const void *got = ft_strnstr(hay, need, n);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p", exp, got);
    }

    return group_finish();
}
