/*Question - In the town of Graphville, there is a quick courier named Lexi who needs to deliver packages to
several businesses located in various districts. Graphville is well-connected, but Lexi wants to ensure the
route taken is not only efficient but also predictable in order, so her dispatch team can easily track her progress.
Lexi decides to always take the lexicographically smallest path that visits each district exactly once and
returns to the starting district. As a budding programmer, you are tasked with helping Lexi find this path using a program.
Input Format- The first line contains an integer n (2 ≤ n ≤ 10), the number of districts.
Each of the next n lines contains n integers, where the j-th integer in the i-th line represents the travel
cost from district i to district j. If the number is -1, it means that the path between the two districts
does not exist.
Output Format- Output the lexicographically smallest path (as a sequence of district indices) that visits
each district exactly once and returns to the starting district. If the path does not exist, return -1
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// swaps two integer values
void swap_values(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// reverses an array from start index to end index
void reverse_array(int arr[], int start, int end)
{
    while (start < end)
    {
        swap_values(&arr[start], &arr[end]);
        start++;
        end--;
    }
}

// generates the next permutation of the array
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
    // finds the next greater element to swap
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

// calculates the cost of a given route
int compute_cost(int n, int **matrix, int route[])
{
    int cost = 0;

    // iterates through the path and adds the corresponding costs
    for (int i = 0; i < n - 1; i++)
    {
        if (matrix[route[i]][route[i + 1]] == -1)
        {
            return -1;
        }
        cost += matrix[route[i]][route[i + 1]];
    }

    // adds cost to return to the starting city
    if (matrix[route[n - 1]][route[0]] == -1)
    {
        return -1;
    }
    cost += matrix[route[n - 1]][route[0]];
    return cost;
}

// finds the minimum cost route for the traveling salesman problem
void find_min_cost(int n, int **matrix, int *opt_cost, int best_route[])
{
    int route[n];

    // initializes the route with cities in order
    for (int i = 0; i < n; i++)
    {
        route[i] = i;
    }

    *opt_cost = INT_MAX;

    // tries all permutations to find the optimal route
    do
    {
        int cur_cost = compute_cost(n, matrix, route);

        // updates the best route if a lower cost is found
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

    // allocates memory for the adjacency matrix
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }

    // takes input for the adjacency matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    int opt_cost;
    int best_route[n];

    // finds the optimal path and minimum cost
    find_min_cost(n, matrix, &opt_cost, best_route);

    // prints the result
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

    // frees allocated memory
    for (int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
