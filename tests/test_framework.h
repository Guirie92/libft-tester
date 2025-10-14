/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_framework.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:06:33 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 20:17:48 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_FRAMEWORK_H
# define TEST_FRAMEWORK_H

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
int  group_finish();

/* convenience macros */
# define SUBTEST_OK()            (group_subtest(1, NULL))
# define SUBTEST_FAILF(...)      (group_subtest(0, __VA_ARGS__))

int group_isalpha(void);
int group_isdigit(void);
int group_isalnum(void);
int group_isascii(void);
int group_isprint(void);
int group_strlen(void);
int group_memset(void);
int group_bzero(void);
int group_memcpy(void);
int group_memmove(void);
int group_strlcpy(void);
int group_strlcat(void);
int group_toupper(void);
int group_tolower(void);
int group_strchr(void);
int group_strrchr(void);
int group_strncmp(void);
int group_memchr(void);
int group_memcmp(void);
int group_strnstr(void);
int group_atoi(void);
int group_calloc(void);
int group_strdup(void);
int group_substr(void);
int group_strjoin(void);
int group_strtrim(void);
int group_split(void);
int group_itoa(void);
int group_strmapi(void);
int group_striteri(void);
int group_putchar_fd(void);
int group_putstr_fd(void);
int group_putendl_fd(void);
int group_putnbr_fd(void);

int group_lstnew(void);
int group_lstadd_front(void);
int group_lstsize(void);
int group_lstlast(void);
int group_lstadd_back(void);
int group_lstdelone(void);
int group_lstclear(void);
int group_lstiter(void);
int group_lstmap(void);

#endif /* TEST_FRAMEWORK_H */
