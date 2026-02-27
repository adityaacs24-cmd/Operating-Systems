#include<stdio.h>
int main(){
    int arr[10], n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");

    for(int i = 0; i < n; i++)
    {
        scanf("%d", arr + i);
    }

    int dup = -1;

    for(int i = 0; i < n; i++){
        int ele = arr[i];

        for(int j = 0; j < n; j++){
            if(i != j && arr[j] == ele){
                dup = arr[j];
                break;
            }
        }

        if(dup != -1){
            break;
        }
    }

    if(dup == -1){
        printf("No duplicates found\n");
    }else{
        printf("Duplicate element %d", dup);
    }

    return 0;
}
