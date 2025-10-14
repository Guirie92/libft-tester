/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_isprint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:47:17 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 22:21:40 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <ctype.h>
#include "../../libft.h"

size_t group_isprint(void)
{
    group_start("isprint");

    /* subtest 1: printable ASCII (32-126) */
    {
		int ok = 1;
        for (int c = 32; c <= 126; c++)
        {
            int exp = isprint(c);
            int got = ft_isprint(c);
			if ((exp == 0 && got != 0) || (exp != 0 && got == 0))
            {
                SUBTEST_FAILF("diff ('%c'): expected=%d | got=%d", c, exp, got);
				ok = 0;
                break;
            }
        }
		if (ok) SUBTEST_OK();
    }

    /* subtest 2: non-printable ASCII (0-31, 127) */
    {
		int ok = 1;
        for (int c = 0; c <= 31; c++)
        {
            int exp = isprint(c);
            int got = ft_isprint(c);
			if ((exp == 0 && got != 0) || (exp != 0 && got == 0))
            {
                SUBTEST_FAILF("diff ('%c'): expected=%d | got=%d", c, exp, got);
				ok = 0;
                break;
            }
        }
		if (ok)
		{
			int c = 127;
			int exp = isprint(c);
			int got = ft_isprint(c);
			if ((exp == 0 && got != 0) || (exp != 0 && got == 0))
				SUBTEST_FAILF("diff ('%c'): expected=%d | got=%d", c, exp, got);
			else
				SUBTEST_OK();
		}
			
    }

    return group_finish();
}
