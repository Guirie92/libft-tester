/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_putendl_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:02:14 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 22:22:52 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../libft.h"

/* reference implementation */
static void putendl_fd(char *s, int fd)
{
	if (!s)
		return;
	else if (*s)
		write(fd, s, strlen(s));
	write(fd, "\n", 1);
}

size_t group_putendl_fd(void)
{
	group_start("putendl_fd");

	fflush(stdout);
	
	/* helper function to capture fd output */
	char buf_expected[8000], buf_got[8000];
	ssize_t n;
	int pipefd[2];

	/* subtest 1: basic string */
	{
		const char *s = "hello";
		pipe(pipefd);
		putendl_fd((char *)s, pipefd[1]);
		close(pipefd[1]);
		n = read(pipefd[0], buf_expected, sizeof(buf_expected)-1);
		buf_expected[n] = '\0';
		close(pipefd[0]);

		pipe(pipefd);
		ft_putendl_fd((char *)s, pipefd[1]);
		close(pipefd[1]);
		n = read(pipefd[0], buf_got, sizeof(buf_got)-1);
		buf_got[n] = '\0';
		close(pipefd[0]);

		if (strcmp(buf_expected, buf_got) == 0) SUBTEST_OK();
		else SUBTEST_FAILF("diff: expected='%s' | got='%s'", buf_expected, buf_got);
	}

	/* subtest 2: empty string */
	{
		const char *s = "";
		pipe(pipefd);
		putendl_fd((char *)s, pipefd[1]);
		close(pipefd[1]);
		n = read(pipefd[0], buf_expected, sizeof(buf_expected)-1);
		buf_expected[n] = '\0';
		close(pipefd[0]);

		pipe(pipefd);
		ft_putendl_fd((char *)s, pipefd[1]);
		close(pipefd[1]);
		n = read(pipefd[0], buf_got, sizeof(buf_got)-1);
		buf_got[n] = '\0';
		close(pipefd[0]);

		if (strcmp(buf_expected, buf_got) == 0) SUBTEST_OK();
		else SUBTEST_FAILF("diff: expected='%s' | got='%s'", buf_expected, buf_got);
	}

	/* subtest 3: NULL string */
	{
		char *s = NULL;
		pipe(pipefd);
		putendl_fd(s, pipefd[1]);
		close(pipefd[1]);
		n = read(pipefd[0], buf_expected, sizeof(buf_expected)-1);
		buf_expected[n] = '\0';
		close(pipefd[0]);

		pipe(pipefd);
		ft_putendl_fd(s, pipefd[1]);
		close(pipefd[1]);
		n = read(pipefd[0], buf_got, sizeof(buf_got)-1);
		buf_got[n] = '\0';
		close(pipefd[0]);

		if (strcmp(buf_expected, buf_got) == 0) SUBTEST_OK();
		else SUBTEST_FAILF("diff: expected='%s' | got='%s'", buf_expected, buf_got);
	}

	/* subtest 4: multibyte UTF-8 string */
	{
		const char *s = "éå漢";
		pipe(pipefd);
		putendl_fd((char *)s, pipefd[1]);
		close(pipefd[1]);
		n = read(pipefd[0], buf_expected, sizeof(buf_expected)-1);
		buf_expected[n] = '\0';
		close(pipefd[0]);

		pipe(pipefd);
		ft_putendl_fd((char *)s, pipefd[1]);
		close(pipefd[1]);
		n = read(pipefd[0], buf_got, sizeof(buf_got)-1);
		buf_got[n] = '\0';
		close(pipefd[0]);

		if (strcmp(buf_expected, buf_got) == 0) SUBTEST_OK();
		else SUBTEST_FAILF("diff: expected='%s' | got='%s'", buf_expected, buf_got);
	}

	/* subtest 5: very long string */
	{
		char *s = malloc(9000);
		for (size_t i = 0; i < 8000; i++)
			s[i] = 'a';
		s[8000] = '\0';

		pipe(pipefd);
		putendl_fd(s, pipefd[1]);
		close(pipefd[1]);
		n = read(pipefd[0], buf_expected, sizeof(buf_expected)-1);
		buf_expected[n] = '\0';
		close(pipefd[0]);

		pipe(pipefd);
		ft_putendl_fd(s, pipefd[1]);
		close(pipefd[1]);
		n = read(pipefd[0], buf_got, sizeof(buf_got)-1);
		buf_got[n] = '\0';
		close(pipefd[0]);

		if (strcmp(buf_expected, buf_got) == 0) SUBTEST_OK();
		else SUBTEST_FAILF("diff: expected[0..10]='%.10s' | got[0..10]='%.10s'", buf_expected, buf_got);

		free(s);
	}
	fflush(stdout);
	
	return group_finish();
}
