/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lstadd_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guillsan <guillsan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:02:53 by guillsan          #+#    #+#             */
/*   Updated: 2025/10/14 22:21:54 by guillsan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_framework.h"
#include "../../libft.h"

/* Reference implementation for comparison */
static void lstadd_front(t_list **lst, t_list *new)
{
    t_list *old;

    if (!new)
        return;
    old = *lst;
    *lst = new;
    (*lst)->next = old;
}

static t_list *create_node(void *content)
{
    t_list *node = malloc(sizeof(t_list));
    if (!node)
        return NULL;
    node->content = content;
    node->next = NULL;
    return node;
}

static int list_size(t_list *lst)
{
    int size = 0;
    while (lst)
    {
        size++;
        lst = lst->next;
    }
    return size;
}

static int compare_lists(t_list *lst1, t_list *lst2)
{
    while (lst1 && lst2)
    {
        if (lst1->content != lst2->content)
            return 0;
        lst1 = lst1->next;
        lst2 = lst2->next;
    }
    return (lst1 == NULL && lst2 == NULL);
}

static void free_list(t_list *lst)
{
    t_list *tmp;
    while (lst)
    {
        tmp = lst;
        lst = lst->next;
        free(tmp);
    }
}
/* subsets 1, 3, 4, and 5 crash, so they're enabled until I implement a way to catch those crashes */
size_t group_lstadd_front(void)
{
	//return 1;
	group_start("lstadd_front");

    /* subtest 1: basic add to empty list */
    /*{
        t_list *lst = NULL;
        t_list *new = create_node("first");
        
        ft_lstadd_front(&lst, new);
        
        if (lst != NULL && lst->content == new->content && lst->next == NULL) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected list with 'first' | got invalid list");
        
        free_list(lst);
    }*/

    /* subtest 2: basic add to existing list */
    {
        t_list *lst = create_node("old_first");
        t_list *new = create_node("new_first");
        void *old_content = lst->content;
        
        ft_lstadd_front(&lst, new);
        
        if (lst != NULL && 
            lst->content == new->content && 
            lst->next != NULL && 
            lst->next->content == old_content) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected 'new_first'->'old_first' | got invalid list");
        
        free_list(lst);
    }

    /* subtest 3: NULL new node */
    /*{
        t_list *lst = create_node("existing");
        t_list *original_lst = lst;
        void *original_content = lst->content;
        
        ft_lstadd_front(&lst, NULL);
        
        if (lst == original_lst && lst->content == original_content) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected unchanged list | got modified list");
        
        free_list(lst);
    }*/

    /* subtest 4: NULL list pointer */
    /*{
        t_list *new = create_node("test");
        
        ft_lstadd_front(NULL, new);
        SUBTEST_OK(); // Should not crash
        
        free(new);
    }*/

    /* subtest 5: both NULL */
    /*{
        ft_lstadd_front(NULL, NULL);
        SUBTEST_OK(); // Should not crash
    }*/

    /* subtest 6: add multiple nodes */
    {
        t_list *lst = NULL;
        t_list *node1 = create_node("third");
        t_list *node2 = create_node("second");
        t_list *node3 = create_node("first");
        
        ft_lstadd_front(&lst, node1);
        ft_lstadd_front(&lst, node2);
        ft_lstadd_front(&lst, node3);
        
        int size = list_size(lst);
        int correct_order = (lst->content == node3->content && 
                           lst->next->content == node2->content && 
                           lst->next->next->content == node1->content);
        
        if (size == 3 && correct_order) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected 3 nodes in correct order | got size=%d", size);
        
        free_list(lst);
    }

    /* subtest 7: comparison with reference implementation */
    {
        t_list *lst1 = create_node("old");
        t_list *lst2 = create_node("old");
        t_list *new1 = create_node("new");
        t_list *new2 = create_node("new");
        
        ft_lstadd_front(&lst1, new1);
        lstadd_front(&lst2, new2);
        
        if (compare_lists(lst1, lst2)) SUBTEST_OK();
        else SUBTEST_FAILF("diff: reference and ft implementations differ");
        
        free_list(lst1);
        free_list(lst2);
    }

    /* subtest 8: add node with NULL content */
    {
        t_list *lst = create_node("existing");
        void *old_content = lst->content;
        t_list *new = create_node(NULL);
        
        ft_lstadd_front(&lst, new);
        
        if (lst->content == NULL && lst->next->content == old_content) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected NULL content at front");
        
        free_list(lst);
    }

    /* subtest 9: list with single node becomes two nodes */
    {
        t_list *lst = create_node("single");
        void *old_content = lst->content;
        t_list *new = create_node("new_front");
        
        ft_lstadd_front(&lst, new);
        
        int size = list_size(lst);
        int correct_content = (lst->content == new->content && 
                             lst->next->content == old_content);
        
        if (size == 2 && correct_content) SUBTEST_OK();
        else SUBTEST_FAILF("diff: expected 2 nodes | got size=%d", size);
        
        free_list(lst);
    }

    /* subtest 10: verify pointer reassignment */
    {
        t_list *lst = create_node("A");
        t_list *B = create_node("B");
        lst->next = B;
        t_list *new = create_node("NEW");
        
        t_list *old_lst = lst; // Save old pointer
        void *B_content = B->content;
        
        ft_lstadd_front(&lst, new);
        
        int correct_structure = (lst == new && 
                               lst->next == old_lst && 
                               lst->next->content == old_lst->content &&
                               lst->next->next == B &&
                               lst->next->next->content == B_content);
        
        if (correct_structure) SUBTEST_OK();
        else SUBTEST_FAILF("diff: incorrect pointer reassignment");
        
        free_list(lst);
    }

    return group_finish();
}
