/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_isalnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:45:23 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 22:19:28 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <ctype.h>
#include "../../libft.h"
#define SIGN_OK(e,g) ((exp == 0 && got != 0) || (exp != 0 && got == 0))

size_t group_isalnum(void)
{
    group_start("isalnum");

    /* subtest 1: letters */
    {
		int ok = 1;
        const char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (size_t i = 0; i < sizeof(letters)-1; i++)
        {
            int exp = isalnum(letters[i]);
            int got = ft_isalnum(letters[i]);
			if (SIGN_OK(exp,got))
            {
                SUBTEST_FAILF("diff ('%c'): expected=%d | got=%d", letters[i], exp, got);
				ok = 0;
                break;
            }
        }
		if (ok) SUBTEST_OK();
    }

    /* subtest 2: digits */
    {
		int ok = 1;
        for (char c = '0'; c <= '9'; c++)
        {
            int exp = isalnum(c);
            int got = ft_isalnum(c);
			if (SIGN_OK(exp,got))
            {
                SUBTEST_FAILF("diff ('%c'): expected=%d | got=%d", c, exp, got);
				ok = 0;
                break;
            }
        }
		if (ok) SUBTEST_OK();
    }

    /* subtest 3: non-alphanumeric */
    {
		int ok = 1;
        const char chars[] = "!@# \t\n";
        for (size_t i = 0; i < sizeof(chars)-1; i++)
        {
            int exp = isalnum(chars[i]);
            int got = ft_isalnum(chars[i]);
			if (SIGN_OK(exp,got))
            {
                SUBTEST_FAILF("diff ('%c'): expected=%d | got=%d", chars[i], exp, got);
				ok = 0;
                break;
            }
        }
		if (ok) SUBTEST_OK();
    }

    return group_finish();
}
