#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct mhs
{
	char nama[50]={};
	struct mhs *next=NULL;
}*table[50], *curr;

struct mhs *createNode(char nama[])
{
	struct mhs *curr = (struct mhs*)malloc(sizeof(struct mhs));
	strcpy(curr->nama,nama);
	curr->next = NULL;
	return curr;
}

int hashFunction(char nama[])
{
	int jml = 0;
	for(int i = 0;i<strlen(nama);i++)
	{
		if(nama[i] >= 'A' && nama[i] <= 'Z')
		{
			jml = jml + (nama[i] - 'A');
		}
		else
		{
			jml = jml + (nama[i] - 'a');
		}
	}	

	return jml%50;
}

int pushBack(char nama[])
{
	curr = createNode(nama);
	int idx = hashFunction(nama);
	
	if(table[idx] == NULL)
	{
		table[idx]= curr;
	}
	else
	{
		struct mhs *temp = table[idx];
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = curr;
	}
}

void printAll()
{
	for(int i =0;i<50;i++)
	{
		if(table[i] != NULL)
		{
				printf("Isi Tabel ke %d = ",i);
			curr = table[i];
			while(curr)
			{
				printf("%s",curr->nama);
				if(curr->next!=NULL)printf(" ");
				curr=curr->next;
			}
			puts("");
		}	
	}
}

int main()
{
	pushBack("Yopaw");
	pushBack("Alicia");
	pushBack("Philip");

	printAll();
}
