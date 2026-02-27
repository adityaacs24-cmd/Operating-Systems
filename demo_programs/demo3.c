#include<stdio.h>
int main()
{
    int arr[10], n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");

    for(int i = 0; i < n; i++)
    {
        scanf("%d", arr + i);
    }

    int small = arr[0], pos = 0;

    for(int i = 1; i < n; i++)
    {
        if(arr[i] < small)
        {
            small = arr[i];
            pos = i;
        }
    }

    printf("Smallest element %d\nAt position %d\n", small, pos);
    return 0;
}
