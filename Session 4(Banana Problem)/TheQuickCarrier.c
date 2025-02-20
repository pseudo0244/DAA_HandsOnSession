#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

void swap_values(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverse_array(int arr[], int start, int end)
{
    while (start < end)
    {
        swap_values(&arr[start], &arr[end]);
        start++;
        end--;
    }
}

bool get_next_perm(int arr[], int size)
{
    int idx = -1;
    for (int i = size - 2; i >= 0; i--)
    {
        if (arr[i] < arr[i + 1])
        {
            idx = i;
            break;
        }
    }

    if (idx == -1)
    {
        return false;
    }

    int swap_idx = -1;
    for (int i = size - 1; i > idx; i--)
    {
        if (arr[i] > arr[idx])
        {
            swap_idx = i;
            break;
        }
    }

    swap_values(&arr[idx], &arr[swap_idx]);
    reverse_array(arr, idx + 1, size - 1);
    return true;
}

int compute_cost(int n, int **matrix, int route[])
{
    int cost = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (matrix[route[i]][route[i + 1]] == -1)
        {
            return -1;
        }
        cost += matrix[route[i]][route[i + 1]];
    }

    if (matrix[route[n - 1]][route[0]] == -1)
    {
        return -1;
    }
    cost += matrix[route[n - 1]][route[0]];
    return cost;
}

void find_min_cost(int n, int **matrix, int *opt_cost, int best_route[])
{
    int route[n];
    for (int i = 0; i < n; i++)
    {
        route[i] = i;
    }
    *opt_cost = INT_MAX;

    do
    {
        int cur_cost = compute_cost(n, matrix, route);
        if (cur_cost != -1 && cur_cost < *opt_cost)
        {
            *opt_cost = cur_cost;
            for (int i = 0; i < n; i++)
            {
                best_route[i] = route[i];
            }
        }
    } while (get_next_perm(route, n));
}

int main()
{
    int n;
    scanf("%d", &n);

    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    int opt_cost;
    int best_route[n];
    find_min_cost(n, matrix, &opt_cost, best_route);

    if (opt_cost == INT_MAX)
    {
        printf("\npath doesn't exist\n");
    }
    else
    {
        printf("\nminimum cost: %d\n", opt_cost);
        printf("optimal path: ");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", best_route[i]);
        }
        printf("%d\n", best_route[0]);
    }

    for (int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}