#include<iostream>
#include <vector>
using namespace std;
#define BUCKETSIZE 2

struct Record{
	bool valid;
	int key;
	int value;
};

struct Bucket{
	int localDepth;
	Record data[BUCKETSIZE];
};

int globalDepth=1;
vector<Bucket> Directory;

void insertItem(Record item);
Record searchItem(int mykey);
void dirdiv();
void dirExp();

//return the index for that key
int indexkey(int key){
   return key&((1<<globalDepth)-1); ;
}
//return the pair_index for that key
int pairIndex(int bucketNo, int depth)
{
    return bucketNo^(1<<(depth-1));
}
//-1 if empty , 1 if full , 0 else
int check(int bucketNo)
{
	bool emp=1,ful=1;
	for(int i=0;i<BUCKETSIZE;i++)
	{
		if(Directory[bucketNo].data[i].valid==0)
			ful=0;
		else
			emp=0;
	}
	if(emp)
		return -1;
	if(ful)
		return 1;
	return 0;
}
//print the record
void printrec(Record x)
{
	cout<<"Record Valid:"<<x.valid<<" Key: "<<x.key<<" value "<<x.value <<"\n";
}
//return new buket
Bucket makebuk()
{
	Bucket temp;
	temp.localDepth=globalDepth;
	for(int i=0;i<BUCKETSIZE;i++)
		temp.data[i].valid=0;
	return temp;
}
//return new rec
Record makerec(int k,int v)
{
	Record temp;
	temp.valid=1;
	temp.key = k;
	temp.value = v;
	return temp;
}
//initlize
void init()
{
	globalDepth=1;
	Directory.push_back(makebuk());
	Directory.push_back(makebuk());
}
//print the dirctory 
void printdir()
{
	cout<<"print dirctory:global depth="<<globalDepth<<endl;
	for(int i=0;i<(1<<globalDepth);i++)
	{
		cout<<"Bucket no."<<i<<endl;
		for(int j=0;j<BUCKETSIZE;j++)
		{
			printrec(Directory[i].data[j]);
		}
	}
}



//increase the size of the dirc to the double
void dirExp()
{
	cout<<"Dirctory exp called \n";
	for(int i=0;i<(1<<globalDepth);i++)
		Directory.push_back(Directory[i]);
	globalDepth++;
}

//decrease the size of the dirc to the half
void dirdiv()
{
	cout<<"Dirctory div called \n";
    for(int i=0 ; i<(1<<globalDepth) ; i++ )
    {
        if(Directory[i].localDepth==globalDepth)
            return;
    }
    globalDepth--;
    for(int i = 0 ; i < (1<<globalDepth) ; i++ )
        Directory.pop_back();
}

//split the bucket to 2
void split(int bucketNo)
{
	cout<<"split called \n";
    Bucket* temp=new Bucket;
	for(int i=0;i<BUCKETSIZE;i++)
		temp->data[i]=Directory[bucketNo].data[i];

	for(int i=0;i<BUCKETSIZE;i++)
		Directory[bucketNo].data[i].valid=0;

	Directory[bucketNo].localDepth++;
    int local_depth = Directory[bucketNo].localDepth;
	int pair_index = pairIndex(bucketNo,local_depth);

    if(local_depth>globalDepth)
        dirExp();
    Bucket tmp=makebuk();
    Directory[pair_index] = tmp;
    Directory[pair_index].localDepth = local_depth;

    int index_diff = 1<<local_depth;
    int dirSize = 1<<globalDepth;

    for(int i=pair_index-index_diff ; i>=0 ; i-=index_diff )
        Directory[i] = Directory[pair_index];
    for(int i=pair_index+index_diff ; i<dirSize ; i+=index_diff )
        Directory[i] = Directory[pair_index];

    for(int i=0;i<BUCKETSIZE;i++)
	{
		if(temp->data[i].valid==1)
			insertItem(temp->data[i]);
	}
        
}

//merge 2 bucket to one
void merge(int bucketNo)
{
	cout<<"merge called \n";
    int localDep = Directory[bucketNo].localDepth;
    int pair_index = pairIndex(bucketNo,localDep);
    int index_diff = 1<<localDep;
    int dirSize = 1<<globalDepth;

    if( Directory[pair_index].localDepth == localDep )
    {
        Directory[pair_index].localDepth--;
        Directory[bucketNo] = Directory[pair_index];
		
        for(int i=bucketNo-index_diff ; i>=0 ; i-=index_diff )
            Directory[i] = Directory[pair_index];
        for(int i=bucketNo+index_diff ; i<dirSize ; i+=index_diff )
            Directory[i] = Directory[pair_index];
    }
}

//insert item
void insertItem(Record item)
{
	if(searchItem(item.key).valid)
		return;
	int index=indexkey(item.key);
	while(check(index)==1)
	{
		split(index);
		index=indexkey(item.key);
	}
	for(int i=0;i<BUCKETSIZE;i++)
	{
		if(Directory[index].data[i].valid==0)
		{
			Directory[index].data[i]=item;
			break;
		}
	}
	cout<<"insert record :";
	printrec(item);
}
//search for key
Record searchItem(int mykey)
{
	int index=indexkey(mykey);
	for(int i=0;i<BUCKETSIZE;i++)
	{
		if(Directory[index].data[i].key==mykey && Directory[index].data[i].valid==1)
			return Directory[index].data[i];
	}
	Record temp;
	temp.valid=0;
	return temp;
}
//delete item
bool deleteItem(int mykey)
{
	cout<<"delete is called\n";
	int index=indexkey(mykey);
	for(int i=0;i<BUCKETSIZE;i++)
	{
		if(Directory[index].data[i].valid==1 && Directory[index].data[i].key==mykey)
		{
			Directory[index].data[i].valid=0;
			if(check(index)==-1&& globalDepth>1)
			{
				merge(index);
			}
			bool div=1;
			for(int j=0;j<(1<<globalDepth);j++)
			{
				if(Directory[j].localDepth==globalDepth)
					div=0;
			}
			if(div)
				dirdiv();
			return true;
		}
	}
	return false;
}




int main()
{
	
	init();
	
	insertItem(makerec(0,0));
	
	printdir();
	
	insertItem(makerec(1,1));
	
	printdir();
	
	insertItem(makerec(2,2));
	
	printdir();
	
	insertItem(makerec(3,3));
	
	printdir();
	
	insertItem(makerec(4,4));
	
	printdir();
	
	insertItem(makerec(5,5));
	
	printdir();
	
	insertItem(makerec(6,6));
	
	printdir();
	
	insertItem(makerec(7,7));
	
	printdir();
	
	insertItem(makerec(8,8));
	
	printdir();
	
	insertItem(makerec(9,9));
	
	printdir();

	cout<<"search for 0 res:";
	printrec(searchItem(0));
	cout<<"search for 200 res:";
	printrec(searchItem(200));


	cout<<"delete 200 is"<<deleteItem(200)<<endl;
	deleteItem(0);
	printdir();
	deleteItem(8);
	printdir();
	deleteItem(4);
	deleteItem(5);
	printdir();

	int input;
	cin>>input;
	return 0;
}
