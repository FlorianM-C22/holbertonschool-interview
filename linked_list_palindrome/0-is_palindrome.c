#include "lists.h"

/**
 * reverse_list - Reverses a linked list
 * @head: Pointer to the head of the list
 * Return: Pointer to the new head of the reversed list
 */
listint_t *reverse_list(listint_t *head)
{
    listint_t *prev = NULL;
    listint_t *current = head;
    listint_t *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

/**
 * is_palindrome - Checks if a singly linked list is a palindrome
 * @head: Double pointer to the head of the list
 * Return: 1 if palindrome, 0 if not
 */
int is_palindrome(listint_t **head)
{
    listint_t *slow = *head;
    listint_t *fast = *head;
    listint_t *second_half;
    listint_t *prev_slow = *head;
    int is_pal = 1;

    if (*head == NULL || (*head)->next == NULL)
        return (1);

    /* Find the middle of the list */
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        prev_slow = slow;
        slow = slow->next;
    }

    /* Handle odd length */
    if (fast != NULL)
        slow = slow->next;

    /* Reverse the second half */
    second_half = reverse_list(slow);
    prev_slow->next = NULL;

    /* Compare first and second half */
    while (*head != NULL && second_half != NULL)
    {
        if ((*head)->n != second_half->n)
        {
            is_pal = 0;
            break;
        }
        *head = (*head)->next;
        second_half = second_half->next;
    }

    /* Restore the list */
    prev_slow->next = reverse_list(second_half);

    return (is_pal);
}