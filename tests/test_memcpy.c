/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:16:07 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 12:47:00 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <string.h>
#include "../../libft.h"

int group_memcpy(void)
{
    group_start("memcpy");

    /* subtest 1: basic copy */
    {
        char src[] = "abcdef";
        char d1[10] = {0}, d2[10] = {0};
        memcpy(d1, src, 6);
        ft_memcpy(d2, src, 6);
        if (memcmp(d1, d2, 6) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", d1, d2);
    }

	/* subtest 2: n == 0 should not touch destination */
	{
		char src[] = "abc";
		char d1[4] = {'X','X','X','\0'}, d2[4] = {'X','X','X','\0'};
		memcpy(d1, src, 0);
		ft_memcpy(d2, src, 0);
		if (memcmp(d1, d2, 3) == 0) SUBTEST_OK();
		else SUBTEST_FAILF("diff: expected='%s' | got='%s'", d1, d2);
		// (n==0 mismatch)
	}
	
	/* subtest 3: overlapping memory (dst < src) */
	{
	    char buf1[10] = "123456789";
	    char buf2[10] = "123456789";
	    memcpy(buf1, buf1 + 2, 5);   // undefined for memcpy
	    ft_memcpy(buf2, buf2 + 2, 5);
	    if (memcmp(buf1, buf2, 10) == 0) SUBTEST_OK();
		else SUBTEST_FAILF("diff: expected='%s' | got='%s'", buf1, buf2);
	    // (overlap (dst < src) mismatch)

	}
	
	/* subtest 4: very large copy */
	{
	    char src[100000];
	    char d1[100000], d2[100000];
	    for (size_t i = 0; i < 100000; i++) src[i] = (char)(i % 256);
	    memcpy(d1, src, 100000);
	    ft_memcpy(d2, src, 100000);
	    if (memcmp(d1, d2, 100000) == 0) SUBTEST_OK();
		else SUBTEST_FAILF("diff: expected='%s' | got='%s'", d1, d2);
	    // (very large copy mismatch)
		
	}
	
	/* subtest 5: n == 0 on garbage */
	{
	    char d1[5] = {'X','X','X','X','X'}, d2[5] = {'X','X','X','X','X'};
	    char src[5] = {'a','b','c','d','e'};
	    memcpy(d1, src, 0);
	    ft_memcpy(d2, src, 0);
	    if (memcmp(d1, d2, 5) == 0) SUBTEST_OK();
		else SUBTEST_FAILF("diff: expected='%s' | got='%s'", d1, d2);
	    // (n==0 with garbage mismatch)
	}
	
	/* subtest 6: integers */
	{
	    int src[5] = {1,2,3,4,5};
	    int d1[5], d2[5];
	    memcpy(d1, src, sizeof(src));
	    ft_memcpy(d2, src, sizeof(src));
	    if (memcmp(d1, d2, sizeof(src)) == 0) SUBTEST_OK();
		else SUBTEST_FAILF("diff: expected='%s' | got='%s'", d1, d2);
	    // (int array copy mismatch)
	}
	
	/* subtest 7: struct copy */
	{
	    struct { int x; char y; } src[2] = {{1,'a'}, {2,'b'}};
	    struct { int x; char y; } d1[2], d2[2];
	    memcpy(d1, src, sizeof(src));
	    ft_memcpy(d2, src, sizeof(src));
	    if (memcmp(d1, d2, sizeof(src)) == 0) SUBTEST_OK();
		else SUBTEST_FAILF("diff: expected='%s' | got='%s'", d1, d2);
		// (struct array copy mismatch)
	}
	
	/* subtest 9: non-aligned pointers */
	{
	    char buffer[10] = "abcdefghi";
	    char d1[10], d2[10];
	    memcpy(d1, buffer + 1, 7);
	    ft_memcpy(d2, buffer + 1, 7);
	    if (memcmp(d1, d2, 7) == 0) SUBTEST_OK();
		else SUBTEST_FAILF("diff: expected='%s' | got='%s'", d1, d2);
	    // (non-aligned copy mismatch)
	}
	
	/* subtest 10: copy one byte */
	{
	    char d1[2] = {0}, d2[2] = {0};
	    char src[] = "x";
	    memcpy(d1, src, 1);
	    ft_memcpy(d2, src, 1);
	    if (memcmp(d1, d2, 1) == 0) SUBTEST_OK();
		else SUBTEST_FAILF("diff: expected='%s' | got='%s'", d1, d2);
	   // (1-byte copy mismatch)
	}

	
    return group_finish();
}
