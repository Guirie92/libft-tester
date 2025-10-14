/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:59:40 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 22:23:26 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <string.h>
#include <stdlib.h>
#include "../../libft.h"

/* helper function to check the result and free memory */
static void check_and_free(const char *src, char *exp_ptr, char *got_ptr)
{
    // check if both pointers are NULL (expected failure) or both non-NULL (expected success)
    if ((exp_ptr == NULL && got_ptr == NULL) || (exp_ptr != NULL && got_ptr != NULL))
    {
        if (exp_ptr != NULL) // Success case
        {
            // check if the content is correct
            if (strcmp(exp_ptr, got_ptr) == 0)
            {
                // check if the pointers are different (a real copy)
                if (src != got_ptr) SUBTEST_OK();
                else SUBTEST_FAILF("diff: expected='%s' | got='%s'\nPointer check: Source pointer returned, not a new copy.", exp_ptr, got_ptr);
            }
            else SUBTEST_FAILF("diff: expected='%s' | got='%s'", exp_ptr, got_ptr);
            
            free(got_ptr); // Clean up
            free(exp_ptr); // Clean up the standard lib result too
        }
        else // failure case (both NULL)
        {
            SUBTEST_OK();
        }
    }
    else
    {
        // mismatched NULL/non-NULL return
        SUBTEST_FAILF("diff: expected=%s | got=%s", exp_ptr == NULL ? "NULL" : "non-NULL", got_ptr == NULL ? "NULL" : "non-NULL");
        if (got_ptr) free(got_ptr);
        if (exp_ptr) free(exp_ptr);
    }
}
	
size_t group_strdup(void)
{
	group_start("strdup");


    /* subtest 1: basic string */
    {
        const char *s = "42 Libft";
        char *exp = strdup(s);
        char *got = ft_strdup(s);
        check_and_free(s, exp, got);
    }
    
    /* subtest 2: empty string */
    {
        const char *s = "";
        char *exp = strdup(s);
        char *got = ft_strdup(s);
        check_and_free(s, exp, got);
    }

    /* subtest 3: string with special characters (whitespace, numbers) */
    {
        const char *s = " \t\n123!@#$";
        char *exp = strdup(s);
        char *got = ft_strdup(s);
        check_and_free(s, exp, got);
    }
    
    /* subtest 4: single character string */
    {
        const char *s = "x";
        char *exp = strdup(s);
        char *got = ft_strdup(s);
        check_and_free(s, exp, got);
    }

    /* subtest 5: very long string (stress test for allocation/copy) */
    {
        char s[10000];
        for (size_t i = 0; i < 9999; i++)
            s[i] = (char)('a' + (i % 26));
        s[9999] = '\0';
    
        char *exp = strdup(s);
        char *got = ft_strdup(s);
        check_and_free(s, exp, got);
    }

    /* subtest 6: string containing a null byte (should stop at first '\0') */
    {
        const char s_buf[6] = {'h', 'e', '\0', 'l', 'l', 'o'}; // C string is only "he"
        const char *s = s_buf;
        char *exp = strdup(s);
        char *got = ft_strdup(s);
        // The expected/got should only be "he" + '\0'
        check_and_free(s, exp, got);
    }

    /* subtest 7: multibyte UTF-8 characters */
	{
		const char *s = "éå漢"; // strlen returns byte count (e.g., 2+2+3 = 7 bytes)
		char *exp = strdup(s);
		char *got = ft_strdup(s);
		check_and_free(s, exp, got);
	}

    return group_finish();
}
