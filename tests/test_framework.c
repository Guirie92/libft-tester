/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_framework.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:07:45 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/18 08:04:33 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#define MAX_SUBTESTS 128

unsigned int	g_b_flush = TRUE;
float			g_flush_seconds = 0.02;

typedef struct s_sub
{
    size_t idx;
    size_t ok;
    char *detail;
} t_sub;

static const char *g_group_name = NULL;
static t_sub g_subs[MAX_SUBTESTS];
static size_t g_sub_count = 0;

static void flush_sleep()
{
    if (!g_b_flush)
        return;
    fflush(stdout);
    usleep((g_flush_seconds * 1000) * 1000); // 40ms by default
}
void group_start(const char *name)
{
    g_group_name = name;
    g_sub_count = 0;
}

void group_subtest(int ok, const char *fmt, ...)
{
    if (g_sub_count >= MAX_SUBTESTS) return;
    size_t i = g_sub_count;
    g_subs[i].idx = i + 1;
    g_subs[i].ok = ok;
    g_subs[i].detail = NULL;

    if (!ok && fmt)
    {
        va_list ap;
        va_start(ap, fmt);
        char tmp[512];
        vsnprintf(tmp, sizeof(tmp), fmt, ap);
        va_end(ap);
        g_subs[i].detail = strdup(tmp);
    }
    g_sub_count++;
}

/* finish group: print grouped line then detailed failures, return failures count */
size_t group_finish()
{
    /* Print compact group header + statuses */
	printf("\n%s%-12s%s:", CLR_CYAN, g_group_name ? g_group_name : "(unknown)", CLR_RESET);
    flush_sleep();
    for (size_t i = 0; i < g_sub_count; ++i)
    {
		if (g_subs[i].ok)
            printf(" %s%ld.OK%s%s ", CLR_GREEN, g_subs[i].idx, SYMBOL_OK, CLR_RESET);
        else
            printf(" %s%ld.KO%s%s ", CLR_RED, g_subs[i].idx, SYMBOL_KO, CLR_RESET);
        flush_sleep();
    }
    
    /* Print details for failures (one-by-one) */
    size_t failures = 0;
    size_t has_errors = 0;
    for (size_t i = 0; i < g_sub_count; ++i)
    {
        if (!g_subs[i].ok)
        {
            failures++;
			has_errors = 1;
			printf(INDENT "\n%s%s (%ld):%s %s", CLR_YELLOW, g_group_name, g_subs[i].idx, CLR_RESET,
                   g_subs[i].detail ? g_subs[i].detail : "failed");
            free(g_subs[i].detail);
            g_subs[i].detail = NULL;
        }
    }
	if (has_errors) printf("\n");
    return failures;
}
