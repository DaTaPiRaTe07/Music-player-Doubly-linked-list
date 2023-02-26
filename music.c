#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>

struct music {
    char *link;
    char *name;
    struct music *next;
    struct music *prev;
}*head=NULL,*tail=NULL;

struct music * create(char *link,char *name) {
    struct music *newnode;
    newnode = (struct music*) malloc(sizeof(struct music));
    newnode->next = NULL;
    newnode->prev = NULL;
    newnode->link = malloc(strlen(link) + 1);
    strcpy(newnode->link, link);
    newnode->name = malloc(strlen(name) + 1);
    strcpy(newnode->name, name);
    return newnode;
}

void insert() {
    struct music *newnode;
    char ch[100], ch1[300];
    printf("\nEnter the song name : ");
    scanf("%s", ch1);
    printf("\nEnter the address of file : ");
    scanf("%s", ch);
    newnode = create(ch, ch1);
    if(head == NULL && tail == NULL) {
        head = newnode;
        tail = newnode;
        printf("\nThe song %s is added successfully ", ch1);
    } else {
        tail->next = newnode;
        newnode->prev = tail;
        printf("\nThe song %s is added successfully ", ch1);
        tail = newnode;
    }
}

void print() {
    if(head == NULL && tail == NULL) {
        printf("\nplaylist is empty ");
    } else {
        struct music *temp = head;
        int i = 1;
        while(temp != NULL) {
            printf("\n %d. %s", i, temp->name);
            i++;
            temp = temp->next;
        }
    }
    
}
char* songling(struct music *ptr)
{
    return ptr->link;
}
int main() 
{
    int choice;
    struct music *current = NULL;
    while (1)
    {
        printf("\n\nChoose an action:\n");
        printf("1. Add a new song\n");
        printf("2. Print the playlist\n");
        printf("3. Play the current song\n");
        printf("4. Stop the current song\n");
        printf("5. Move to the next song\n");
        printf("6. Move to the previous song\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                insert();
                if (current == NULL) {
                    current = head;
                }
                break;
            case 2:
                print();
                break;
            case 3:
                if (current == NULL) {
                    printf("\nNo song is selected");
                } else {
                    printf("\nNow Playing : %s \n",current->name);
                    PlaySound(songling(current), NULL, SND_FILENAME | SND_ASYNC);
                }
                break;
            case 4:
                if (current == NULL) {
                    printf("\nNo song is selected");
                } else {
                    PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_PURGE);
                }
                break;
            case 5:
                if (current == NULL) {
                    printf("\nNo song is selected");
                } else if (current->next == NULL) {
                    printf("\nYou have reached the end of the playlist");
                    //PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                } else {
                    current = current->next;
                    printf("\nNow Playing : %s \n",current->name);                    
                    PlaySound(songling(current), NULL, SND_FILENAME | SND_ASYNC);
                }
                break;
            case 6:
                if (current == NULL) {
                    printf("\nNo song is selected");
                } else if (current->prev == NULL) {
                    printf("\nYou have reached the beginning of the playlist");
                    //PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                } else {
                    current = current->prev;
                    printf("\nNow Playing : %s \n",current->name);
                    PlaySound(songling(current), NULL, SND_FILENAME | SND_ASYNC);
                }
                break;
            case 7:
                printf("Exited Successfully");
                exit(0);
                break;
        }
    }
    return 0;
}
