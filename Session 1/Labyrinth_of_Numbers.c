#include<stdio.h>
int totalCombinations(int n) {
    
    //CASE 1 (If n=0)
    if(n==0)
    {
        return 1;
    }
    
    //CASE 2 (If n is negative)
    if(n<0)
    {
        return 0;
    }
    
    //MAIN CASE 
    int a=0;
    for(int i=1;i<=n;i++)
    {
        a = a + totalCombinations(n-i);
    }
    return a;
}
int main() {
    int n;
    scanf("%d", &n);
    int result = totalCombinations(n);
    printf("%d\n",result);
    return 0;
}