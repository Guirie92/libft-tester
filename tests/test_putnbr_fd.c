/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_putnbr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:02:28 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 20:43:19 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include "../../libft.h"

/* reference implementation for comparison */
static void putnbr_fd(int n, int fd)
{
    char c;

    if (n == INT_MIN)
    {
        write(fd, "-2147483648", 11);
        return;
    }
    if (n < 0)
    {
        write(fd, "-", 1);
        n *= -1;
    }
    if (n >= 10)
        putnbr_fd(n / 10, fd);
    c = n % 10 + '0';
    write(fd, &c, 1);
}

int group_putnbr_fd(void)
{
	group_start("putnbr_fd");
    fflush(stdout);
    
    /* subtest 1: basic positive number */
    {
        int pipefd[2];
        pipe(pipefd);
        
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        
        ft_putnbr_fd(42, STDOUT_FILENO);
        fflush(stdout);
        
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        close(pipefd[1]);
        
        char buf[10] = {0};
        read(pipefd[0], buf, 9);
        close(pipefd[0]);
        
        if (strcmp(buf, "42") == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='42' | got='%s'", buf);
    }

    /* subtest 2: basic negative number */
    {
        int pipefd[2];
        pipe(pipefd);
        
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        
        ft_putnbr_fd(-42, STDOUT_FILENO);
        fflush(stdout);
        
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        close(pipefd[1]);
        
        char buf[10] = {0};
        read(pipefd[0], buf, 9);
        close(pipefd[0]);
        
        if (strcmp(buf, "-42") == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='-42' | got='%s'", buf);
    }

    /* subtest 3: zero */
    {
        int pipefd[2];
        pipe(pipefd);
        
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        
        ft_putnbr_fd(0, STDOUT_FILENO);
        fflush(stdout);
        
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        close(pipefd[1]);
        
        char buf[10] = {0};
        read(pipefd[0], buf, 9);
        close(pipefd[0]);
        
        if (strcmp(buf, "0") == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='0' | got='%s'", buf);
    }

    /* subtest 4: INT_MAX */
    {
        int pipefd[2];
        pipe(pipefd);
        
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        
        ft_putnbr_fd(INT_MAX, STDOUT_FILENO);
        fflush(stdout);
        
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        close(pipefd[1]);
        
        char buf[15] = {0};
        read(pipefd[0], buf, 14);
        close(pipefd[0]);
        
        if (strcmp(buf, "2147483647") == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='2147483647' | got='%s'", buf);
    }

    /* subtest 5: INT_MIN */
    {
        int pipefd[2];
        pipe(pipefd);
        
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        
        ft_putnbr_fd(INT_MIN, STDOUT_FILENO);
        fflush(stdout);
        
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        close(pipefd[1]);
        
        char buf[15] = {0};
        read(pipefd[0], buf, 14);
        close(pipefd[0]);
        
        if (strcmp(buf, "-2147483648") == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='-2147483648' | got='%s'", buf);
    }

    /* subtest 6: single digit positive */
    {
        int pipefd[2];
        pipe(pipefd);
        
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        
        ft_putnbr_fd(7, STDOUT_FILENO);
        fflush(stdout);
        
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        close(pipefd[1]);
        
        char buf[10] = {0};
        read(pipefd[0], buf, 9);
        close(pipefd[0]);
        
        if (strcmp(buf, "7") == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='7' | got='%s'", buf);
    }

    /* subtest 7: single digit negative */
    {
        int pipefd[2];
        pipe(pipefd);
        
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        
        ft_putnbr_fd(-9, STDOUT_FILENO);
        fflush(stdout);
        
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        close(pipefd[1]);
        
        char buf[10] = {0};
        read(pipefd[0], buf, 9);
        close(pipefd[0]);
        
        if (strcmp(buf, "-9") == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='-9' | got='%s'", buf);
    }

    /* subtest 8: large positive number */
    {
        int pipefd[2];
        pipe(pipefd);
        
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        
        ft_putnbr_fd(123456789, STDOUT_FILENO);
        fflush(stdout);
        
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        close(pipefd[1]);
        
        char buf[15] = {0};
        read(pipefd[0], buf, 14);
        close(pipefd[0]);
        
        if (strcmp(buf, "123456789") == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='123456789' | got='%s'", buf);
    }

    /* subtest 9: large negative number */
    {
        int pipefd[2];
        pipe(pipefd);
        
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        
        ft_putnbr_fd(-987654321, STDOUT_FILENO);
        fflush(stdout);
        
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        close(pipefd[1]);
        
        char buf[15] = {0};
        read(pipefd[0], buf, 14);
        close(pipefd[0]);
        
        if (strcmp(buf, "-987654321") == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='-987654321' | got='%s'", buf);
    }

    /* subtest 10: write to file descriptor */
    {
        char filename[] = "/tmp/test_putnbr_fd_XXXXXX";
        int fd = mkstemp(filename);
        
        ft_putnbr_fd(12345, fd);
        close(fd);
        
        fd = open(filename, O_RDONLY);
        char buf[10] = {0};
        read(fd, buf, 9);
        close(fd);
        unlink(filename);
        
        if (strcmp(buf, "12345") == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='12345' | got='%s'", buf);
    }

    /* subtest 11: write to stderr */
    {
        int pipefd[2];
        pipe(pipefd);
        
        int saved_stderr = dup(STDERR_FILENO);
        dup2(pipefd[1], STDERR_FILENO);
        
        ft_putnbr_fd(999, STDERR_FILENO);
        fflush(stderr);
        
        dup2(saved_stderr, STDERR_FILENO);
        close(saved_stderr);
        close(pipefd[1]);
        
        char buf[10] = {0};
        read(pipefd[0], buf, 9);
        close(pipefd[0]);
        
        if (strcmp(buf, "999") == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='999' | got='%s'", buf);
    }

    /* subtest 12: comparison with reference implementation */
    {
        int pipefd1[2], pipefd2[2];
        pipe(pipefd1);
        pipe(pipefd2);
        
        int saved_stdout = dup(STDOUT_FILENO);
        
        // Test ft_putnbr_fd
        dup2(pipefd1[1], STDOUT_FILENO);
        ft_putnbr_fd(-123456, STDOUT_FILENO);
        fflush(stdout);
        
        // Test putnbr_fd
        dup2(pipefd2[1], STDOUT_FILENO);
        putnbr_fd(-123456, STDOUT_FILENO);
        fflush(stdout);
        
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        close(pipefd1[1]);
        close(pipefd2[1]);
        
        char buf1[15] = {0};
        char buf2[15] = {0};
        read(pipefd1[0], buf1, 14);
        read(pipefd2[0], buf2, 14);
        close(pipefd1[0]);
        close(pipefd2[0]);
        
        if (strcmp(buf1, buf2) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: reference='%s' | ft='%s'", buf2, buf1);
    }
    fflush(stdout);

    return group_finish();
}
