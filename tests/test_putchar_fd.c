/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_putchar_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:01:40 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 22:22:49 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "../../libft.h"

size_t group_putchar_fd(void)
{
	group_start("putchar_fd");

    fflush(stdout);

    /* subtest 1: basic character to stdout */
    {
        //int fd = STDOUT_FILENO;
        char c = 'A';
        
        // We'll test by redirecting stdout to a file and comparing
        int pipefd[2];
        pipe(pipefd);
        
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        
        ft_putchar_fd(c, STDOUT_FILENO);
        fflush(stdout);
        
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        close(pipefd[1]);
        
        char buf[2] = {0};
        read(pipefd[0], buf, 1);
        close(pipefd[0]);
        
        if (buf[0] == c) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%c' | got='%c'", c, buf[0]);
    }

    /* subtest 2: special characters (newline) */
    {
        int pipefd[2];
        pipe(pipefd);
        
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        
        ft_putchar_fd('\n', STDOUT_FILENO);
        fflush(stdout);
        
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        close(pipefd[1]);
        
        char buf[2] = {0};
        read(pipefd[0], buf, 1);
        close(pipefd[0]);
        
        if (buf[0] == '\n') SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='\\n' | got='%c'", buf[0]);
    }

    /* subtest 3: null character */
    {
        int pipefd[2];
        pipe(pipefd);
        
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        
        ft_putchar_fd('\0', STDOUT_FILENO);
        fflush(stdout);
        
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        close(pipefd[1]);
        
        char buf[2] = {0};
        read(pipefd[0], buf, 1);
        close(pipefd[0]);
        
        if (buf[0] == '\0') SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='\\0' | got='%c'", buf[0]);
    }

    /* subtest 4: write to stderr */
    {
        int pipefd[2];
        pipe(pipefd);
        
        int saved_stderr = dup(STDERR_FILENO);
        dup2(pipefd[1], STDERR_FILENO);
        
        ft_putchar_fd('E', STDERR_FILENO);
        fflush(stderr);
        
        dup2(saved_stderr, STDERR_FILENO);
        close(saved_stderr);
        close(pipefd[1]);
        
        char buf[2] = {0};
        read(pipefd[0], buf, 1);
        close(pipefd[0]);
        
        if (buf[0] == 'E') SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='E' | got='%c'", buf[0]);
    }

    /* subtest 5: write to file descriptor */
    {
        char filename[] = "/tmp/test_putchar_fd_XXXXXX";
        int fd = mkstemp(filename);
        
        ft_putchar_fd('X', fd);
        close(fd);
        
        fd = open(filename, O_RDONLY);
        char buf[2] = {0};
        read(fd, buf, 1);
        close(fd);
        unlink(filename);
        
        if (buf[0] == 'X') SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='X' | got='%c'", buf[0]);
    }
    fflush(stdout);
    return group_finish();
}
