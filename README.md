# README

# Question-1: 

In this question, we have to reverse a given file and then create a folder with the reversed file in it. Also, the permissions for both the files have been specified.
## Logic for the code
So, I have read <buffer> bytes from input file and store it into buffer variable. But before writing, I call this function again and again  (ie.recursively). Now this happens until there is nothing left to read, then I  write using LIFO (Last In, First Out). Therefore reverse of file is present in Output file.

**Error handling for Question-1**
Arguments - ./a.out <path_to_file>
The only valid argument that is acceptable is the name of the file that you want to reverse along with it's path. Take a look to the response of the program to different kinds of arguments below :  

1. ./a.out <name_of_any_directory> - It will show an error as "You need to enter a valid file!". With this, it will terminate.

2. ./a.out asdfghj <path_to_file> (Wrong number of arguments) - It will show error as "You need to give the name of single file to be reversed. Aborting!". With this, it will terminate.

3. If already the folder with Assignment name exists (Running the program again) - It will show "Directory already exists. File contents will be over-written if a file of the same name exists in the directory". It doesn't terminate after that. It keeps looking whether the file inside is reversed or not.

4. If the entered file does not exist - The error will be thrown as "c1: No such file or directory". 

# Question-2:

In this question we have to output whether the directory has been created, file has been reversed and all the permissions have been given correctly or not. 
## Logic for the code
So, Just like the previous question, I read recursively here too. Now in place of writing to another file, I compare it with normal front read Buffer variable. If they aren't same I return FALSE else I return TRUE. The order of the output is like New file, Old file and then Directory.

**Error handling for Question-2**
Arguments - ./a.out <path_to_new_file>  <path_to_old_file>  <directory> 
If we give arguments other than that, it will throw an appropriate error in response. Take a look to the response of the program to different kinds of arguments below : 

1. ./a.out <name_of_directory> <path_to_old_file> <directory> (If a directory is given instead of any of the two files) - It will show "Enter valid New file/Old File. Aborting!" and then the execution of the program will terminate then and there.

2. ./a.out <path_to_new_file> <path_to_old_file> <any_file> (If we give name of a file instead of the directory) - It will show "Directory Error: No such file or directory" and the programe execution will terminate immediately.

3. Wrong number of arguments - If more or less than 4 arguments are entered then it will throw error as Insufficient "number of argument" and terminate. 

4. If the entered file does not exist - The error will be thrown as "c1: No such file or directory".
