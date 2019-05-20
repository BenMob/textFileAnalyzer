/***************************************************************                                                                                  
By Benjamin Ombeni                                                                                                                                                                                     
                                                                                                                                       
This app analyzes a text file with a (.dat) extension. 
At run time, the user will have a choice between viewing info
for one letter of the alphabet (A - Z) or view info for all letters of the alphabet.                                                                                               
***************************************************************/
#include <iostream>  //for cin & cout                                                                                                  
#include <fstream> //for files                                                                                                         
#include <cstdlib>  //for exit()                                                                                                       
#include <iomanip> //for setw()                                                                                                        
using namespace std;
#include "myC-StringManip.h"  //fo my c-string functions                                                                                 

const int MAX = 30;  //accomodates up to 29 letters + the NULL terminator                                                              
const int SIZE = 26;  //26 letters in the alphabet                                                                                     
typedef char cstr[MAX];  //Giving an alias "cstr" to c-string with 30 slots                                                            

struct Let
{
  int count;  //number of character in each word                                                                                       
  cstr shortest;  // shortest word                                                                                                     
  cstr longest;  // longest word                                                                                                       
};

//function prototypes                                                                                                                           
void initializeArray(Let ar[]);
void readFile(Let ar[]);
void processWord(const cstr w, Let ar[]);
void printInfoOnOneLetter(const Let ar[]);
void printInfoOnAllLetters(const Let ar[]);

int main()
{
  int choice; //user's choice                                                                                                          
  Let letAr[SIZE];  //declaring the array                                                                                              
  initializeArray(letAr);  //initializing the array                                                                                    
  readFile(letAr);  //reading the input file and processing every word individualy                                                     

  do
    {
      cout <<endl;
      cout <<"1. Show information for all letters." <<endl;
      cout <<"2. Show information for one letter." <<endl;
      cout <<"3. Quit." <<endl;
      cout <<"Enter your choice here: " ;
      cin >> choice;

      switch(choice)
        {
        case 1:
          printInfoOnAllLetters(letAr);
          break;
        case 2:
          printInfoOnOneLetter(letAr);
          break;
        case 3:
          cout <<endl <<"Thank you for using the system. Goodbye." <<endl;
          break;
        default:
          cout <<"Invalid Choice. Please try again" <<endl;
        }
    }while(choice != 3);

  cout <<endl;


  return 0;
}

/*************************************************                                                                                     
This function will initialize any array of type Let                                                                                    
                                                                                                                                       
Let ar[]: an array of type Let                                                                                                         
**************************************************/
void initializeArray(Let ar[])
{
  for (int i = 0; i < SIZE; i++)
    {
      ar[i].count = 0;  //initializes count to zero                                                                                    
      myStrcpy(ar[i].shortest,"xxxxxxxxxxxxxxxxxxxxxxxxxxxxx"); //initializes shortest to longest word possible(29 xs and the last spot of the NULL character)                                                                                                               
      myStrcpy(ar[i].longest,"");   //initialize shortest word to extremely short                                                    
    }
}

/***************************************************                                                                                   
This funtion will read data from an input file and                                                                                     
and send each word to be processed                                                                                                     
Let ar[]: An array of type let                                                                                                         
***************************************************/
void readFile(Let ar[])
{
  cstr word;  //will store each word before sending it to be processed                                                                 
  ifstream fin;

  fin.open("textFile.dat");  //open input file                                                                                         
  if(!fin)  //checks if input file exists in the directory                                                                             
    {
      cout <<"INPUT FILE DOES NOT EXIST!" <<endl;
      exit(1); //terminates the program                                                                                                
    }
  else
    {
      fin >> word; //collects the first character in the input file                                                                    
        while(fin)
        {
          processWord(word,ar);  //passes one word at a time to be processed                                                       
          fin >> word;
        }
    }

  fin.close(); //closes input file                                                                                                     
}

/**********************************************************                                                                            
This function will process one word at a time in the array                                                                             
                                                                                                                                       
cstr w: a C-string word                                                                                                                
Let ar[]: an array of type Let                                                                                                         
**********************************************************/
void processWord(const cstr w, Let ar[])
{
  ar[myToUpper(w[0])-'A'].count++;  //increment the array spot corresponding to the first letter of the word                           

  //updating shortest                                                                                                                  
  if(myStrlen(w) < myStrlen(ar[myToUpper(w[0])-'A'].shortest))
    myStrcpy(ar[myToUpper(w[0])-'A'].shortest,w);

  //updating longest                                                                                                                   
  if(myStrlen(w) > myStrlen(ar[myToUpper(w[0])-'A'].longest))
    myStrcpy(ar[myToUpper(w[0])-'A'].longest,w);
}

/**************************************************************                                                                        
This function will show info for one letter picked by the user                                                                         
Let ar[]: an array of type Let                                                                                                         
***************************************************************/
void printInfoOnOneLetter(const Let ar[])
{
  cout <<endl;
  char L;  //will store the letter that the user is interested in                                                                      
  cout <<"Which letter are you interested in ?: ";
  cin >> L;  //getting user's letter choice                                                                                            
  L = myToUpper(L);  //changes L into a capital                                                                                        
  cout <<endl;

  if(ar[L - 'A'].count != 0)  //there is at least a word beginning with the user's chosen letter                                       
    {
      cout <<"Frequency: " <<ar[L - 'A'].count <<endl;
      cout <<"Longest: " <<ar[L - 'A'].longest <<endl;
      cout <<"Shortest: " <<ar[L - 'A'].shortest <<endl;
    }
  else //there is no word beginning with the user's chosen letter                                                                      
    {
      cout <<"Frequency: " <<ar[L - 'A'].count <<endl;
    }
}

/**********************************************                                                                                        
This function will show info on all the letters                                                                                        
Let ar[]: an array of type Let                                                                                                         
***********************************************/

void printInfoOnAllLetters(const Let ar[])
{
  cout <<endl;
  char L;  //starting point for letter                                                                                                 
  for (int i = 0, L = 'A'; i < SIZE; i++, L++)  //showing info for every letter in the alphabet                                        
    {
      cout <<(char)L <<setw(5) <<ar[i].count <<": ";
      for(int x = 0; x < ar[i].count; x++)  //prints stars                                                                             
        {
          cout <<"-";
        }
      if(ar[i].count != 0)  //prints longest and shortest only for letters where count >  0                                            
      cout << "  ("<<ar[i].longest <<"), (" <<ar[i].shortest <<")" <<endl;
      else cout <<endl;
    }
}

