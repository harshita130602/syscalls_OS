#include<stdio.h> 
#include <fcntl.h> 
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
int pf=0;
int flag=0;
int f2_original;
char err[1000];
long long int buffer = 1000000;
int comp=-1;

char *strrev(char *str)
{
  int i=0;
  char *p1, *p2;

  if (! str || ! *str)
    return str;
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
  return str;
}

void revcheck_multiple(int f2) {
	int i=0;
	int temp;
	char *data = (char *) calloc(buffer,sizeof(char));			//allocating buffer size memory  
	temp = read(f2, data, buffer) ;
	if (flag<temp) {
		if(flag==pf) revcheck_multiple(f2);
		if(comp==pf) return 0;
		data = strrev(data);
		char *data2 = (char *) calloc(buffer,sizeof(char));		//now checking both datas
		int temp2;
		temp2 = read(f2_original, data2, temp);
		if(strcmp(data,data2)!=0)								//if they aren't same then save -1 in pf
			pf = comp;
	}
}

char owner[100]="User has ";
char perm[100]="read";
char txt[]=" permission on ";
char fil[100] ="newfile";
char retStr[500]="";

void concat(int j)
{
	int i=0;
	flag=0;
	memset(retStr, 0, strlen(retStr));
	strcpy(retStr,owner);
	strcat(retStr,perm);
	strcat(retStr,txt);
	strcat(retStr,fil);
	if(flag+1==j) strcat(retStr,": YES\n");
	else strcat(retStr,": NO\n");
!	write(1,retStr,sizeof(retStr));
}

void permissions(char *file,char * strx){
	int i=0;
	struct stat st;
	flag=0;
	if(flag == stat(file, &st)){
		mode_t permis = st.st_mode;
		strcpy(fil,strx);
		strcpy(owner,"User has ");
		strcpy(perm,"read");
		if(permis & S_IRUSR) concat(1);
		else concat(0);
		//i++;

		strcpy(owner,"User has ");
		strcpy(perm,"write");
		if(permis & S_IWUSR) concat(1);
		else concat(0);
		//i++;

		strcpy(owner,"User has ");
		strcpy(perm,"execute");
		if(permis & S_IXUSR) concat(1);
		else concat(0);
		write(1,"\n",sizeof("\n"));

		strcpy(owner,"Group has ");
		strcpy(perm,"read");
		if(permis & S_IRGRP) concat(1);
		else concat(0);

		strcpy(owner,"Group has ");
		strcpy(perm,"write");
		if(permis & S_IWGRP) concat(1);
		else concat(0);

		strcpy(owner,"Group has ");
		strcpy(perm,"execute");
		if(permis & S_IXGRP) concat(1);
		else concat(0);
		write(1,"\n",sizeof("\n"));

		strcpy(owner,"Others have ");
		strcpy(perm,"read");
		if(permis & S_IROTH) concat(1);
		else concat(0);

		strcpy(owner,"Others have ");
		strcpy(perm,"write");
		if(permis & S_IWOTH) concat(1);
		else concat(0);

		strcpy(owner,"Others have ");
		strcpy(perm,"execute");
		if(permis & S_IXOTH) concat(1);
		else concat(0);
		write(1,"\n",sizeof("\n"));
	}
}

int main(int argc, char* argv[]) 
{
	char message[200];
	int i=0;
	struct stat stats;
	if(argc != 4)
	{
		strcpy(err, "Insufficient number of argument \n");
		write(1,err,strlen(err));
		exit(1);
	}
	if (stat(argv[1], &stats) == 0)
    {
        if (!S_ISREG(stats.st_mode))
        {
            sprintf(message, "Enter valid New file. Aborting!\n");
            write(2, message, strlen(message));
            return 0;
        }
    }
	if (stat(argv[2], &stats) == 0)
    {
        if (!S_ISREG(stats.st_mode))
        {
            sprintf(message, "Enter valid old file. Aborting!\n");
            write(2, message, strlen(message));
            return 0;
        }
    }
	int f2 = open(argv[2], O_RDONLY);				//jo file reverse krani thi wo check krrhe h ki exist krrhi h ya nhi
	if (f2<flag){ 
		perror("c1"); 
		exit(1);
	}
	f2_original = open(argv[1], O_RDONLY);			//new file check krrhe h ki exist krrhi h ya nhi
	if (f2_original<flag){ 
		perror("c1"); 
		exit(1);
	}	
	int f2_original_t = open(argv[1], O_RDONLY); //i++;		//reversed file
	int f2_t = open(argv[2], O_RDONLY);	//i++;			//jo file reverse krni thi 
	char str[100] = "Directory is created: ";			//checking if the 3rd argument is directory and if that exists or not

	if (stat(argv[3], &stats) == 0)
    {
        if (S_ISDIR(stats.st_mode))
        {
            strcat(str,"YES\n");
			write(1,str,sizeof(str));
			fflush(stdout);
        }
        else
        {
            strcat(str,"NO\n");
			write(1,str,sizeof(str));
			fflush(stdout);
			exit(0);
        }
    }
    else{
        perror("\nDirectory Error");
		exit(0);
    }

	int size1 = lseek(f2_t,0,SEEK_END);				// size of old file
	close(f2_t);
	int size2 = lseek(f2_original_t,0,SEEK_END);	//size of new file
	close(f2_original_t);

	if(size1==size2)								//if they are same
	{
		write(1,"Checking\r",sizeof("Checking\r"));
		revcheck_multiple(f2);						//calling rev check function
	}
	else pf=-1;										//else they are not same if size isnt same
	
	close(f2);
	strcpy(str,"Whether file contents are reversed in newfile: ");

	if(pf!=-1)
	{
		strcat(str,"YES\n\n");					//if p!=-1 then they are same else no
		write(1,str,sizeof(str));
		fflush(stdout);
	}
	else 
	{
		strcat(str,"NO\n");
		write(1,str,sizeof(str));
		fflush(stdout);
		exit(0);
	}
	i+=1;
	//perror("c1");
	permissions(argv[1],"New file");
	fflush(stdout);
	permissions(argv[2],"Old file");
	fflush(stdout);
	permissions(argv[3],"Directory");
	fflush(stdout);
}