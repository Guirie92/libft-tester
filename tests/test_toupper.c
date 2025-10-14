/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_toupper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:30:04 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 20:48:34 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <ctype.h>
#include "../../libft.h"

int group_toupper(void)
{
    group_start("toupper");

    /* subtest 1: lowercase letters (a-z) */
    {
        int ok = 1;
        for (int c = 'a'; c <= 'z'; c++)
        {
            int exp = toupper(c);
            int got = ft_toupper(c);
            if (exp != got)
            {
                SUBTEST_FAILF("diff ('%c'): expected=%d | got=%d", c, exp, got);
                ok = 0;
                break;
            }
        }
        if (ok) SUBTEST_OK();
    }

    /* subtest 2: uppercase letters (A-Z) */
    {
        int ok = 1;
        for (int c = 'A'; c <= 'Z'; c++)
        {
            int exp = toupper(c);
            int got = ft_toupper(c);
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
            int exp = toupper(chars[i]);
            int got = ft_toupper(chars[i]);
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
