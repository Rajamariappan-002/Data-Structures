#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define max 10
int count = 0;

//for storing the edges in ascending order
struct ascnode 
{
	char src[max];
	char des[max];
	int weight;
	struct ascnode* next;
};
//for storing the nodes in graph
struct node 
{
    char city[max];
    struct node* adjvertex;
    struct node* adjlist;
    int weight;
};

struct node* root = NULL; //root of a graph
struct ascnode* head = NULL; //head of the ascending order list

//Node creation for storing the edges in ascending order

struct ascnode* createascnode(char src[max],char des[max],int weight)
{
	struct ascnode* newnode = (struct ascnode*)malloc(sizeof(struct ascnode));
	strcpy(newnode->src,src);
	strcpy(newnode->des,des);
	newnode->weight = weight;
	newnode->next = NULL;
	return newnode;
}

//node creation for storing the nodes in graph
struct node* createvertex(char city[max])
{
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    strcpy(newnode->city,city);
    newnode->adjvertex = NULL;
    newnode->adjlist = NULL;
    newnode->weight = 0;
    return newnode;
}

//function to check for the existence of vertex

int vertexexists(char city[max])
{
	struct node* current = root;
	while(current!=NULL)
	{
		if(strcmp(current->city,city) == 0)
		{
			return 1;
		}
		else 
		{
			return 0;
		}
		current = current->adjvertex;
	}
		
}

//function to add a vertex

void addvertex(char city[max]) 
{
	if(vertexexists(city))
	{
		printf("\nVertex already exists..");
		return;
	}
	
    if (root == NULL) 
	{
        root = createvertex(city);
    }
    else 
	{
        struct node* current = root;
        while (current->adjvertex != NULL) 
		{
            current = current->adjvertex;
        }
        current->adjvertex = createvertex(city);
        count++;
    }
}

//function to add edge in graph

void addedge(char src[max], char des[max], int weight) 
{
    struct node* current = root;
    while (current != NULL)
	 {
        if (strcmp(current->city,src) == 0) 
		{
            struct node* temp = current;
            while (temp->adjlist != NULL)
			{
                temp = temp->adjlist;
            }
            temp->adjlist = createvertex(des);
            temp->adjlist->weight = weight;
            printf("\nEdge added");
            
            break;
        }
        current = current->adjvertex;
    }
}

//function to display the graph

void display() {
    if (root == NULL) 
	{
        printf("\nNo graph");
        return;
    }
    else
	{
        struct node* current = root;
        while (current != NULL)
		 {
            struct node* temp = current;
            while (temp != NULL) 
			{
                printf("(%d)%s-> ", temp->weight,temp->city);
                temp = temp->adjlist;
            }
            printf("NULL\n");
            current = current->adjvertex;
        }
    }
}

//Function to create ascending order list based on weight of the edge

void createasclist(char src[max], char des[max], int weight) {
    struct ascnode* newnode = createascnode(src, des, weight);
    struct ascnode* prev = NULL;  // Initialize prev to NULL

    if (head == NULL) 
	{
        // If the list is empty, the new node becomes the head
        head = newnode;
    } 
	else
	{
        struct ascnode* current = head;

        // Traverse the list to find the correct position based on ascending order
        while (current != NULL && weight > current->weight) {
            prev = current;
            current = current->next;
        }

        // Insert the new node at the correct position
        if (prev == NULL) {
            // Insert at the beginning of the list
            newnode->next = head;
            head = newnode;
        } else {
            // Insert in the middle or at the end of the list
            prev->next = newnode;
            newnode->next = current;
        }
    }
}

//display the ascending order list
void displayasc()
{
	struct ascnode* current = head;
	while(current!=NULL)
	{
		printf("%d\n",current->weight);
		current = current->next;
	}
}

void findminspan()
{
	int n = 0;
	int totalweight = 0;
	struct ascnode* current = head;
	
	while(n<count)
	{
		printf("%s->%s(%d)",current->src,current->des,current->weight);
		printf("\n");
		current = current->next;
		totalweight = totalweight+current->weight;
		n++;
	}
	printf("Total weight of the Minimum spannaing Tree is %d",totalweight);
		
} 

int main() {
    int choice,weight;
    char city[max];
    char src[max],des[max];


    while (1) {
        printf("\n1.Add a vertex \n2.Add an edge \n3.Display \n4.Find minimum spanning Tree \n5.Exit \n6.DisplayAscList");
        printf("\nEnter your choice:");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter the vertex:");
                scanf("%s",city);
                addvertex(city);
                break;
            case 2:
                if (root == NULL) {
                    printf("\nNo vertex to add an edge!!!\nAdd a vertex first.");
                    break;
                }
               	
                printf("\nEnter the source:");
                scanf("%s", &src);
                printf("\nEnter the destination:");
                scanf("%s", &des);
                printf("\nEnter the weight:");
               	scanf("%d",&weight);
                addedge(src, des, weight);
               	createasclist(src,des,weight);
                break;
            case 3:
                display();
                break;
                
            case 4:
				findminspan();
				break;    
                
            case 5:
                exit(0);
                
            case 6:
				displayasc(); 
				break;
            default:
                printf("\nInvalid choice...");
                
        }
    }

    return 0;
}

