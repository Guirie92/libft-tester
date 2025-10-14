/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:04:51 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 22:23:40 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <string.h>
#include "../../libft.h"

size_t group_strlen(void)
{
    group_start("strlen");

    /* subtest 1: basic */
    {
        const char *s = "hello";
        size_t exp = strlen(s);
        size_t got = ft_strlen(s);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%zu | got=%zu", exp, got);
    }
	
	/* subtest 2: empty */
    {
        const char *s = "";
        size_t exp = strlen(s);
        size_t got = ft_strlen(s);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%zu | got=%zu", exp, got);
    }

	/* subtest 3: longer */
    {
        const char *s = "this is a longer test string";
        size_t exp = strlen(s);
        size_t got = ft_strlen(s);
        if (exp == got) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=%zu | got=%zu", exp, got);
    }

	/* subtest 4: string with embedded null bytes */
	{
	    const char s[6] = {'h', 'e', '\0', 'l', 'l', 'o'}; // strlen stops at first '\0'
	    size_t exp = strlen(s);
	    size_t got = ft_strlen(s);
	    if (exp == got) SUBTEST_OK();
	    else SUBTEST_FAILF("diff: expected=%zu | got=%zu", exp, got);
	}

	/* subtest 5: very long string */
	{
	    char s[100000];
	    for (size_t i = 0; i < 99999; i++)
	        s[i] = 'a';
	    s[99999] = '\0';
	
	    size_t exp = strlen(s);
	    size_t got = ft_strlen(s);
	    if (exp == got) SUBTEST_OK();
	    else SUBTEST_FAILF("diff: expected=%zu | got=%zu", exp, got);
	}

	/* subtest 6: only whitespace */
	{
	    const char *s = "   \t\n";
	    size_t exp = strlen(s);
	    size_t got = ft_strlen(s);
	    if (exp == got) SUBTEST_OK();
	    else SUBTEST_FAILF("diff: expected=%zu | got=%zu", exp, got);
	}

	/* subtest 7: multibyte UTF-8 characters */
	{
    	const char *s = "éå漢";
    	size_t exp = strlen(s); // counts bytes, not Unicode chars
    	size_t got = ft_strlen(s);
    	if (exp == got) SUBTEST_OK();
    	else SUBTEST_FAILF("diff: expected=%zu | got=%zu", exp, got);
	}

	/* subtest 8: single character */
	{
	    const char *s = "x";
	    size_t exp = strlen(s);
	    size_t got = ft_strlen(s);
	    if (exp == got) SUBTEST_OK();
	    else SUBTEST_FAILF("diff: expected=%zu | got=%zu", exp, got);
	}
	
    return group_finish();
}
