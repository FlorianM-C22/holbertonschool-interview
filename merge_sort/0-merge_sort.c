#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

/**
 * print_subarray - Prints a subarray with a label
 *
 * @label: Label to print before the subarray
 * @array: The array to print from
 * @low: Starting index
 * @high: Ending index
 */
void print_subarray(char *label, int *array, int low, int high)
{
	int i;
	char *sep;

	printf("[%s]: ", label);
	sep = "";
	for (i = low; i <= high; i++)
	{
		printf("%s%d", sep, array[i]);
		sep = ", ";
	}
	printf("\n");
}

/**
 * merge - Merges two sorted subarrays
 *
 * @array: The array to merge in
 * @low: Starting index of the left subarray
 * @mid: Ending index of the left subarray
 * @high: Ending index of the right subarray
 * @buffer: Auxiliary buffer for merging
 */
void merge(int *array, int low, int mid, int high, int *buffer)
{
	int left, right, i;

	left = i = low;
	right = mid + 1;

	printf("Merging...\n");
	print_subarray("left", array, low, mid);
	print_subarray("right", array, mid + 1, high);

	while (left <= mid && right <= high)
	{
		if (array[left] < array[right])
			buffer[i++] = array[left++];
		else
			buffer[i++] = array[right++];
	}

	while (left <= mid)
		buffer[i++] = array[left++];

	while (right <= high)
		buffer[i++] = array[right++];

	for (i = low; i <= high; i++)
		array[i] = buffer[i];

	print_subarray("Done", array, low, high);
}

/**
 * sort_subarray - Recursively sorts a subarray
 *
 * @array: The array to sort
 * @low: Starting index
 * @high: Ending index
 * @buffer: Auxiliary buffer for merging
 */
void sort_subarray(int *array, int low, int high, int *buffer)
{
	int mid;

	if (low < high)
	{
		mid = (low + high - 1) / 2;
		sort_subarray(array, low, mid, buffer);
		sort_subarray(array, mid + 1, high, buffer);
		merge(array, low, mid, high, buffer);
	}
}

/**
 * merge_sort - Sorts an array of integers in ascending order
 *              using the merge sort algorithm
 *
 * @array: The array to be sorted
 * @size: Number of elements in @array
 */
void merge_sort(int *array, size_t size)
{
	int *buffer;

	if (size < 2)
		return;

	buffer = malloc(sizeof(int) * size);
	if (!buffer)
		return;

	sort_subarray(array, 0, size - 1, buffer);
	free(buffer);
}
