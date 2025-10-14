/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:16:26 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 22:23:34 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <string.h>
#include <stdlib.h>
#include "../../libft.h"

size_t group_strjoin(void)
{
	group_start("strjoin");
    
    /* subtest 1: basic concat */
    {
        const char *a = "hello";
        const char *b = "world";
        size_t la = strlen(a), lb = strlen(b);
        char *expected = malloc(la + lb + 1);
        if (!expected) { SUBTEST_FAILF("malloc failed"); }
        else
        {
            memcpy(expected, a, la);
            memcpy(expected + la, b, lb);
            expected[la+lb] = '\0';
            char *got = ft_strjoin(a, b);
            if (!got) SUBTEST_FAILF("ft_strjoin returned NULL");
            else
            {
                if (strcmp(expected, got) == 0) SUBTEST_OK();
                else SUBTEST_FAILF("diff: expected='%s' | got='%s'", expected, got);
                free(got);
            }
            free(expected);
        }
    }
    
    /* subtest 2: first string empty */
    {
        const char *a = "";
        const char *b = "world";
        char *got = ft_strjoin(a, b);
        if (!got) SUBTEST_FAILF("ft_strjoin returned NULL for empty/full");
        else
        {
            if (strcmp(got, "world") == 0) SUBTEST_OK();
            else SUBTEST_FAILF("diff: expected='world' | got='%s'", got);
            free(got);
        }
    }
    
    /* subtest 3: second string empty */
    {
        const char *a = "hello";
        const char *b = "";
        char *got = ft_strjoin(a, b);
        if (!got) SUBTEST_FAILF("ft_strjoin returned NULL for full/empty");
        else
        {
            if (strcmp(got, "hello") == 0) SUBTEST_OK();
            else SUBTEST_FAILF("diff: expected='hello' | got='%s'", got);
            free(got);
        }
    }
    
    /* subtest 4: both strings empty */
    {
        const char *a = "";
        const char *b = "";
        char *got = ft_strjoin(a, b);
        if (!got) SUBTEST_FAILF("ft_strjoin returned NULL for empty/empty");
        else
        {
            if (strcmp(got, "") == 0) SUBTEST_OK();
            else SUBTEST_FAILF("diff: expected empty string | got='%s'", got);
            free(got);
        }
    }
    
    /* subtest 5: NULL first string */
    {
        const char *a = NULL;
        const char *b = "world";
        char *got = ft_strjoin(a, b);
        if (got == NULL) SUBTEST_OK();
        else
        {
            SUBTEST_FAILF("expected NULL for NULL first string | got='%s'", got);
            free(got);
        }
    }
    
    /* subtest 6: NULL second string */
    {
        const char *a = "hello";
        const char *b = NULL;
        char *got = ft_strjoin(a, b);
        if (got == NULL) SUBTEST_OK();
        else
        {
            SUBTEST_FAILF("expected NULL for NULL second string | got='%s'", got);
            free(got);
        }
    }
    
    /* subtest 7: both strings NULL */
    {
        const char *a = NULL;
        const char *b = NULL;
        char *got = ft_strjoin(a, b);
        if (got == NULL) SUBTEST_OK();
        else
        {
            SUBTEST_FAILF("expected NULL for both NULL strings | got='%s'", got);
            free(got);
        }
    }
    
    /* subtest 8: very long strings */
    {
        char *long1 = malloc(10001);
        char *long2 = malloc(10001);
        if (!long1 || !long2) { 
            SUBTEST_FAILF("malloc failed for long strings");
            if (long1) free(long1);
            if (long2) free(long2);
        }
        else
        {
            memset(long1, 'A', 10000);
            memset(long2, 'B', 10000);
            long1[10000] = '\0';
            long2[10000] = '\0';
            
            char *got = ft_strjoin(long1, long2);
            if (!got) SUBTEST_FAILF("ft_strjoin returned NULL for long strings");
            else
            {
                int ok = 1;
                for (int i = 0; i < 10000; i++) {
                    if (got[i] != 'A') { ok = 0; break; }
                }
                for (int i = 0; i < 10000; i++) {
                    if (got[10000 + i] != 'B') { ok = 0; break; }
                }
                if (ok && got[20000] == '\0') SUBTEST_OK();
                else SUBTEST_FAILF("long string concatenation failed");
                free(got);
            }
            free(long1);
            free(long2);
        }
    }
    
    /* subtest 9: strings with special characters */
    {
        const char *a = "hello\tworld\n";
        const char *b = "test\x01string";
        size_t la = strlen(a), lb = strlen(b);
        char *expected = malloc(la + lb + 1);
        if (!expected) { SUBTEST_FAILF("malloc failed"); }
        else
        {
            memcpy(expected, a, la);
            memcpy(expected + la, b, lb);
            expected[la+lb] = '\0';
            char *got = ft_strjoin(a, b);
            if (!got) SUBTEST_FAILF("ft_strjoin returned NULL for special chars");
            else
            {
                if (memcmp(expected, got, la + lb) == 0) SUBTEST_OK();
                else SUBTEST_FAILF("special characters not handled correctly");
                free(got);
            }
            free(expected);
        }
    }
    
    /* subtest 10: verify null termination */
    {
        const char *a = "test";
        const char *b = "ing";
        char *got = ft_strjoin(a, b);
        if (!got) SUBTEST_FAILF("ft_strjoin returned NULL");
        else
        {
            size_t len = strlen(got);
            if (got[len] == '\0') SUBTEST_OK();
            else SUBTEST_FAILF("result not properly null-terminated");
            free(got);
        }
    }

    return group_finish();
}
