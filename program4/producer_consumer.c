#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

int empty = BUFFER_SIZE;
int full = 0;

void produce() {
    if (empty == 0) {
        printf("\nBuffer is full! Cannot produce.\n");
        return;
    }

    int item;
    printf("Enter item to produce: ");
    scanf("%d", &item);

    buffer[in] = item;
    printf("Produced: %d\n", item, in);
    
    in = (in + 1) % BUFFER_SIZE;
    empty--;
    full++;
}

void consume() {
    if (full == 0) {
        printf("Buffer is empty! Cannot consume.\n");
        return;
    }

    int item = buffer[out];
    printf("Consumed: %d\n", item, out);
    
    out = (out + 1) % BUFFER_SIZE;
    full--;
    empty++;
}

int main() {
    int choice;
    printf("Buffer Size: %d\n", BUFFER_SIZE);

    while (1) {
        printf("\n1. Produce\n2. Consume\n3. Exit\n");
        printf("Current State: [Full slots: %d | Empty slots: %d]\n", full, empty);
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                produce();
                break;
            case 2:
                consume();
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}