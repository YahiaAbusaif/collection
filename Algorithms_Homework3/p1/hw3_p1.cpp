#include <bits/stdc++.h>
using namespace std;
#define lop(i,n) for(int i=0; i<n; i++)
ifstream InputFile;

struct Node
{
	int Value;
	Node* Left;
	Node* Right;
};

Node* build() //Build the given BST 
{
	int input;
	InputFile>>input;
	if(input==-1)
		return NULL;
	Node* curr=new Node;
	curr->Value=input;
	curr->Left=build();
	curr->Right=build();
	return curr;
}

vector<int> CommonElements;
void solve(Node* fir,Node* sec)
{ 
    stack<Node *> Stack1, Stack2; 
    while (1) 
    { 
        if (fir) 
        { 
            Stack1.push(fir); 
            fir = fir->Left; 
        } 
        else if (sec) 
        { 
            Stack2.push(sec); 
            sec = sec->Left; 
        } 
        else if (!Stack1.empty() && !Stack2.empty()) 
        { 
            fir = Stack1.top(); 
            sec = Stack2.top(); 

            if (fir->Value == sec->Value) 
            { 
				CommonElements.push_back(fir->Value);
                Stack1.pop(); 
                Stack2.pop(); 
                fir = fir->Right; 
                sec = sec->Right; 
            } 
            else if (fir->Value < sec->Value) 
            { 
                Stack1.pop(); 
                fir = fir->Right;
                sec = NULL; 
            } 
            else
            { 
                Stack2.pop(); 
                sec = sec->Right; 
                fir = NULL; 
            } 
        } 
        else  
			break; 
    } 
} 

int main(int argc, char* argv[]) 
{
	if (argc != 4)
	{
		cout<<"Error #argument";
		return 1;
	}

	
	InputFile.open(argv[1]);
	if (!InputFile )
	{
		cout<<"Error can't open file";
		return 1;
	}
	//take the input and build the 2 BST
	int n,m;
	InputFile>>n;
	Node* head1= build();
	InputFile>>m;
	Node* head2= build();

	auto started = chrono::high_resolution_clock::now();
	//solve the problem
	solve(head1,head2);
	auto done = chrono::high_resolution_clock::now();
	long long timespent=chrono::duration_cast< chrono::milliseconds >(done-started).count();
	ofstream OutputFile,TimeFile;
	OutputFile.open(argv[2], ios::out);
	TimeFile.open(argv[3], ios::out);
	if (!OutputFile || !TimeFile )
	{
		cout<<"Error can't create file";
		return 1;
	}
	TimeFile << "Running time: " << timespent <<"ms\n";
	OutputFile<<CommonElements.size()<<endl;
	lop(i,CommonElements.size())
	{
		OutputFile<<CommonElements[i];
		if(i!=CommonElements.size()-1)
			OutputFile<<" ";
	}
}
