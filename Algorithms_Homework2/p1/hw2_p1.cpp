#include <bits/stdc++.h> 
using namespace std;

int Infinte=2147483640;

struct Node
{
	int value;
	Node* next;
};


Node * LinkedListReverse(Node * Head,long long  & timespent,const int & length)
{
	if(Head==NULL || length<1) //validation
	{
		timespent=0;
		return NULL;
	}
	auto started = chrono::high_resolution_clock::now(); //start time 
	Node** ReverseStack= new Node*[length]; //declare array
	Node * CurrentPointer=Head; //for loop on the linked list
	//puch all elements to stack
	int last=0;
	while(CurrentPointer!=NULL)
	{
		ReverseStack[last++]=CurrentPointer;
		CurrentPointer=CurrentPointer->next;
	}
	//if last = 0 return null (empty linked list)
	if(last==0)
	{
		timespent=0;
		return NULL;
	}
	//reverse
	Head=ReverseStack[length-1];
	for(int iter=length-1;iter>0;iter--)
		ReverseStack[iter]->next=ReverseStack[iter-1];
	ReverseStack[0]->next=NULL;

	auto done = chrono::high_resolution_clock::now();//end time 

	timespent=chrono::duration_cast< chrono::milliseconds >(done-started).count();//calculte algoritm time 

	return Head; //retrun the new head of linked list 
}

int main(int argc, char* argv[])
{
	//if no enough argument end the program
	if(argc<3) 
		return 1;
	//open file
	fstream inputfile;
   	inputfile.open(argv[1],ios::in); 
  	if(!inputfile) //if can not open file end the program
		return 1;

	
	//Read data from the file
	Node * Head=NULL; //head of linked list 
	Node * last=NULL; //last item in linked list (optmize for inserting instead of loop on all nodes each time for insert)
	int length=0;
	while(!(inputfile.eof()))
	{
		int currentnumber=Infinte; //mark the variable
		inputfile>>currentnumber;
		if(currentnumber!=Infinte) //if there are input make node and insert it to linked list
		{
			Node* current=new Node;
			current->value=currentnumber;
			current->next=NULL;
			if(last==NULL)
				Head=current;
			else
				last->next=current;
			last=current;
			length++;
		}
	}

	//process
	long long TotalTime=0;
	Head=LinkedListReverse(Head,TotalTime,length); //reverse

	//print reversed data
	FILE * Result= fopen (argv[2],"w");
	if(Result==NULL) //if can not open file end the program
		return 1;

	Node * CurrentPointer=Head;
	while(CurrentPointer!=NULL)
	{
		string current =to_string(CurrentPointer->value)+"\n";
		char const *output = current.c_str(); 
		fputs (output,Result);
		CurrentPointer=CurrentPointer->next;
	}
	fclose (Result);

	//print the spent time
	FILE * TimeSpent= fopen (argv[3],"w");
	if(TimeSpent==NULL) //if can not open file end the program
		return 1;
	string OutputTime =to_string(TotalTime)+"\n";
	char const *pchar = OutputTime.c_str(); 
	fputs (pchar,TimeSpent);
	fclose (TimeSpent);
	return 0;
}

