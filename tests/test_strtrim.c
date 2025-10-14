/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strtrim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:00:48 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 20:47:53 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <string.h>
#include <stdlib.h>
#include "../../libft.h"

int group_strtrim(void)
{
	group_start("strtrim");

    /* subtest 1: basic trim from both sides */
    {
        const char *s1 = "   hello world   ";
        const char *set = " ";
        char *expected = "hello world";
        char *got = ft_strtrim(s1, set);
        if (!got) SUBTEST_FAILF("ft_strtrim returned NULL");
        else if (strcmp(expected, got) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", expected, got);
        free(got);
    }

    /* subtest 2: trim multiple different characters */
    {
        const char *s1 = " \t\nhello world\t\n ";
        const char *set = " \t\n";
        char *expected = "hello world";
        char *got = ft_strtrim(s1, set);
        if (!got) SUBTEST_FAILF("ft_strtrim returned NULL");
        else if (strcmp(expected, got) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", expected, got);
        free(got);
    }

    /* subtest 3: no trimming needed */
    {
        const char *s1 = "hello world";
        const char *set = " ";
        char *expected = "hello world";
        char *got = ft_strtrim(s1, set);
        if (!got) SUBTEST_FAILF("ft_strtrim returned NULL");
        else if (strcmp(expected, got) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", expected, got);
        free(got);
    }

    /* subtest 4: empty string */
    {
        const char *s1 = "";
        const char *set = " ";
        char *expected = "";
        char *got = ft_strtrim(s1, set);
        if (!got) SUBTEST_FAILF("ft_strtrim returned NULL");
        else if (strcmp(expected, got) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", expected, got);
        free(got);
    }

    /* subtest 5: all characters trimmed */
    {
        const char *s1 = "xxx";
        const char *set = "x";
        char *expected = "";
        char *got = ft_strtrim(s1, set);
        if (!got) SUBTEST_FAILF("ft_strtrim returned NULL");
        else if (strcmp(expected, got) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", expected, got);
        free(got);
    }

    /* subtest 6: NULL string */
    {
        const char *s1 = NULL;
        const char *set = " ";
        char *got = ft_strtrim(s1, set);
        if (got == NULL) SUBTEST_OK();
        else
        {
            SUBTEST_FAILF("expected NULL for NULL string | got='%s'", got);
            free(got);
        }
    }

    /* subtest 7: NULL set */
    {
        const char *s1 = "hello";
        const char *set = NULL;
        char *got = ft_strtrim(s1, set);
        if (got == NULL) SUBTEST_OK();
        else
        {
            SUBTEST_FAILF("expected NULL for NULL set | got='%s'", got);
            free(got);
        }
    }

    /* subtest 8: both NULL */
    {
        const char *s1 = NULL;
        const char *set = NULL;
        char *got = ft_strtrim(s1, set);
        if (got == NULL) SUBTEST_OK();
        else
        {
            SUBTEST_FAILF("expected NULL for both NULL | got='%s'", got);
            free(got);
        }
    }

    /* subtest 9: empty set (trim nothing) */
    {
        const char *s1 = "   hello   ";
        const char *set = "";
        char *expected = "   hello   ";
        char *got = ft_strtrim(s1, set);
        if (!got) SUBTEST_FAILF("ft_strtrim returned NULL");
        else if (strcmp(expected, got) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", expected, got);
        free(got);
    }

    /* subtest 10: trim only from left */
    {
        const char *s1 = "   hello";
        const char *set = " ";
        char *expected = "hello";
        char *got = ft_strtrim(s1, set);
        if (!got) SUBTEST_FAILF("ft_strtrim returned NULL");
        else if (strcmp(expected, got) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", expected, got);
        free(got);
    }

    /* subtest 11: trim only from right */
    {
        const char *s1 = "hello   ";
        const char *set = " ";
        char *expected = "hello";
        char *got = ft_strtrim(s1, set);
        if (!got) SUBTEST_FAILF("ft_strtrim returned NULL");
        else if (strcmp(expected, got) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", expected, got);
        free(got);
    }

    /* subtest 12: string with only trim characters */
    {
        const char *s1 = "     ";
        const char *set = " ";
        char *expected = "";
        char *got = ft_strtrim(s1, set);
        if (!got) SUBTEST_FAILF("ft_strtrim returned NULL");
        else if (strcmp(expected, got) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", expected, got);
        free(got);
    }

    /* subtest 13: complex trim set */
    {
        const char *s1 = "*#*hello world#*#";
        const char *set = "*#";
        char *expected = "hello world";
        char *got = ft_strtrim(s1, set);
        if (!got) SUBTEST_FAILF("ft_strtrim returned NULL");
        else if (strcmp(expected, got) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", expected, got);
        free(got);
    }

    /* subtest 14: verify new string is properly allocated */
    {
        const char *s1 = "  test  ";
        const char *set = " ";
        char *got = ft_strtrim(s1, set);
        if (!got) SUBTEST_FAILF("ft_strtrim returned NULL");
        else
        {
            // Check if it's a different memory address
            if (got != s1 && strcmp(got, "test") == 0) SUBTEST_OK();
            else SUBTEST_FAILF("memory issue: same address or wrong content");
            free(got);
        }
    }

    return group_finish();
}
