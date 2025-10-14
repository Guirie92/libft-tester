/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:00:56 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 22:23:18 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <string.h>
#include <stdlib.h>
#include "../../libft.h"

static size_t compare_string_arrays(char **expected, char **got)
{
    if (expected == NULL && got == NULL) return 1;
    if (expected == NULL || got == NULL) return 0;
    
    size_t i = 0;
    while (expected[i] != NULL && got[i] != NULL) {
        if (strcmp(expected[i], got[i]) != 0) return 0;
        i++;
    }
    return (expected[i] == NULL && got[i] == NULL);
}

static void free_string_array(char **arr)
{
    if (arr == NULL) return;
    for (int i = 0; arr[i] != NULL; i++) free(arr[i]);
    free(arr);
}

static char **create_expected_array(const char **strings)
{
    int count = 0;
    while (strings[count] != NULL) count++;
    
    char **arr = malloc((count + 1) * sizeof(char *));
    if (!arr) return NULL;
    
    for (int i = 0; i < count; i++) {
        arr[i] = strdup(strings[i]);
        if (!arr[i]) {
            for (int j = 0; j < i; j++) free(arr[j]);
            free(arr);
            return NULL;
        }
    }
    arr[count] = NULL;
    return arr;
}

size_t group_split(void)
{
	group_start("split");

    /* subtest 1: basic split */
    {
        const char *s = "hello world test";
        char c = ' ';
        const char *expected_strs[] = {"hello", "world", "test", NULL};
        char **expected = create_expected_array(expected_strs);
        char **got = ft_split(s, c);
        
        if (!expected) SUBTEST_FAILF("malloc failed in test setup");
        else if (compare_string_arrays(expected, got)) SUBTEST_OK();
        else SUBTEST_FAILF("basic split failed");
        
        free_string_array(expected);
        free_string_array(got);
    }

    /* subtest 2: multiple consecutive delimiters */
    {
        const char *s = "hello   world    test";
        char c = ' ';
        const char *expected_strs[] = {"hello", "world", "test", NULL};
        char **expected = create_expected_array(expected_strs);
        char **got = ft_split(s, c);
        
        if (!expected) SUBTEST_FAILF("malloc failed in test setup");
        else if (compare_string_arrays(expected, got)) SUBTEST_OK();
        else SUBTEST_FAILF("multiple consecutive delimiters failed");
        
        free_string_array(expected);
        free_string_array(got);
    }

    /* subtest 3: delimiter at start and end */
    {
        const char *s = "  hello world test  ";
        char c = ' ';
        const char *expected_strs[] = {"hello", "world", "test", NULL};
        char **expected = create_expected_array(expected_strs);
        char **got = ft_split(s, c);
        
        if (!expected) SUBTEST_FAILF("malloc failed in test setup");
        else if (compare_string_arrays(expected, got)) SUBTEST_OK();
        else SUBTEST_FAILF("delimiters at start/end failed");
        
        free_string_array(expected);
        free_string_array(got);
    }

    /* subtest 4: only delimiters */
    {
        const char *s = "     ";
        char c = ' ';
        const char *expected_strs[] = {NULL};
        char **expected = create_expected_array(expected_strs);
        char **got = ft_split(s, c);
        
        if (!expected) SUBTEST_FAILF("malloc failed in test setup");
        else if (compare_string_arrays(expected, got)) SUBTEST_OK();
        else SUBTEST_FAILF("only delimiters failed");
        
        free_string_array(expected);
        free_string_array(got);
    }

    /* subtest 5: empty string */
    {
        const char *s = "";
        char c = ' ';
        const char *expected_strs[] = {NULL};
        char **expected = create_expected_array(expected_strs);
        char **got = ft_split(s, c);
        
        if (!expected) SUBTEST_FAILF("malloc failed in test setup");
        else if (compare_string_arrays(expected, got)) SUBTEST_OK();
        else SUBTEST_FAILF("empty string failed");
        
        free_string_array(expected);
        free_string_array(got);
    }

    /* subtest 6: NULL string */
    {
        const char *s = NULL;
        char c = ' ';
        char **got = ft_split(s, c);
        
        if (got == NULL) SUBTEST_OK();
        else
        {
            SUBTEST_FAILF("expected NULL for NULL string");
            free_string_array(got);
        }
    }

    /* subtest 7: no delimiters in string */
    {
        const char *s = "hello";
        char c = ' ';
        const char *expected_strs[] = {"hello", NULL};
        char **expected = create_expected_array(expected_strs);
        char **got = ft_split(s, c);
        
        if (!expected) SUBTEST_FAILF("malloc failed in test setup");
        else if (compare_string_arrays(expected, got)) SUBTEST_OK();
        else SUBTEST_FAILF("no delimiters failed");
        
        free_string_array(expected);
        free_string_array(got);
    }

    /* subtest 8: different delimiter */
    {
        const char *s = "hello,world,test";
        char c = ',';
        const char *expected_strs[] = {"hello", "world", "test", NULL};
        char **expected = create_expected_array(expected_strs);
        char **got = ft_split(s, c);
        
        if (!expected) SUBTEST_FAILF("malloc failed in test setup");
        else if (compare_string_arrays(expected, got)) SUBTEST_OK();
        else SUBTEST_FAILF("different delimiter failed");
        
        free_string_array(expected);
        free_string_array(got);
    }

    /* subtest 9: tab delimiter */
    {
        const char *s = "hello\tworld\ttest";
        char c = '\t';
        const char *expected_strs[] = {"hello", "world", "test", NULL};
        char **expected = create_expected_array(expected_strs);
        char **got = ft_split(s, c);
        
        if (!expected) SUBTEST_FAILF("malloc failed in test setup");
        else if (compare_string_arrays(expected, got)) SUBTEST_OK();
        else SUBTEST_FAILF("tab delimiter failed");
        
        free_string_array(expected);
        free_string_array(got);
    }

    /* subtest 10: single character between delimiters */
    {
        const char *s = "a b c d e";
        char c = ' ';
        const char *expected_strs[] = {"a", "b", "c", "d", "e", NULL};
        char **expected = create_expected_array(expected_strs);
        char **got = ft_split(s, c);
        
        if (!expected) SUBTEST_FAILF("malloc failed in test setup");
        else if (compare_string_arrays(expected, got)) SUBTEST_OK();
        else SUBTEST_FAILF("single characters failed");
        
        free_string_array(expected);
        free_string_array(got);
    }

    /* subtest 11: verify null termination of array */
    {
        const char *s = "hello world";
        char c = ' ';
        char **got = ft_split(s, c);
        
        if (!got) SUBTEST_FAILF("ft_split returned NULL");
        else
        {
            int count = 0;
            while (got[count] != NULL) count++;
            
            if (count == 2 && strcmp(got[0], "hello") == 0 && 
                strcmp(got[1], "world") == 0 && got[2] == NULL) SUBTEST_OK();
            else SUBTEST_FAILF("array not properly null-terminated");
            
            free_string_array(got);
        }
    }

    /* subtest 12: delimiter as null character */
    {
        const char s[] = {'h', 'e', 'l', 'l', 'o', '\0', 'w', 'o', 'r', 'l', 'd', '\0'};
        char c = '\0';
        // This should treat the entire string as one token since null is string terminator
        const char *expected_strs[] = {"hello", NULL};
        char **expected = create_expected_array(expected_strs);
        char **got = ft_split(s, c);
        
        if (!expected) SUBTEST_FAILF("malloc failed in test setup");
        else if (compare_string_arrays(expected, got)) SUBTEST_OK();
        else SUBTEST_FAILF("null delimiter failed");
        
        free_string_array(expected);
        free_string_array(got);
    }

    return group_finish();
}
