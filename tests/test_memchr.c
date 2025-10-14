/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:37:45 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 22:22:38 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <string.h>
#include "../../libft.h"

size_t group_memchr(void)
{
    group_start("memchr");

    /* subtest 1: basic found */
    {
        const char src[] = "hello world";
        int c = 'o';
        const void *exp = memchr(src, c, strlen(src));
        const void *got = ft_memchr(src, c, strlen(src));
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p", exp, got);
    }

    /* subtest 2: not found -> should return NULL */
    {
        const char src[] = "abcd";
        int c = 'z';
        const void *exp = memchr(src, c, sizeof(src)-1);
        const void *got = ft_memchr(src, c, sizeof(src)-1);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p", exp, got);
    }

    /* subtest 3: search for '\\0' should find terminating zero if within n */
    {
        const char src[] = {'a','b','\0','c','d'};
        int c = '\0';
        const void *exp = memchr(src, c, 5);
        const void *got = ft_memchr(src, c, 5);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p", exp, got);
    }

    /* subtest 4: n == 0 must return NULL (do not inspect memory) */
    {
        const char src[] = "anything";
        int c = 'a';
        const void *exp = memchr(src, c, 0);
        const void *got = ft_memchr(src, c, 0);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p", exp, got);
    }

    /* subtest 5: byte values >= 128 (unsigned behavior) */
    {
        const unsigned char src[] = {0x80, 0x90, 0xFF, 0x00};
        int c = 0xFF;
        const void *exp = memchr(src, c, 4);
        const void *got = ft_memchr(src, c, 4);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p", exp, got);
    }

    /* subtest 6: non-aligned pointer search */
    {
        const char buf[] = "0123456789";
        const void *exp = memchr(buf + 1, '3', 5); /* searching in "12345" */
        const void *got = ft_memchr(buf + 1, '3', 5);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%p | got=%p", exp, got);
    }

    return group_finish();
}
