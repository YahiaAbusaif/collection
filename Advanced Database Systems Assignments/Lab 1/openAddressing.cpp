#include "readfile.h"


int hashCode(int key){
   return key % MBUCKETS;
}

int hashCode2(int key){
   return (key*3)% MBUCKETS;
}


int insertItem(int fd,DataItem item){
	struct DataItem data;   //a variable to read in it the records from the db
	int count = 1;				//No of accessed records
	int rewind = 0;			//A flag to start searching from the first bucket
	int hashIndex = hashCode(item.key);  				//calculate the Bucket index
	int startingOffset = hashIndex*sizeof(Bucket);		//calculate the starting address of the bucket
	int Offset = startingOffset;						//Offset variable which we will use to iterate on the db

    ssize_t result = pread(fd,&data,sizeof(DataItem), Offset);
    if(result <= 0) return -1;
    while (data.valid == 1)
    {
        Offset+=sizeof(DataItem);
        if(Offset >= FILESIZE && rewind ==0 )
    	 { //if reached end of the file start again
    			rewind = 1;
    			Offset = 0;
    	  } else
    	      if(rewind == 1 && Offset >= startingOffset) {
    			return -1; //no empty spaces
    	   }
        result = pread(fd,&data,sizeof(DataItem), Offset);
        if(result <= 0) return -1;
        count++;
    }
   result = pwrite(fd,&item, sizeof(DataItem), Offset);
   return count;
}


int insertItem2(int fd,DataItem item){
	struct DataItem data;   //a variable to read in it the records from the db
	int count = 0;				//No of accessed records
	int rewind = 0;			//A flag to start searching from the first bucket
	int hashIndex = hashCode(item.key);  				//calculate the Bucket index
	int startingOffset = hashIndex*sizeof(Bucket);		//calculate the starting address of the bucket
	int Offset = startingOffset;
    						//Offset variable which we will use to iterate on the db
    ssize_t result;
    
    for(int cntbuk=0;cntbuk<RECORDSPERBUCKET;cntbuk++)
    {
        count++;
        result = pread(fd,&data,sizeof(DataItem), Offset); if(result <= 0) { return -1; }
        if(data.valid==0) {break;  }
        Offset+=sizeof(DataItem);
    }
    if(data.valid == 0)
    {    result = pwrite(fd,&item, sizeof(DataItem), Offset); return count;   }
    else
    {
        if (data.next==-1)
        {   
            int oldoffset=Offset;
            for(Offset=MBUCKETS*BUCKETSIZE;Offset<FILESIZE;Offset+=sizeof(DataItem))
            {
                count++;
                result = pread(fd,&data,sizeof(DataItem), Offset); if(result <= 0) { return -1; } 
                if(data.valid == 0) break;
            
            }
            
            if( Offset>=FILESIZE) {return -1;}
            result = pwrite(fd,&item, sizeof(DataItem), Offset); if(result <= 0) { return -1; }
            result = pread(fd,&data,sizeof(DataItem), oldoffset); if(result <= 0) { return -1; }
            data.next=Offset;
            result = pwrite(fd,&data, sizeof(DataItem), oldoffset); if(result <= 0) { return -1; }
        }
        else
        { 
            for(Offset=data.next;Offset<FILESIZE;Offset+=sizeof(DataItem))
            {
                count++;
                result = pread(fd,&data,sizeof(DataItem), Offset); if(result <= 0) { return -1; } 
                if(data.valid == 0) break;
            
            }
            if( Offset>=FILESIZE) {return -1;}
            result = pwrite(fd,&item, sizeof(DataItem), Offset); if(result <= 0) { return -1; }
            }
        
    }
        
   return count;
}

int insertItem3(int fd,DataItem item){
	struct DataItem data;   //a variable to read in it the records from the db
	int count = 1;				//No of accessed records
	int rewind = 0;			//A flag to start searching from the first bucket
	int hashIndex = hashCode2(item.key);  				//calculate the Bucket index
	int startingOffset = hashIndex*sizeof(Bucket);		//calculate the starting address of the bucket
	int Offset = startingOffset;
    						//Offset variable which we will use to iterate on the db
    
    ssize_t result = pread(fd,&data,sizeof(DataItem), Offset); if(result <= 0) { return -1; }
    int cntbuk=1;
    while(data.valid == 1 && cntbuk<RECORDSPERBUCKET)
    {
        Offset+=sizeof(DataItem),count++,cntbuk++;
        result = pread(fd,&data,sizeof(DataItem), Offset); if(result <= 0) { return -1; }
    }
        
    if(data.valid == 0)
    { result = pwrite(fd,&item, sizeof(DataItem), Offset); return count;   }
    
    int cnt2=    insertItem(fd,item);
    if (cnt2==-1) return -1;

        
   return count+cnt2;
}


/* Functionality: using a key, it searches for the data item
 *          1. use the hash function to determine which bucket to search into
 *          2. search for the element starting from this bucket and till it find it.
 *          3. return the number of records accessed (searched)
 *
 * Input:  fd: filehandler which contains the db
 *         item: the dataitem which contains the key you will search for
 *               the dataitem is modified with the data when found
 *         count: No. of record searched
 *
 * Output: the in the file where we found the item
 */

int searchItem(int fd,struct DataItem* item,int *count)
{

	//Definitions
	struct DataItem data;   //a variable to read in it the records from the db
	*count = 0;				//No of accessed records
	int rewind = 0;			//A flag to start searching from the first bucket
	int hashIndex = hashCode(item->key);  				//calculate the Bucket index
	int startingOffset = hashIndex*sizeof(Bucket);		//calculate the starting address of the bucket
	int Offset = startingOffset;						//Offset variable which we will use to iterate on the db

	//Main Loop
	RESEEK:
	//on the linux terminal use man pread to check the function manual
	ssize_t result = pread(fd,&data,sizeof(DataItem), Offset);
	//one record accessed
	(*count)++;
	//check whether it is a valid record or not
    if(result <= 0) //either an error happened in the pread or it hit an unallocated space
	{ 	 // perror("some error occurred in pread");
		  return -1;
    }
    else if (data.valid == 1 && data.key == item->key) {
    	//I found the needed record
    			item->data = data.data ;
    			return Offset;

    } else { //not the record I am looking for
    		Offset +=sizeof(DataItem);  //move the offset to next record
    		if(Offset >= FILESIZE && rewind ==0 )
    		 { //if reached end of the file start again
    				rewind = 1;
    				Offset = 0;
    				goto RESEEK;
    	     } else
    	    	  if(rewind == 1 && Offset >= startingOffset) {
    				return -1; //no empty spaces
    	     }
    		goto RESEEK;
    }
}

int searchItem2(int fd,struct DataItem* item,int *count)
{

	//Definitions
	struct DataItem data;   //a variable to read in it the records from the db
	*count = 0;				//No of accessed records
	int rewind = 0;			//A flag to start searching from the first bucket
	int hashIndex = hashCode(item->key);  				//calculate the Bucket index
	int startingOffset = hashIndex*sizeof(Bucket);		//calculate the starting address of the bucket
	int Offset = startingOffset;						//Offset variable which we will use to iterate on the db

    ssize_t result;
    
    for(int cntbuk=0;cntbuk<RECORDSPERBUCKET;cntbuk++)
    {
        (*count)++;
        result = pread(fd,&data,sizeof(DataItem), Offset); if(result <= 0) { return -1; }
        if (data.valid == 1 && data.key == item->key) {return Offset;  }
        Offset+=sizeof(DataItem);
    }
    if(data.next !=-1 )
    {
            for(Offset=data.next;Offset<FILESIZE;Offset+=sizeof(DataItem))
            {
                (*count)++;
                result = pread(fd,&data,sizeof(DataItem), Offset); if(result <= 0) { return -1; } 
                if (data.valid == 1 && data.key == item->key) {return Offset;  } 
            
            }      
    }
        
   return -1;
}




int searchItem3(int fd,struct DataItem* item,int *count){
	struct DataItem data;   //a variable to read in it the records from the db	
   	int rewind = 0;			//A flag to start searching from the first bucket
    *count = 0;	
	int hashIndex = hashCode2(item->key);  				//calculate the Bucket index
	int startingOffset = hashIndex*sizeof(Bucket);		//calculate the starting address of the bucket
	int Offset = startingOffset;
    						//Offset variable which we will use to iterate on the db
    
    ssize_t result;
    
    for(int cntbuk=0;cntbuk<RECORDSPERBUCKET;cntbuk++)
    {
        (*count)++;
        result = pread(fd,&data,sizeof(DataItem), Offset); if(result <= 0) { return -1; }
        if (data.valid == 1 && data.key == item->key) {return Offset;  }
        Offset+=sizeof(DataItem);
    }
    
    return searchItem(fd,item,count);
        
}

/* Functionality: Display all the file contents
 *
 * Input:  fd: filehandler which contains the db
 *
 * Output: no. of non-empty records
 */
int DisplayFile(int fd){

	struct DataItem data;
	int count = 0;
	int Offset = 0;
	for(Offset =0; Offset< FILESIZE;Offset += sizeof(DataItem))
	{
		ssize_t result = pread(fd,&data,sizeof(DataItem), Offset);
		if(result < 0)
		{ 	  perror("some error occurred in pread");
			  return -1;
		} else if (result == 0 || data.valid == 0 ) { //empty space found or end of file
			printf("Bucket: %d, Offset %d:~\n",Offset/BUCKETSIZE,Offset);
		} else {
			pread(fd,&data,sizeof(DataItem), Offset);
			printf("Bucket: %d, Offset: %d, Data: %d, key: %d\n",Offset/BUCKETSIZE,Offset,data.data,data.key);
					 count++;
		}
	}
	return count;
}


/* Functionality: Delete item at certain offset
 *
 * Input:  fd: filehandler which contains the db
 *         Offset: place where it should delete
 *
 * Hint: you could only set the valid key and write just and integer instead of the whole record
 */
int deleteOffset(int fd, int Offset)
{
	struct DataItem dummyItem;
	dummyItem.valid = 0;
	dummyItem.key = -1;
	dummyItem.data = 0;
	int result = pwrite(fd,&dummyItem,sizeof(DataItem), Offset);
	return result;
}


/*
int deleteOffset2(int fd, int Offset)
{
    struct DataItem dummyItem,data;
    int myoffset=-1;
    ssize_t result = pread(fd,&data,sizeof(DataItem), Offset); if(result <= 0) { return -1; }
    if(data.next!=-1)
    {
        for(Offset=data.next;Offset<FILESIZE;Offset+=sizeof(DataItem))
            {
                result = pread(fd,&data,sizeof(DataItem), myoffset); if(result <= 0) { return -1; } 
                if (hashCode(data.key) == hashCode(item->key) { break;  } 
            }
    }
	dummyItem.valid = 0;
	dummyItem.key = -1;
	dummyItem.data = 0;
    if(myoffset!=-1)
    {   }
	result = pwrite(fd,&dummyItem,sizeof(DataItem), Offset);

	return result;



}
*/


int deleteOffset3(int fd, int Offset)
{
	struct DataItem dummyItem,data;
    ssize_t result = pread(fd,&data,sizeof(DataItem), Offset); if(result <= 0) { return -1; }
	dummyItem.valid = 0;
	dummyItem.key = -1;
	dummyItem.data = 0;
	result = pwrite(fd,&dummyItem,sizeof(DataItem), Offset);

	return result;
}


