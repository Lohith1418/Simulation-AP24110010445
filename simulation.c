#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *head = NULL;

unsigned long fake_address(void *ptr) {
    return (unsigned long)ptr % 100000;
}

void displaySimulation() {
    printf("\n--- INTERNAL STATE OF LINKED LIST ---\n");

    if (head == NULL) {
        printf("[EMPTY LIST]\n");
        printf("Head -> NULL\n");
        printf("-------------------------------------\n\n");
        return;
    }

    Node *temp = head;
    int index = 0;

    printf("Head Address: %lu\n\n", fake_address(head));

    while (temp != NULL) {
        printf("Node %d:\n", index);
        printf("   Address: %lu\n", fake_address(temp));
        printf("   Data   : %d\n", temp->data);

        if (temp->next != NULL)
            printf("   Next -> %lu\n\n", fake_address(temp->next));
        else
            printf("   Next -> NULL\n\n");

        temp = temp->next;
        index++;
    }

    printf("-------------------------------------\n\n");
}

void insertAtEnd(int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    printf("\nCreating Node...\n");
    printf("New Node Address: %lu\n", fake_address(newNode));
    printf("Data Stored: %d\n\n", value);

    if (head == NULL) {
        head = newNode;
        printf("List was empty → Head now points to new node.\n");
        displaySimulation();
        return;
    }

    Node *temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;

    printf("Inserted %d at END. Updated pointer of last node.\n", value);
    displaySimulation();
}

void deleteAtPosition(int pos) {
    if (head == NULL) {
        printf("\nList is empty. Cannot delete.\n");
        return;
    }

    if (pos == 0) {
        Node *del = head;
        head = head->next;

        printf("\nDeleting HEAD node...\n");
        printf("Deleted Node Address: %lu\n", fake_address(del));

        free(del);
        displaySimulation();
        return;
    }

    Node *temp = head;
    for (int i = 0; temp != NULL && i < pos - 1; i++)
        temp = temp->next;

    if (temp == NULL || temp->next == NULL) {
        printf("\nInvalid position!\n");
        return;
    }

    Node *del = temp->next;
    temp->next = temp->next->next;

    printf("\nDeleting Node at position %d...\n", pos);
    printf("Deleted Node Address: %lu\n", fake_address(del));

    free(del);
    displaySimulation();
}

void traverseList() {
    printf("\nTraversing list...\n");
    Node *temp = head;
    int step = 0;

    while (temp != NULL) {
        printf("Step %d → Node Address: %lu, Data: %d\n",
               step, fake_address(temp), temp->data);
        temp = temp->next;
        step++;
    }
    printf("Traversal complete.\n");
    printf("-------------------------------------\n\n");
}

int main() {
    int choice, value, pos;

    while (1) {
        printf("LINKED LIST INTERNAL SIMULATION\n");
        printf("1. Insert at End\n");
        printf("2. Delete at Position\n");
        printf("3. Display Internal State\n");
        printf("4. Traverse\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insertAtEnd(value);
                break;

            case 2:
                printf("Enter position to delete (0-indexed): ");
                scanf("%d", &pos);
                deleteAtPosition(pos);
                break;

            case 3:
                displaySimulation();
                break;

            case 4:
                traverseList();
                break;

            case 0:
                printf("Exiting simulation.\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}
