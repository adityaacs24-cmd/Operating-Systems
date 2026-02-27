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

    int l = 0, h = n - 1;

    while(l <= h)
    {
        int mid = (l + h) / 2;

        if(arr[mid] == ele)
        {
            printf("Found at pos %d", mid);
            return 0;
        }

        if(arr[mid] > ele)
        {
            h = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }

    printf("Element not found\n");
    return 0;
}
