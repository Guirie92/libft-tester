/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strmapi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:01:17 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 20:47:27 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <string.h>
#include <stdlib.h>
#include "../../libft.h"

/* reference strmapi */
static char *strmapi(char const *s, char (*f)(unsigned int, char))
{
    char *res;
    size_t i;

    if (!s || !f)
        return NULL;
    if (!*s)
        return strdup("");
    i = strlen(s);
    res = malloc(i + 1);
    if (!res)
        return NULL;
    i = 0;
    while (s[i])
    {
        res[i] = f(i, s[i]);
        i++;
    }
    res[i] = '\0';
    return res;
}

static char f_upper(unsigned int i, char c) { (void)i; return (c >= 'a' && c <= 'z') ? c - 32 : c; }

static char f_index_add(unsigned int i, char c) { return c + i; }

static char f_identity(unsigned int i, char c) { (void)i; return c; }

int group_strmapi(void)
{
	group_start("strmapi");

    /* subtest 1: basic string with uppercase function */
    {
        const char *s = "hello";
        char *exp = strmapi(s, f_upper);
        char *got = ft_strmapi(s, f_upper);
        if (strcmp(exp, got) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", exp, got);
        free(exp); free(got);
    }

    /* subtest 2: empty string */
    {
        const char *s = "";
        char *exp = strmapi(s, f_upper);
        char *got = ft_strmapi(s, f_upper);
        if (strcmp(exp, got) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", exp, got);
        free(exp); free(got);
    }

    /* subtest 3: index-based transformation */
    {
        const char *s = "abcd";
        char *exp = strmapi(s, f_index_add);
        char *got = ft_strmapi(s, f_index_add);
        if (strcmp(exp, got) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'\n(index-based increment)", exp, got);
        free(exp); free(got);
    }

    /* subtest 4: multibyte / UTF-8 characters */
    {
        const char *s = "éå漢";
        char *exp = strmapi(s, f_identity);
        char *got = ft_strmapi(s, f_identity);
        if (strcmp(exp, got) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'\n(multibyte check)", exp, got);
        free(exp); free(got);
    }

    /* subtest 5: NULL string input */
    {
        char *got = ft_strmapi(NULL, f_upper);
        if (got == NULL) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=NULL | got='%s'", got);
    }

    /* subtest 6: NULL function input */
    {
        const char *s = "abc";
        char *got = ft_strmapi(s, NULL);
        if (got == NULL) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected=NULL | got='%s'", got);
    }

    return group_finish();
}
