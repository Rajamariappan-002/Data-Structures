#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

char array[30];
char popelements[30];
int poptop = -1;
int top = -1;

void push(char c)
{
	top = top+1;
	array[top] = c;
}


void operandfun(char c)
{
	
	push(c);
}

char pop()
{
	return array[top--];
}

void poppush(c)
{ 
	poptop = poptop+1;
	popelements[poptop] = c;
}

void operatorfun()
{
	
	char c = pop();
	poppush(c);
}

void display()
{
	int i;
	for(i=0;i<=poptop;i++)
	{
		printf("%c",popelements[i]);
	}
}

int main()
{
	int i=0;
	char string[30];
	printf("Enter an expression:");
	scanf("%s",string);
	
	while(string[i] != '\0')
	{
		
		if(isalpha(string[i]))
		{
			operandfun(string[i]);
		}
		else if(string[i] == '*')
		{
			operatorfun(string[i]);
		}
		i++;
	}
	
	display();
	
	return 0;
}
