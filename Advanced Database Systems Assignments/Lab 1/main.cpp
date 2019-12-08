//============================================================================
// Name        : hashskeleton.cpp
// Author      : 
// Version     :
// Copyright   : Code adapted From https://www.tutorialspoint.com/
// Description : Hashing using open addressing
//============================================================================

#include "readfile.h"

void insert(int key,int data);
int deleteItem(int key);
struct DataItem * search(int key);


int filehandle;   //handler for the database file
/* DBMS (DataBase Management System) needs to store its data in something non-volatile
 * so it stores its data into files (manteqy :)).

 * Some DBMS or even file-systems constraints the size of that file. 

 * for the efficiency of storing and retrieval, DBMS uses hashing 
 * as hashing make it very easy to store and retrieve, it introduces 
 * another type of problem which is handling conflicts when two items
 * have the same hash index

 * In this exercise we will store our database into a file and experience
 * how to retrieve, store, update and delete the data into this file 

 * This file has a constant capacity and uses external-hashing to store records,
 * however, it suffers from hashing conflicts.
 * 
 * You are required to help us resolve the hashing conflicts 

 * For simplification, consider the database has only one table 
 * which has two columns key and data (both are int)

 * Functions in this file are just wrapper functions, the actual functions are in openAddressing.cpp

*/

void test1(int FH)
{
   DisplayFile(filehandle);
   insert(1, 20);
   insert(2, 70);
   insert(42, 80);
   insert(4, 25);
   insert(12, 44);
   insert(14, 32);
   insert(17, 11);
   insert(13, 78);
   insert(37, 97);
   insert(11, 34);
   insert(22, 730);
   insert(46, 840);
   insert(9, 83);
   insert(21, 424);
   insert(41, 115);
   insert(71, 47);
   insert(31, 92);
   insert(73, 45);
   DisplayFile(filehandle);
   search(13);
   deleteItem(31);
   DisplayFile(filehandle);
   close(filehandle);
}

void test2(int FH)
{

   DisplayFile(filehandle);
   insert(10, 20);
   insert(20, 70);
   insert(12, 80);
   insert(22, 25);
   insert(32, 44);
   insert(42, 32);
   insert(52, 11);
   insert(19, 78);
   insert(29, 97);
   insert(39, 34);
   insert(49, 730);
   insert(59, 840);
   insert(69, 83);
   insert(79, 424);
   insert(89, 115);
   insert(99, 47);
   insert(119, 92);
   insert(129, 45);
   DisplayFile(filehandle);
   search(10);
   search(129);
   deleteItem(129);
//7. Display the final data base
   DisplayFile(filehandle);
   // And Finally don't forget to close the file.
   close(filehandle);
}

void test3(int FH)
{
   DisplayFile(filehandle);
   insert(1, 20);
   insert(2, 70);
   insert(42, 80);
   insert(4, 25);
   insert(41, 33);
   insert(71, 47);
   insert(31, 92);
   insert(73, 32);
   DisplayFile(filehandle);
   search(1);
   search(73);
   search(4);
   DisplayFile(filehandle);
   close(filehandle);
}


void test4(int FH)
{
   DisplayFile(filehandle);
   insert(32, 44);
   insert(42, 32);
   insert(52, 11);
   insert(19, 78);
   insert(29, 97);
   insert(39, 34);
   insert(49, 730);
   insert(59, 840);
   insert(69, 83);
   insert(79, 424);
   DisplayFile(filehandle);
   search(59);
   DisplayFile(filehandle);
   close(filehandle);
}


void test5(int FH)
{
   DisplayFile(filehandle);
   insert(32, 44);
   insert(42, 32);
   insert(52, 11);
   insert(19, 78);
   insert(69, 83);
   insert(79, 424);
   DisplayFile(filehandle);
   search(79);
   search(12);
   search(32);
   deleteItem(19);
   DisplayFile(filehandle);
   close(filehandle);
}


void test6(int FH)
{
   DisplayFile(filehandle);
   insert(42, 32);
   insert(52, 11);
   insert(19, 78);
   insert(29, 97);
   insert(39, 34);
   insert(49, 730);
   insert(59, 840);
   insert(69, 83);
   insert(79, 424);
   insert(89, 115);
   insert(99, 47);
   insert(119, 92);
   DisplayFile(filehandle);
   search(13);
   search(89);
   search(19);
   deleteItem(47);
   DisplayFile(filehandle);
   close(filehandle);
}


int main(){

//here we create a sample test to read and write to our database file
    
  //1. Create Database file or Open it if it already exists, check readfile.cpp
   filehandle = createFile(FILESIZE,"openaddressing");
    test2(filehandle);
    
   // And Finally don't forget to close the file.
   close(filehandle);
   return 0;



}

/* functionality: insert the (key,data) pair into the database table
                  and print the number of comparisons it needed to find
    Input: key, data
    Output: print statement with the no. of comparisons
*/
void insert(int key,int data){
     struct DataItem item ;
     item.data = data;
     item.key = key;
     item.valid = 1;
     item.next = -1;
     int result= insertItem(filehandle,item);  //TODO: implement this function in openAddressing.cpp
     printf("Insert: No.of searched records:%d\n",abs(result));
}

/* Functionality: search for a data in the table using the key

   Input:  key
   Output: the return data Item
*/
struct DataItem * search(int key)
{
  struct DataItem* item = (struct DataItem *) malloc(sizeof(struct DataItem));
     item->key = key;
     int diff = 0;
     int Offset= searchItem(filehandle,item,&diff); //this function is implemented for you in openAddressing.cpp
     printf("Search: No of records searched is %d\n",diff);
     if(Offset <0)  //If offset is negative then the key doesn't exists in the table
       printf("Item not found\n");
     else
        printf("Item found at Offset: %d,  Data: %d and key: %d\n",Offset,item->data,item->key);
  return item;
}

/* Functionality: delete a record with a certain key

   Input:  key
   Output: return 1 on success and -1 on failure
*/
int deleteItem(int key){
   struct DataItem* item = (struct DataItem *) malloc(sizeof(struct DataItem));
   item->key = key;
   int diff = 0;
   int Offset= searchItem(filehandle,item,&diff);
   printf("Delete: No of records searched is %d\n",diff);
   if(Offset >=0 )
   {
    return deleteOffset(filehandle,Offset);
   }
   return -1;
}
