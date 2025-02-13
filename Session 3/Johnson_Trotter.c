/*You are given an array ‘nums’ containing distinct elements, an array ‘dir’ of the same length representing the initial direction of each element, and an integer k. Your task is to find the k-th next permutation in Johnson-Trotter order starting from the given permutation. If no such permutation exists print ‘Permutation does not exist’.

The Johnson-Trotter algorithm is used to generate permutations by identifying the largest mobile element—A directed integer is said to be mobile if it is greater than its immediate neighbor in the direction it is looking at.—and swapping it with its adjacent element. Further the directions of all the elements greater than the mobile element is reversed. The process is repeated to generate successive permutations.

Your task is to implement this algorithm and determine the k-th next permutation after performing k iterations from the given state.

Input Format

The first line contains an integer n (size of the array).
The second line contains n space-separated distinct integers representing the array nums.
The third line contains n space-separated integers (0 or 1) representing the array dir, where:
0 indicates the element is moving left.
1 indicates the element is moving right.
The fourth line contains an integer k, representing the number of steps to generate the k-th next permutation.
Constraints

1 ≤ n ≤ 10 1 ≤ each element in nums ≤ 100 nums contains distinct elements. 1 ≤ k ≤ min(100,n!)

Output Format

Print n space-separated integers representing the k-th permutation after performing k iterations using the Johnson-Trotter algorithm.
‘Permutation does not exist’ if it is not possible to find the k-th permutation from the current permutation  */

#include <stdio.h>
#include <stdbool.h>

// Function to find the largest mobile element's index
int findLargestMobile(int n, int nums[], int dir[])
{
    int mobileIndex = -1;
    int largestMobile = -1;

    for (int i = 0; i < n; i++)
    {
        int neighborIndex = (dir[i] == 0) ? i - 1 : i + 1; // Left or right neighbor

        if (neighborIndex >= 0 && neighborIndex < n && nums[i] > nums[neighborIndex])
        {
            if (nums[i] > largestMobile)
            {
                largestMobile = nums[i];
                mobileIndex = i;
            }
        }
    }
    return mobileIndex;
}

// Function to swap two elements
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to generate the next permutation using Johnson-Trotter algorithm
bool generateNextPermutation(int n, int nums[], int dir[])
{
    int mobileIndex = findLargestMobile(n, nums, dir);
    if (mobileIndex == -1)
    {
        return false; // No mobile element found, meaning no more permutations exist
    }

    int moveTo = (dir[mobileIndex] == 0) ? mobileIndex - 1 : mobileIndex + 1;

    // Swap the mobile element with the adjacent element in its direction
    swap(&nums[mobileIndex], &nums[moveTo]);
    swap(&dir[mobileIndex], &dir[moveTo]);

    // Reverse the direction of all elements greater than the moved element
    for (int i = 0; i < n; i++)
    {
        if (nums[i] > nums[moveTo])
        {
            dir[i] = 1 - dir[i]; // Flip direction
        }
    }

    return true;
}

// Function to compute the k-th permutation
void johnsonTrotter(int n, int nums[], int dir[], int k)
{
    for (int i = 0; i < k; i++)
    {
        if (!generateNextPermutation(n, nums, dir))
        {
            printf("Permutation does not exist\n");
            return;
        }
    }

    // Print the k-th permutation
    for (int i = 0; i < n; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

// Driver function
int main()
{
    int n, k;

    scanf("%d", &n);
    int nums[n], dir[n];

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &nums[i]);
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &dir[i]);
    }

    scanf("%d", &k);

    johnsonTrotter(n, nums, dir, k);

    return 0;
}
