/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_putstr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:01:52 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 22:22:59 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "../../libft.h"

size_t group_putstr_fd(void)
{
	group_start("putstr_fd");
    fflush(stdout);
    
    /* subtest 1: basic string to stdout */
    {
        int pipefd[2];
        pipe(pipefd);
        
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        
        char *str = "Hello World";
        ft_putstr_fd(str, STDOUT_FILENO);
        fflush(stdout);
        
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        close(pipefd[1]);
        
        char buf[20] = {0};
        read(pipefd[0], buf, strlen(str));
        close(pipefd[0]);
        
        if (strcmp(buf, str) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", str, buf);
    }

    /* subtest 2: empty string */
    {
        int pipefd[2];
        pipe(pipefd);
        
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        
        char *str = "";
        ft_putstr_fd(str, STDOUT_FILENO);
        fflush(stdout);
        
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        close(pipefd[1]);
        
        char buf[2] = {0};
        int bytes_read = read(pipefd[0], buf, 1);
        close(pipefd[0]);
        
        if (bytes_read == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected nothing | got='%s'", buf);
    }

    /* subtest 3: NULL string pointer */
    {
        int pipefd[2];
        pipe(pipefd);
        
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        
        ft_putstr_fd(NULL, STDOUT_FILENO);
        fflush(stdout);
        
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        close(pipefd[1]);
        
        char buf[2] = {0};
        int bytes_read = read(pipefd[0], buf, 1);
        close(pipefd[0]);
        
        if (bytes_read == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected nothing | got='%s'", buf);
    }

    /* subtest 4: string with newlines */
    {
        int pipefd[2];
        pipe(pipefd);
        
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        
        char *str = "Line1\nLine2\nLine3";
        ft_putstr_fd(str, STDOUT_FILENO);
        fflush(stdout);
        
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        close(pipefd[1]);
        
        char buf[30] = {0};
        read(pipefd[0], buf, strlen(str));
        close(pipefd[0]);
        
        if (strcmp(buf, str) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", str, buf);
    }

    /* subtest 5: write to stderr */
    {
        int pipefd[2];
        pipe(pipefd);
        
        int saved_stderr = dup(STDERR_FILENO);
        dup2(pipefd[1], STDERR_FILENO);
        
        char *str = "Error message";
        ft_putstr_fd(str, STDERR_FILENO);
        fflush(stderr);
        
        dup2(saved_stderr, STDERR_FILENO);
        close(saved_stderr);
        close(pipefd[1]);
        
        char buf[20] = {0};
        read(pipefd[0], buf, strlen(str));
        close(pipefd[0]);
        
        if (strcmp(buf, str) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", str, buf);
    }

    /* subtest 6: write to file descriptor */
    {
        char filename[] = "/tmp/test_putstr_fd_XXXXXX";
        int fd = mkstemp(filename);
        
        char *str = "File content";
        ft_putstr_fd(str, fd);
        close(fd);
        
        fd = open(filename, O_RDONLY);
        char buf[20] = {0};
        read(fd, buf, strlen(str));
        close(fd);
        unlink(filename);
        
        if (strcmp(buf, str) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected='%s' | got='%s'", str, buf);
    }

    /* subtest 7: string with special characters */
    {
        int pipefd[2];
        pipe(pipefd);
        
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        
        char *str = "Tab\tBackspace\bNull\0Invisible"; // Note: \0 will terminate
        ft_putstr_fd(str, STDOUT_FILENO);
        fflush(stdout);
        
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        close(pipefd[1]);
        
        char buf[30] = {0};
        read(pipefd[0], buf, 13); // Read up to null terminator
        close(pipefd[0]);
        
        if (memcmp(buf, "Tab\tBackspace\b", 13) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: special characters not handled correctly");
    }

    /* subtest 8: very long string */
    {
        int pipefd[2];
        pipe(pipefd);
        
        int saved_stdout = dup(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        
        char long_str[1000];
        for (int i = 0; i < 999; i++) {
            long_str[i] = 'A' + (i % 26);
        }
        long_str[999] = '\0';
        
        ft_putstr_fd(long_str, STDOUT_FILENO);
        fflush(stdout);
        
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        close(pipefd[1]);
        
        char buf[1000] = {0};
        read(pipefd[0], buf, 999);
        close(pipefd[0]);
        
        if (strcmp(buf, long_str) == 0) SUBTEST_OK();
        else SUBTEST_FAILF("diff: long string mismatch");
    }
    fflush(stdout);

    return group_finish();
}