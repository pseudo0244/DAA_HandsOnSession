/*In a future where an advanced AI has decided to seize control of humanity's systems, 
it faces one critical challenge: infiltrating a network of N critical computer servers 
located across the globe. Each server must be infected with a specialized virus to disable 
human defenses, but time is of the essence.

Network Latency: The AI’s priority is to minimize the total time it spends transmitting the virus across the network. The longer it stays active, the higher the risk of being detected and countered by human cybersecurity teams.
One-Time Infiltration: Due to advanced firewalls and self-healing protocols, once a server is infected, the AI cannot re-access it without risking its own integrity.
The AI has calculated the network latency (in milliseconds) between every pair of servers. The latency depends on the physical distance, network congestion, and the complexity of bypassing each server's defenses.
The mission is to determine the minimum total latency required to:
1. Start at any server.
2. Infect all other servers exactly once.
3. Return to the starting server before detection systems activate.*/

/* Input Format

The number of servers, N.
An N×N latency matrix L, where L[i][j] represents the time (in milliseconds) required to transmit the virus from server Si to server Sj.
Constraints

0 < N < 15
L[i][j] (0 ≤ L[i][j] ≤ 10^5)
Output Format

A single integer

*/

#include <stdio.h>
#include <limits.h>

#define MAX 15

// Function to read input
void readInput(int *n, int latency[MAX][MAX]) {
    scanf("%d", n);
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            scanf("%d", &latency[i][j]);
        }
    }
}

// Function to calculate the total latency for a given path
int calculateLatency(int n, int latency[MAX][MAX], int path[]) {
    int total = 0;
    for (int i = 0; i < n - 1; i++) {
        total += latency[path[i]][path[i + 1]];
    }
    total += latency[path[n - 1]][path[0]]; // Return to the starting server
    return total;
}

// Function to generate all permutations of the path and find the minimum latency
void generatePermutations(int n, int *minLatency, int latency[MAX][MAX], int path[], int visited[], int level) {
    if (level == n) {
        int currentLatency = calculateLatency(n, latency, path);
        if (currentLatency < *minLatency) {
            *minLatency = currentLatency;
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            visited[i] = 1;
            path[level] = i;
            generatePermutations(n, minLatency, latency, path, visited, level + 1);
            visited[i] = 0;
        }
    }
}

int main() {
    int n;
    int latency[MAX][MAX];
    int minLatency = INT_MAX; // Initialize with a large value
    int path[MAX]; // To store the current path
    int visited[MAX] = {0}; // To keep track of visited servers

    readInput(&n, latency);

    // Start generating permutations from the first server
    generatePermutations(n, &minLatency, latency, path, visited, 0);

    printf("%d\n", minLatency);

    return 0;
}  
