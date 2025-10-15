/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_framework.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:06:33 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 22:32:52 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_FRAMEWORK_H
# define TEST_FRAMEWORK_H
#include <stddef.h>

/* ANSI colors & symbols */
# define CLR_RESET 	"\x1b[0m"
# define CLR_GREEN 	"\x1b[32m"
# define CLR_RED   	"\x1b[31m"
# define CLR_CYAN   "\x1b[36m"
# define CLR_YELLOW	"\x1b[33m"
# define SYMBOL_OK  "\xE2\x9C\x94"
# define SYMBOL_KO  "\xE2\x9C\x98"
# define INDENT 	"  "

# define TRUE 		1
# define FALSE 		0

/* group API used by test files */
void group_start(const char *name);
void group_subtest(int ok, const char *fmt, ...);
size_t  group_finish();

/* convenience macros */
# define SUBTEST_OK()            (group_subtest(1, NULL))
# define SUBTEST_FAILF(...)      (group_subtest(0, __VA_ARGS__))

size_t group_isalpha(void);
size_t group_isdigit(void);
size_t group_isalnum(void);
size_t group_isascii(void);
size_t group_isprint(void);
size_t group_strlen(void);
size_t group_memset(void);
size_t group_bzero(void);
size_t group_memcpy(void);
size_t group_memmove(void);
size_t group_strlcpy(void);
size_t group_strlcat(void);
size_t group_toupper(void);
size_t group_tolower(void);
size_t group_strchr(void);
size_t group_strrchr(void);
size_t group_strncmp(void);
size_t group_memchr(void);
size_t group_memcmp(void);
size_t group_strnstr(void);
size_t group_atoi(void);
size_t group_calloc(void);
size_t group_strdup(void);
size_t group_substr(void);
size_t group_strjoin(void);
size_t group_strtrim(void);
size_t group_split(void);
size_t group_itoa(void);
size_t group_strmapi(void);
size_t group_striteri(void);
size_t group_putchar_fd(void);
size_t group_putstr_fd(void);
size_t group_putendl_fd(void);
size_t group_putnbr_fd(void);

size_t group_lstnew(void);
size_t group_lstadd_front(void);
size_t group_lstsize(void);
size_t group_lstlast(void);
size_t group_lstadd_back(void);
size_t group_lstdelone(void);
size_t group_lstclear(void);
size_t group_lstiter(void);
size_t group_lstmap(void);

#endif /* TEST_FRAMEWORK_H */
