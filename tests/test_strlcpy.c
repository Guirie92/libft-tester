/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strlcpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:17:43 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 15:39:32 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <bsd/string.h>
#include "../../libft.h"

int group_strlcpy(void)
{
    group_start("strlcpy");

    /* subtest 1: basic copy */
    {
        char dst1[10] = {0}, dst2[10] = {0};
        const char *src = "hello";
        size_t exp = strlcpy(dst1, src, sizeof(dst1));
        size_t got = ft_strlcpy(dst2, src, sizeof(dst2));
        if (exp == got && memcmp(dst1, dst2, sizeof(dst1)) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%zu | got=%zu\nexpected dst='%s' | got dst='%s'", exp, got, dst1, dst2);
    }

    /* subtest 2: zero-size destination */
    {
        char dst1[5] = "XXXX", dst2[5] = "XXXX";
        const char *src = "hello";
        size_t exp = strlcpy(dst1, src, 0);
        size_t got = ft_strlcpy(dst2, src, 0);
        if (exp == got && memcmp(dst1, dst2, 4) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%zu | got=%zu\nexpected dst='%s' | got dst='%s'", exp, got, dst1, dst2);
    }

    /* subtest 3: exact fit */
    {
        char dst1[6] = {0}, dst2[6] = {0};
        const char *src = "hello";
        size_t exp = strlcpy(dst1, src, 6);
        size_t got = ft_strlcpy(dst2, src, 6);
        if (exp == got && memcmp(dst1, dst2, 6) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%zu | got=%zu\nexpected dst='%s' | got dst='%s'", exp, got, dst1, dst2);
    }

    /* subtest 4: source longer than destination */
    {
        char dst1[5] = {0}, dst2[5] = {0};
        const char *src = "hello world";
        size_t exp = strlcpy(dst1, src, sizeof(dst1));
        size_t got = ft_strlcpy(dst2, src, sizeof(dst2));
        if (exp == got && memcmp(dst1, dst2, sizeof(dst1)) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%zu | got=%zu\nexpected dst='%s' | got dst='%s'", exp, got, dst1, dst2);
    }

    /* subtest 5: empty string */
    {
        char dst1[5] = {0}, dst2[5] = {0};
        const char *src = "";
        size_t exp = strlcpy(dst1, src, sizeof(dst1));
        size_t got = ft_strlcpy(dst2, src, sizeof(dst2));
        if (exp == got && memcmp(dst1, dst2, sizeof(dst1)) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%zu | got=%zu\nexpected dst='%s' | got dst='%s'", exp, got, dst1, dst2);
    }

    /* subtest 6: multibyte UTF-8 */
    {
        char dst1[10] = {0}, dst2[10] = {0};
        const char *src = "éå漢";
        size_t exp = strlcpy(dst1, src, sizeof(dst1));
        size_t got = ft_strlcpy(dst2, src, sizeof(dst2));
        if (exp == got && memcmp(dst1, dst2, sizeof(dst1)) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%zu | got=%zu\nexpected dst='%s' | got dst='%s'", exp, got, dst1, dst2);
    }

	/* subtest 7: very long source for strlcpy */
	{
	    char dst1[100000] = {0}, dst2[100000] = {0};
	    char src[100000];
	    for (size_t i = 0; i < 99999; i++)
	        src[i] = 'a' + (i % 26);
	    src[99999] = '\0';
	
	    size_t exp = strlcpy(dst1, src, sizeof(dst1));
	    size_t got = ft_strlcpy(dst2, src, sizeof(dst2));
	    if (exp == got && memcmp(dst1, dst2, sizeof(dst1)) == 0) SUBTEST_OK();
	    else SUBTEST_FAILF("diff: expected=%zu | got=%zu\nexpected dst[0:10]='%.10s' | got dst[0:10]='%.10s'", exp, got, dst1, dst2);
	}

    return group_finish();
}
