#include <stdio.h> 
#include <fcntl.h> 
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>

int pf=-1;
int flag=0;
char a[6];
long long int counter=0;
long long int current=0;
long long int buffer= 1000000;
char MESSAGE[200];

char *strrev(char *str)
{
  int i=0;
  char *p1, *p2;

  if (! str || ! *str)
    return str;                     //ye func basically likhne ke liye h rev krke
  p1 = str;
  p2 = str+strlen(str)-1; 
  while(p1<p2)
  {
    *p1 ^= *p2;
    *p2 ^= *p1;
    *p1 ^= *p2;
    ++p1;
    --p2;
    i++;
  }

  //printf("%d",i);
  return str;
}

void reverse_multiple(int f2, int f1) {
  int temp=0;
  char *data = (char *) calloc(buffer,sizeof(char));      //data mein humne buffer size memory allocate krdi h
  temp = read(f2, data, buffer) ;       //ab hum buffer jitni bytes file se read kra kre h data m

  if (flag<temp) {
    current=current+temp;            //hum bytes gin rhe h current m plus kr krke
    reverse_multiple(f2, f1);
    int pr = (current*100)/counter;
    int i=0;
    if(!(pr<pf))
    {
      pf = pr;
      convert(pr);
      write(1,&a,strlen(a));      //ab hum new file m likhne ke liye dheere dheere chzzein daal rhe h usse pehle hum use vapis char m convert krrhe h
      i++; 
      fflush(stdout);
      //printf("%d ",i);
    }
    data = strrev(data);                        
    write(f1, data, temp);      //uske bd str rev krke new file m likh rhe h
  }
}

void convert(int curr)                    
{
  for (int i = 0; i < 5; i++) a[i]=' ';
  
  int i=0;
  a[0]='\r';
  a[5]='%';
  while(curr)
  {
    int temp=curr%10+48;
    char c_temp = (char)(temp);
    a[3-i]=c_temp;
    curr=curr/10;
    i+=1;
  }
}


int main(int argc, char* argv[]) {

	if(argc == 1 || argc >= 3)
  {
      sprintf(MESSAGE, "You need to give the name of single file to be reversed. Aborting!");
      puts(MESSAGE);
      exit(1);
  }

  struct stat stats;
  if (stat(argv[1], &stats) == 0)
    {
        if (!S_ISREG(stats.st_mode))
        {
            sprintf(MESSAGE, "You need to enter a valid file!\n");
            write(2, MESSAGE, strlen(MESSAGE));
            exit(1);
        }
    }

  char delim[] = "/";
  char str[100000];
  strcpy(str,argv[1]);
  int init_size = strlen(str);
  char *ptr = strtok(str, delim);
  char str1[100000];

  while(ptr != NULL)
  {
    strcpy(str1,ptr);
    ptr = strtok(NULL, delim);
  }
  int dir;
  struct stat directory;
  if (stat("Assignment", &directory) != 0)
        dir = mkdir("Assignment", 0700);
    else{
        sprintf(MESSAGE, "Directory already exists. File contents will be over-written if a file of the same name exists in the directory.");
        puts(MESSAGE);
    }
 // int dir = mkdir("Assignment",0700);

  char str_t[] = "Assignment/";
  strcat(str_t,str1);

  int f1 = open(str_t, O_WRONLY | O_CREAT, 0600); //fileout
  if (f1<0) { 
    perror("c1"); 
    exit(1);                                    
  }

  int f2 = open(argv[1], O_RDONLY);               //fileIn
  if (f2<0) { 
    perror("c1"); 
    exit(1); 
  }

  int fileTemp = open(argv[1], O_RDONLY); //new file read krne ke liye open ki h
  counter = lseek(fileTemp,0,SEEK_END); //counter ko last m laga diya hai 
  close(fileTemp);

  write(1,"  0 % completed",sizeof("      completed"));
  reverse_multiple(f2, f1);             //reverse function ko call kiya h
  close(f1);
  close(f2);
  write(1,"\nDone\n",sizeof("\nDone\n"));
  return 0;
}