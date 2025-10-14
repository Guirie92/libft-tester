/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tolower.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:29:53 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 22:24:07 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <ctype.h>
#include "../../libft.h"

size_t group_tolower(void)
{
    group_start("tolower");

    /* subtest 1: uppercase letters (A-Z) */
    {
        int ok = 1;
        for (int c = 'A'; c <= 'Z'; c++)
        {
            int exp = tolower(c);
            int got = ft_tolower(c);
            if (exp != got)
            {
                SUBTEST_FAILF("diff ('%c'): expected=%d | got=%d", c, exp, got);
                ok = 0;
                break;
            }
        }
        if (ok) SUBTEST_OK();
    }

    /* subtest 2: lowercase letters (a-z) */
    {
        int ok = 1;
        for (int c = 'a'; c <= 'z'; c++)
        {
            int exp = tolower(c);
            int got = ft_tolower(c);
            if (exp != got)
            {
                SUBTEST_FAILF("diff ('%c'): expected=%d | got=%d", c, exp, got);
                ok = 0;
                break;
            }
        }
        if (ok) SUBTEST_OK();
    }

    /* subtest 3: non-alphabetic characters (digits, symbols, whitespace) */
    {
        const char chars[] = "0123456789!@#$%^&*()-_=+[]{};:'\",.<>/? \t\n";
        int ok = 1;
        for (size_t i = 0; i < sizeof(chars) - 1; i++)
        {
            int exp = tolower(chars[i]);
            int got = ft_tolower(chars[i]);
            if (exp != got)
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
