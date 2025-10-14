/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strlcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:18:06 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 20:46:30 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <bsd/string.h>
#include "../../libft.h"

int group_strlcat(void)
{
    group_start("strlcat");

    /* subtest 1: basic concatenation */
    {
        char dst1[10] = "hi", dst2[10] = "hi";
        const char *src = " there";
        size_t exp = strlcat(dst1, src, sizeof(dst1));
        size_t got = ft_strlcat(dst2, src, sizeof(dst2));
        if (exp == got && memcmp(dst1, dst2, sizeof(dst1)) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%zu | got=%zu\nexpected dst='%s' | got dst='%s'", exp, got, dst1, dst2);
    }

    /* subtest 2: zero-size destination */
    {
        char dst1[5] = "X", dst2[5] = "X";
        const char *src = "abc";
        size_t exp = strlcat(dst1, src, 0);
        size_t got = ft_strlcat(dst2, src, 0);
        if (exp == got && memcmp(dst1, dst2, 1) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%zu | got=%zu\nexpected dst='%s' | got dst='%s'", exp, got, dst1, dst2);
    }

    /* subtest 3: exact fit */
    {
        char dst1[6] = "hi", dst2[6] = "hi";
        const char *src = "abc";
        size_t exp = strlcat(dst1, src, sizeof(dst1));
        size_t got = ft_strlcat(dst2, src, sizeof(dst2));
        if (exp == got && memcmp(dst1, dst2, sizeof(dst1)) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%zu | got=%zu\nexpected dst='%s' | got dst='%s'", exp, got, dst1, dst2);
    }

    /* subtest 4: source longer than remaining space */
    {
        char dst1[6] = "hi", dst2[6] = "hi";
        const char *src = " there world";
        size_t exp = strlcat(dst1, src, sizeof(dst1));
        size_t got = ft_strlcat(dst2, src, sizeof(dst2));
        if (exp == got && memcmp(dst1, dst2, sizeof(dst1)) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%zu | got=%zu\nexpected dst='%s' | got dst='%s'", exp, got, dst1, dst2);
    }

    /* subtest 5: empty source */
    {
        char dst1[5] = "hi", dst2[5] = "hi";
        const char *src = "";
        size_t exp = strlcat(dst1, src, sizeof(dst1));
        size_t got = ft_strlcat(dst2, src, sizeof(dst2));
        if (exp == got && memcmp(dst1, dst2, sizeof(dst1)) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%zu | got=%zu\nexpected dst='%s' | got dst='%s'", exp, got, dst1, dst2);
    }

    /* subtest 6: multibyte UTF-8 */
    {
        char dst1[12] = "A", dst2[12] = "A";
        const char *src = "éå漢";
        size_t exp = strlcat(dst1, src, sizeof(dst1));
        size_t got = ft_strlcat(dst2, src, sizeof(dst2));
        if (exp == got && memcmp(dst1, dst2, sizeof(dst1)) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%zu | got=%zu\nexpected dst='%s' | got dst='%s'", exp, got, dst1, dst2);
    }

	/* subtest 7: very long destination and source for strlcat */
	{
	    char dst1[100000] = {0}, dst2[100000] = {0};
	    char src[50000];
	    for (size_t i = 0; i < 99999; i++)
	        dst1[i] = 'A' + (i % 26);
	    dst1[99999] = '\0';
	    memcpy(dst2, dst1, sizeof(dst1));
	
	    for (size_t i = 0; i < 49999; i++)
	        src[i] = 'a' + (i % 26);
	    src[49999] = '\0';
	
	    size_t exp = strlcat(dst1, src, sizeof(dst1));
	    size_t got = ft_strlcat(dst2, src, sizeof(dst2));
	    if (exp == got && memcmp(dst1, dst2, sizeof(dst1)) == 0) SUBTEST_OK();
	    else SUBTEST_FAILF(
	        "diff: expected=%zu | got=%zu\nexpected dst[0:10]='%.10s' | got dst[0:10]='%.10s'\nexpected dst[end-10:]=%.10s | got dst[end-10:]=%.10s",
	        exp, got, dst1, dst2, dst1 + sizeof(dst1) - 11, dst2 + sizeof(dst2) - 11
	    );
	}

    return group_finish();
}
