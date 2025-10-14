/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_striteri.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:01:26 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 22:23:30 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <string.h>
#include "../../libft.h"

/* reference implementation for comparison */
static void striteri(char *s, void (*f)(unsigned int, char*))
{
    size_t i;

    if (!s || !f)
        return;
    i = -1;
    while (s[++i])
        f(i, &s[i]);
}

static void test_func_index_upper(unsigned int i, char *c)
{
    if (i % 2 == 0)
        *c = ft_toupper(*c);
}

static void test_func_add_index(unsigned int i, char *c)
{
    *c = *c + (char)(i % 10);
}

static void test_func_null_third(unsigned int i, char *c)
{
    if (i % 3 == 0)
        *c = '\0';
}

size_t group_striteri(void)
{
	group_start("striteri");

    /* subtest 1: basic functionality - uppercase even indices */
    {
        char s1_ft[] = "abcdef";
        char s1_ref[] = "abcdef";
        
        ft_striteri(s1_ft, test_func_index_upper);
        striteri(s1_ref, test_func_index_upper);
        
        if (strcmp(s1_ft, s1_ref) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", s1_ref, s1_ft);
    }

    /* subtest 2: empty string */
    {
        char s1_ft[] = "";
        char s1_ref[] = "";
        
        ft_striteri(s1_ft, test_func_index_upper);
        striteri(s1_ref, test_func_index_upper);
        
        if (strcmp(s1_ft, s1_ref) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", s1_ref, s1_ft);
    }

    /* subtest 3: single character */
    {
        char s1_ft[] = "a";
        char s1_ref[] = "a";
        
        ft_striteri(s1_ft, test_func_index_upper);
        striteri(s1_ref, test_func_index_upper);
        
        if (strcmp(s1_ft, s1_ref) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", s1_ref, s1_ft);
    }

    /* subtest 4: function that modifies characters with index arithmetic */
    {
        char s1_ft[] = "aaaa";
        char s1_ref[] = "aaaa";
        
        ft_striteri(s1_ft, test_func_add_index);
        striteri(s1_ref, test_func_add_index);
        
        if (strcmp(s1_ft, s1_ref) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", s1_ref, s1_ft);
    }

    /* subtest 5: function that introduces null bytes (string termination) */
    {
        char s1_ft[7] = "abcdef";
        char s1_ref[7] = "abcdef";
        
        ft_striteri(s1_ft, test_func_null_third);
        striteri(s1_ref, test_func_null_third);
        
        if (strcmp(s1_ft, s1_ref) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", s1_ref, s1_ft);
    }

    /* subtest 6: NULL string pointer (should not crash) */
    {
        char *null_str = NULL;
        ft_striteri(null_str, test_func_index_upper);
        SUBTEST_OK(); // If we get here without crashing, it's good
    }

    /* subtest 7: NULL function pointer (should not crash) */
    {
        char str[] = "test";
        ft_striteri(str, NULL);
        SUBTEST_OK(); // If we get here without crashing, it's good
    }

    /* subtest 8: both NULL pointers (should not crash) */
    {
        ft_striteri(NULL, NULL);
        SUBTEST_OK(); // If we get here without crashing, it's good
    }

    /* subtest 9: long string */
    {
        char long_str_ft[100];
        char long_str_ref[100];
        
        for (int i = 0; i < 99; i++) {
            long_str_ft[i] = 'a' + (i % 26);
            long_str_ref[i] = 'a' + (i % 26);
        }
        long_str_ft[99] = '\0';
        long_str_ref[99] = '\0';
        
        ft_striteri(long_str_ft, test_func_index_upper);
        striteri(long_str_ref, test_func_index_upper);
        
        if (strcmp(long_str_ft, long_str_ref) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff in long string");
    }

    return group_finish();
}
