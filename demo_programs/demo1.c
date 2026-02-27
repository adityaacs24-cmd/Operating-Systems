#include<stdio.h>
int main()
{
    int arr[10], n, ele;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");

    for(int i = 0; i < n; i++)
    {
        scanf("%d", arr + i);
    }

    printf("Enter element to search: ");
    scanf("%d", &ele);

    for(int i = 0; i < n; i++)
    {
        if(arr[i] == ele)
        {
            printf("Found at pos %d\n", i);
            return 0;
        }
    }

    printf("Element Not found\n");
    return 0;
}
