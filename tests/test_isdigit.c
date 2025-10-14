/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_isdigit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:45:01 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 22:21:38 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <ctype.h>
#include "../../libft.h"

size_t group_isdigit(void)
{
    group_start("isdigit");

    /* subtest 1: digits 0-9 */
    {
		int ok = 1;
        for (char c = '0'; c <= '9'; c++)
        {
            int exp = isdigit(c);
            int got = ft_isdigit(c);
			if ((exp == 0 && got != 0) || (exp != 0 && got == 0))
            {
                SUBTEST_FAILF("diff ('%c'): expected=%d | got=%d", c, exp, got);
				ok = 0;
                break;
            }
        }
		if (ok) SUBTEST_OK();
    }

    /* subtest 2: non-digit characters */
    {
		int ok = 1;
        const char chars[] = "abc!@# \t\n";
        for (size_t i = 0; i < sizeof(chars)-1; i++)
        {
            int exp = isdigit(chars[i]);
            int got = ft_isdigit(chars[i]);
			if ((exp == 0 && got != 0) || (exp != 0 && got == 0))
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
