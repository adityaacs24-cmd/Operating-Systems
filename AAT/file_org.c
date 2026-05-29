#include <stdio.h>
#include <string.h>
#define MAX 10

// Structs to simplify the data tracking
struct SingleLevel {
    char filenames[MAX][20];
    int fileCount;
};

struct UserDirectory {
    char username[20];
    char filenames[MAX][20];
    int fileCount;
};

// a) Single Level Directory
// Everything sits in one giant pool. No two files can share a name.
void singleLevelSimulation() {
    struct SingleLevel dir;
    dir.fileCount = 0;
    char name[20];
    int choice;

    printf("\n--- Single-Level Directory Simulation ---\n");
    while (1) {
        printf("\n1. Create File\n2. List Files\n3. Back to Main Menu\nChoice: ");
        scanf("%d", &choice);

        if (choice == 3) break;

        if (choice == 1) {
            printf("Enter file name: ");
            scanf("%s", name);

            // Check for duplicate names (Not allowed in single level!)
            int duplicate = 0;
            for (int i = 0; i < dir.fileCount; i++) {
                if (strcmp(dir.filenames[i], name) == 0) {
                    duplicate = 1;
                    break;
                }
            }

            if (duplicate) {
                printf("Error: File '%s' already exists in root directory!\n", name);
            } else if (dir.fileCount < MAX) {
                strcpy(dir.filenames[dir.fileCount], name);
                dir.fileCount++;
                printf("File created successfully.\n");
            } else {
                printf("Directory full!\n");
            }
        } else if (choice == 2) {
            printf("\nRoot Directory:\n");
            if (dir.fileCount == 0) printf("(Empty)\n");
            for (int i = 0; i < dir.fileCount; i++) {
                printf("  └── %s\n", dir.filenames[i]);
            }
        }
    }
}

// b) Two Level Directory
// Master Directory points to User Directories.
// Different users CAN have files with the exact same name.
void twoLevelSimulation() {
    struct UserDirectory master[3];  // 3 simulated users
    strcpy(master[0].username, "UserA");
    master[0].fileCount = 0;
    strcpy(master[1].username, "UserB");
    master[1].fileCount = 0;
    strcpy(master[2].username, "UserC");
    master[2].fileCount = 0;

    int choice, userIdx;
    char name[20];

    printf("\n--- Two-Level Directory Simulation ---\n");
    while (1) {
        printf("\nSelect User:\n1. UserA\n2. UserB\n3. UserC\n4. Back to Main Menu\nChoice: ");
        scanf("%d", &choice);

        if (choice == 4) break;
        if (choice < 1 || choice > 3) continue;

        userIdx = choice - 1;  // Map choice to array index

        printf("\n[%s's Directory Menu]\n1. Create File\n2. List All Directories\nChoice: ", master[userIdx].username);
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter file name: ");
            scanf("%s", name);

            // Checks duplicate ONLY inside this specific user's folder
            int duplicate = 0;
            for (int i = 0; i < master[userIdx].fileCount; i++) {
                if (strcmp(master[userIdx].filenames[i], name) == 0) {
                    duplicate = 1;
                    break;
                }
            }

            if (duplicate) {
                printf("Error: '%s' already exists for %s.\n", name, master[userIdx].username);
            } else if (master[userIdx].fileCount < MAX) {
                strcpy(master[userIdx].filenames[master[userIdx].fileCount], name);
                master[userIdx].fileCount++;
                printf("File created inside %s's folder.\n", master[userIdx].username);
            }
        } else if (choice == 2) {
            printf("\n--- Master Directory Map ---\n");
            for (int u = 0; u < 3; u++) {
                printf("Root / %s\n", master[u].username);
                if (master[u].fileCount == 0) printf("  └── (Empty)\n");
                for (int f = 0; f < master[u].fileCount; f++) {
                    printf("  └── %s\n", master[u].filenames[f]);
                }
            }
        }
    }
}

// c) Hierarchical Directory
// True tree structure. To keep it simple without pointers, we simulate a
// hardcoded three-deep tree path: root/Documents/your_file
void hierarchicalSimulation() {
    char documentsFolder[MAX][20];
    int docCount = 0;
    char name[20];
    int choice;

    printf("\n--- Hierarchical Directory Simulation ---\n");
    printf("Simulating path layout: root -> Documents -> [Your Files]\n");

    while (1) {
        printf("\n1. Create File inside 'root/Documents/'\n2. View full Tree map\n3. Back to Main Menu\nChoice: ");
        scanf("%d", &choice);

        if (choice == 3) break;

        if (choice == 1) {
            printf("Enter file name: ");
            scanf("%s", name);

            if (docCount < MAX) {
                strcpy(documentsFolder[docCount], name);
                docCount++;
                printf("File placed at: root/Documents/%s\n", name);
            }
        } else if (choice == 2) {
            printf("\nroot\n");
            printf("└── Documents\n");
            if (docCount == 0) printf("    └── (Empty)\n");
            for (int i = 0; i < docCount; i++) {
                printf("    └── %s\n", documentsFolder[i]);
            }
        }
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n=================================");
        printf("\nFILE ORGANIZATION TECHNIQUES");
        printf("\n=================================");
        printf("\n1. Single-Level Directory");
        printf("\n2. Two-Level Directory");
        printf("\n3. Hierarchical Directory");
        printf("\n4. Exit");
        printf("\nEnter choice (1-4): ");
        scanf("%d", &choice);

        if (choice == 4) break;

        switch (choice) {
            case 1:
                singleLevelSimulation();
                break;
            case 2:
                twoLevelSimulation();
                break;
            case 3:
                hierarchicalSimulation();
                break;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

// efficiency order:
// 1. Hierarchical (Best for large, complex file systems with many users)
// 2. Two-Level (Good for moderate complexity, allows user separation)
// 3. Single-Level (Simple but can become unmanageable with many files/users)