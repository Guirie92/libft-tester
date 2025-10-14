/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tester.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:57:30 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 20:07:57 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/test_framework.h"
#include <stdio.h>
#include <string.h>

/* registry: name -> runner function
 * The same names are the ones shown on the command line/output.
 */
typedef int (*t_groupfn)(void);
typedef struct s_group
{
	const char *name;
	t_groupfn fn;
}  	t_group;

static t_group g_groups[] =
{
	{ "isalpha",		group_isalpha		},
	{ "isdigit",		group_isdigit		},
	{ "isalnum",		group_isalnum		},
	{ "isascii",		group_isascii		},
	{ "isprint",		group_isprint		},
	{ "strlen",			group_strlen		},
	{ "memset",			group_memset 		},
	{ "bzero",			group_bzero 		},
	{ "memcpy",			group_memcpy		},
	{ "memmove",		group_memmove		},
	{ "strlcpy",		group_strlcpy		},
	{ "strlcat",		group_strlcat		},
	{ "toupper",		group_toupper		},
	{ "tolower",		group_tolower		},
	{ "strchr",			group_strchr 		},
	{ "strrchr",		group_strrchr		},
	{ "strncmp",		group_strncmp		},
	{ "memchr",			group_memchr		},
	{ "memcmp",			group_memcmp		},
	{ "strnstr",		group_strnstr		},
	{ "atoi",			group_atoi			},
	{ "calloc",			group_calloc		},
	{ "strdup",			group_strdup		},
	{ "substr",			group_substr		},
	{ "strjoin",		group_strjoin		},
	{ "strtrim",		group_strtrim		},
	{ "split",			group_split			},
	{ "itoa",			group_itoa			},
	{ "strmapi",		group_strmapi		},
	{ "striteri",		group_striteri		},
	{ "putchar_fd",		group_putchar_fd	},
	{ "putstr_fd",		group_putstr_fd		},
	{ "putendl_fd",		group_putendl_fd	},
	{ "putnbr_fd",		group_putnbr_fd		},
#ifdef HAVE_BONUS
	{ "lstnew",			group_lstnew		},
	{ "lstadd_front",	group_lstadd_front	},
	{ "lstsize",		group_lstsize		},
	{ "lstlast",		group_lstlast		},
	{ "lstadd_back",	group_lstadd_back	},
	{ "lstdelone",		group_lstdelone		},
	{ "lstclear",		group_lstclear		},
	{ "lstiter",		group_lstiter		},
	{ "lstmap",			group_lstmap		},
#endif
};

static const int g_groups_count = sizeof(g_groups) / sizeof(g_groups[0]);

int main(int argc, char **argv)
{
	
	int total_failures = 0;
	size_t functions_passed = 0;
	size_t run_all = (argc == 1);

	for (size_t i = 0; i < g_groups_count; ++i)
	{
		const char *gname = g_groups[i].name;
		int should_run = run_all;
		if (!run_all)
		{
			for (int a = 1; a < argc; ++a)
				if (strcmp(argv[a], gname) == 0) { should_run = 1; break; }
		}
		if (!should_run)
			continue;

		total_failures += g_groups[i].fn();
		functions_passed++;
	}

	if (total_failures == 0)
		printf("\n\n" CLR_GREEN "All tests passed (%d)\n\n" CLR_RESET, functions_passed);
	else
		printf("\n\n" CLR_RED "Tests failed: %d\n\n" CLR_RESET, total_failures);

	return (total_failures == 0 ? 0 : 1);
}
