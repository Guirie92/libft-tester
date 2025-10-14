/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_isascii.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:46:42 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 15:39:04 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <ctype.h>
#include "../../libft.h"

int group_isascii(void)
{
    group_start("isascii");

    /* subtest 1: ASCII characters (0-127) */
    {
		int ok = 1;
        for (int c = 0; c <= 127; c++)
        {
            int exp = isascii(c);
            int got = ft_isascii(c);
			if ((exp == 0 && got != 0) || (exp != 0 && got == 0))
            {
                SUBTEST_FAILF("diff ('%c'): expected=%d | got=%d", c, exp, got);
				ok = 0;
                break;
            }
        }
		if (ok) SUBTEST_OK();
    }

    /* subtest 2: non-ASCII characters (128-255) */
    {
		int ok = 1;
        for (int c = 128; c <= 255; c++)
        {
            int exp = isascii(c);
            int got = ft_isascii(c);
			if ((exp == 0 && got != 0) || (exp != 0 && got == 0))
            {
                SUBTEST_FAILF("diff ('%c'): expected=%d | got=%d", c, exp, got);
				ok = 0;
                break;
            }
        }
		if (ok) SUBTEST_OK();
    }

    return group_finish();
}
