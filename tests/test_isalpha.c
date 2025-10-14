/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_isalpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:44:26 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 22:19:30 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <ctype.h>
#include "../../libft.h"

size_t group_isalpha(void)
{
    group_start("isalpha");

    /* subtest 1: lowercase letters */
    {
        int ok = 1;
        for (int c = 'a'; c <= 'z'; c++)
        {
			int exp = isalpha(c);
            int got = ft_isalpha(c);
            if ((exp == 0 && got != 0) || (exp != 0 && got == 0))
            {
                SUBTEST_FAILF("diff ('%c'):  expected=%d  |  got=%d", c, isalpha(c), ft_isalpha(c));
                ok = 0;
                break;
            }
        }
        if (ok) SUBTEST_OK();
    }

    /* subtest 2: uppercase letters */
    {
        int ok = 1;
        for (int c = 'A'; c <= 'Z'; c++)
        {
			int exp = isalpha(c);
            int got = ft_isalpha(c);
            if ((exp == 0 && got != 0) || (exp != 0 && got == 0))
            {
                SUBTEST_FAILF("diff ('%c'):  expected=%d  |  got=%d", c, isalpha(c), ft_isalpha(c));
                ok = 0;
                break;
            }
        }
        if (ok) SUBTEST_OK();
    }

    /* subtest 3: non-alpha characters */
    {
        const unsigned char chars[] = "0123456789!@# \t\n";
        int ok = 1;
        for (size_t i = 0; i < sizeof(chars)-1; i++)
        {
			int exp = isalpha(chars[i]);
            int got = ft_isalpha(chars[i]);
            //if (ft_isalpha(chars[i]) <= 0 && isalpha(chars[i]) > 0)
			if ((exp == 0 && got != 0) || (exp != 0 && got == 0))
            {
                SUBTEST_FAILF("diff ('%c'): expected=%d  |  got=%d", chars[i],
					isalpha(chars[i]), ft_isalpha(chars[i]));
                ok = 0;
                break;
            }
        }
        if (ok) SUBTEST_OK();
    }

    return group_finish();
}
