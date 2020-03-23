#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"

struct campus
{
	char studentMajor[30]={};
	char studentId[15]={};
	char studentName[25]={};
	char className[10]={};
	char classMajor[50]={};
	char classLecturer[50]={};
	
	struct campus *next = NULL;
}*curr, *classRoom[100];

struct campus *createStudent(char id[], char major[], char name[], char className[], char studentMajor[], char classLecturer[])
{
	curr = (struct campus*)malloc(sizeof(struct campus));
	curr->next = NULL;
	
	strcpy(curr->studentId,id);
	strcpy(curr->studentMajor,major);
	strcpy(curr->studentName,name);
	strcpy(curr->className,className);
	strcpy(curr->classLecturer,classLecturer);
	strcpy(curr->studentMajor,studentMajor);
	
	return curr;
}

struct campus *createClass(char classMajor[], char className[], char classLecturer[])
{
	curr = (struct campus*)malloc(sizeof(struct campus));
	curr->next = NULL;
	
	strcpy(curr->classLecturer,classLecturer);
	strcpy(curr->classMajor,classMajor);
	strcpy(curr->className,className);
	return curr;
}

//prototype
void splash(int _);
void blank();
void printStart();
void printUi();
void printClassError(int _);
void arrowMark();
void showError(int a,int b);
void createClass();
void insertStudent();
void viewStudent();
void exitMessage();
void printClassMajor(char str[]);
void printStudentError(int _);
int classNameCheck(char str[]);
int hashFunction(char str[]);
int checkClass();
int checkClassMajor(char str[]);
int checkStudentId(char str[]);
void printClassMajor(char str[]);

int main()
{
	int input = -1;
	char errHandle[50];
	printStart();
	do
	{
		printUi();	
		do
		{
			input = -1;
			arrowMark();scanf("%d",&input);
			if(input >= 1 && input <= 4)getchar();
			if(input > 4 || input < 1)
			{
				gets(errHandle);
				showError(1,4);	
			}
			
		}while(input > 4 || input < 1);
			switch(input)
			{
				case 1:
					createClass();
					break;
				case 2:
					insertStudent();
					break;
				case 3:
					viewStudent();
					break;
				case 4:
					exitMessage();
					break;
			}
	}while(input != 4);
	
}

void splash(int _)
{
	_*=25;
	clock_t curr = clock();
	while(clock() < curr+_);
}

void blank()
{
	for(int i =0;i<30;i++)puts("");
}

void printStart()
{
	char welcome[] = "HashTable Training\n";
	char credit[] = "Made by S!rent";
	blank();
	for(int i = 0;i<strlen(welcome);i++){
		printf("%c",welcome[i]);
		splash(1);
	}
	
	for(int i = 0;i<strlen(credit);i++){
		printf("%c",credit[i]);
		splash(1);
	}
	splash(50);
}

void printUi()
{
	blank();
	puts("Sunib University");
	puts("================");
	puts("1. Create Class");
	puts("2. Insert Student");
	puts("3. View Class & Student");
	puts("4. Exit");
}

void arrowMark()
{
	printf(">> ");
}

void showError(int a,int b)
{
	printf("Please input [%d - %d]!\n",a,b);
}

void printClassError(int _)
{
	switch(_)
	{
		case 1:
			printf("Class Name Must be 5 Characters !\n");
			break;
		case 2:
			printf("Class Name Must have 1 '-' and 2 Numbers,Alphabet\n");
			break;
		case 3:
			printf("Class Name Must Be Like [AA-XX] A: Alphabet X:Number !\n");
			break;
		case 4:
			printf("Class Name Must Be Like [AA-XX] A: Alphabet X:Number !\n");
			break;
		case 5:
			printf("Class Name Must Be Like [AA-XX] A: Alphabet X:Number !\n");
			break;
		case 6:
			printf("Class Name Already Exist !\n");
			break;
	}
}

void createClass()
{
	int error=-1;
	char className[50];
	char classMajor[50];
	char classLecturer[50];
	
	blank();
	do
	{
		error = -1;
		printf("Input Class Name [AA-XX] : ");scanf("%[^\n]",className);getchar();
		error = classNameCheck(className);
		if(error !=0)printClassError(error);
	}while(error != 0);

		printf("Input Class Major : ");scanf("%[^\n]",classMajor);getchar();
		printf("Input Class Lecturer : ");scanf("%[^\n]",classLecturer);getchar();
		
	curr = createClass(classMajor,className,classLecturer);
	classRoom[hashFunction(className)] = curr;
}

void insertStudent()
{
	blank();
	int error=-1;
	char className[50];
	char studentMajor[50];
	char studentId[50];
	char studentName[50];
	
	if(checkClass() == 0)
	{
		printf("There is no class available !.");
		getchar();
	}
	else
	{
		printf("Input Student Major : ");scanf("%[^\n]",studentMajor);getchar();
		if(checkClassMajor(studentMajor) == 0)
		{
			printf("There is no class available !");
			getchar();
		}
		else
		{
			printClassMajor(studentMajor);
			do
			{
				printf("Input Class Name [AA-XX] : ");scanf("%[^\n]",className);getchar();
				error = classNameCheck(className);
			}while(error != 6);
			do
			{
				error = -1;
				printf("Input Student ID [BXXXXXXXXX] : ");scanf("%[^\n]",studentId);getchar();
				error = checkStudentId(studentId);
				if(error != 0)printStudentError(error);
			}while(error != 0 );
			
				printf("Input Student Name : ");scanf("%[^\n]",studentName);getchar();
			
			curr = createStudent(studentId, studentMajor, studentName, className, studentMajor, classRoom[hashFunction(className)]->classLecturer);
			
			struct campus *temp = classRoom[hashFunction(className)];
			
			while(temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = curr;
		}	
	}

}

void viewStudent()
{
	
}

void exitMessage()
{
	
}

int checkClass()
{
	int ctr=0;
	for(int i = 0;i<100;i++)
	{
		if(classRoom[i] != NULL)ctr++;
	}
	return ctr;
}

int classNameCheck(char str[])
{
	int alpha=0,num=0,stripe=0;
		if(strlen(str) != 5)return 1;
	for(int i = 0;i<strlen(str);i++)
	{
		if(str[i] >= 'A' && str[i]<= 'Z')alpha++;
		if(str[i] >= '0' && str[i]<='9')num++;
		if(str[i] == '-')stripe++;
	}
		if(alpha != 2 || num !=2 || stripe !=1)return 2;
		if(!(str[0] >= 'A' && str[0] <= 'Z') || !(str[1] >= 'A' && str[1] <= 'Z'))return 3;
		if(str[2] != '-')return 4;
		if(!(str[3] >= '0' && str[3] <= '9') || !(str[4] >= '0' && str[4] <= '9'))return 5;
		if((classRoom[hashFunction(str)] != NULL)&&(strcmp(str,classRoom[hashFunction(str)]->className)==0))return 6;
	return 0;
}

int hashFunction(char str[])
{
	int jml=0;
	for(int i = 0;i<strlen(str);i++)
	{
		jml+=str[i];
	}
	return jml%50;
}

int checkStudentId(char str[])
{
	if(strlen(str) != 10)return 1;
	if(str[0] != 'B')return 2;
	return 0;
}

int checkClassMajor(char str[])
{
	int ctr=0;
	for(int i = 0;i<100;i++)
	{
		if(classRoom[i] != NULL)
		{
			if(strcmp(str,classRoom[i]->classMajor) == 0)ctr++;
		}
	}
	return ctr;
}

void printStudentError(int _)
{
	switch(_)
	{
		case 1:
			printf("Student Id length must be 10 characters\n");
			break;
		case 2:
			printf("Student Id must start with 'B'\n");
			break;
	}
}

void printClassMajor(char str[])
{
	printf("%s\n",str);
	for(int i= 0;i<strlen(str);i++)printf("=");
	puts("");
	for(int i = 0;i<100;i++)
	{
		if(classRoom[i] != NULL)
		{
			if(strcmp(str,classRoom[i]->classMajor) == 0){
				printf("%s\n",classRoom[i]->className);
			}	
		}
		
	}
}
