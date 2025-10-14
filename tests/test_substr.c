/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_substr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:59:19 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 20:48:15 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <string.h>
#include <stdlib.h>
#include "../../libft.h"

static void free_and_fail(char *s1, char *s2, const char *fmt, const char *exp, const char *got)
{
    if (s1) free(s1);
    if (s2) free(s2);
    SUBTEST_FAILF(fmt, exp, got);
}

static void free_and_ok(char *s1, char *s2)
{
    if (s1) free(s1);
    if (s2) free(s2);
    SUBTEST_OK();
}

int group_substr(void)
{
	group_start("substr");
    char *got;

    /* subtest 1: basic middle extraction (start=2, len=3) */
    {
        const char *s = "abcdefgh";
        const char *exp = "cde";
        got = ft_substr(s, 2, 3);
        if (got && strcmp(exp, got) == 0) free_and_ok(got, NULL);
        else free_and_fail(got, NULL, "diff: expected='%s' | got='%s'", exp, got ? got : "NULL");
    }

    /* subtest 2: start at 0, full string copy (len > s_len) */
    {
        const char *s = "hello";
        const char *exp = "hello";
        got = ft_substr(s, 0, 10);
        if (got && strcmp(exp, got) == 0) free_and_ok(got, NULL);
        else free_and_fail(got, NULL, "diff: expected='%s' | got='%s'", exp, got ? got : "NULL");
    }

    /* subtest 3: extract till end (start=3, len=MAX) */
    {
        const char *s = "0123456789";
        const char *exp = "3456789";
        got = ft_substr(s, 3, 100);
        if (got && strcmp(exp, got) == 0) free_and_ok(got, NULL);
        else free_and_fail(got, NULL, "diff: expected='%s' | got='%s'", exp, got ? got : "NULL");
    }

    // -------------------------------------------------------------------------
    // HARD EDGE CASE: Start Index
    // -------------------------------------------------------------------------

    /* subtest 4: start exactly at string end (s_len) -> Should return "" */
    {
        const char *s = "abc"; // s_len = 3
        const char *exp = "";
        got = ft_substr(s, 3, 5);
        if (got && strcmp(exp, got) == 0) free_and_ok(got, NULL);
        else free_and_fail(got, NULL, "diff: expected='%s' | got='%s'", exp, got ? got : "NULL");
        // (start at s_len mismatch)
    }

    /* subtest 5: start past string end (s_len + 1) -> Should return "" */
    {
        const char *s = "abc"; // s_len = 3
        const char *exp = "";
        got = ft_substr(s, 4, 5);
        if (got && strcmp(exp, got) == 0) free_and_ok(got, NULL);
        else free_and_fail(got, NULL, "diff: expected='%s' | got='%s'", exp, got ? got : "NULL");
        // (start > s_len mismatch)
    }

    // -------------------------------------------------------------------------
    // HARD EDGE CASE: Length Parameter (len)
    // -------------------------------------------------------------------------

    /* subtest 6: len = 0 (any start) -> Should return "" */
    {
        const char *s = "abcdef";
        const char *exp = "";
        got = ft_substr(s, 1, 0);
        if (got && strcmp(exp, got) == 0) free_and_ok(got, NULL);
        else free_and_fail(got, NULL, "diff: expected='%s' | got='%s'", exp, got ? got : "NULL");
        // (len=0 mismatch)
    }

    /* subtest 7: extraction of exactly one character (start=0, len=1) */
    {
        const char *s = "a";
        const char *exp = "a";
        got = ft_substr(s, 0, 1);
        if (got && strcmp(exp, got) == 0) free_and_ok(got, NULL);
        else free_and_fail(got, NULL, "diff: expected='%s' | got='%s'", exp, got ? got : "NULL");
    }
    
    // -------------------------------------------------------------------------
    // HARD EDGE CASE: Source String (s)
    // -------------------------------------------------------------------------

    /* subtest 8: empty source string s = "" */
    {
        const char *s = "";
        const char *exp = "";
        got = ft_substr(s, 0, 5);
        if (got && strcmp(exp, got) == 0) free_and_ok(got, NULL);
        else free_and_fail(got, NULL, "diff: expected='%s' | got='%s'", exp, got ? got : "NULL");
    }

    /* subtest 9: source string s = NULL (standard behavior is to return NULL) */
    {
        const char *s = NULL;
        const char *exp = "NULL"; // Representing NULL pointer
        got = ft_substr(s, 0, 5);
        if (got == NULL) free_and_ok(NULL, NULL);
        else free_and_fail(got, NULL, "diff: expected='%s' | got='%s'", exp, got ? got : "ptr (not NULL)");
        // (s=NULL mismatch)
    }

    /* subtest 10: large string, mid-range extraction */
    {
        char s[100];
        memset(s, 'A', 99);
        s[99] = '\0';
        const char *exp = "AAAAA";
        got = ft_substr(s, 50, 5);
        if (got && strcmp(exp, got) == 0) free_and_ok(got, NULL);
        else free_and_fail(got, NULL, "diff: expected='%s' | got='%s'", exp, got ? got : "NULL");
    }
    
    return group_finish();
}
