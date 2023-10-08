


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dirent.h> 
#include <unistd.h>
#include <time.h>
FILE *fpLog;
time_t tm;

void print_index();
void terminate_op();
void show_dir();
void createfile();
void copyfile();
void deletefile();
void showfile();
void file_op();
void appendline(char name[]);
void deleteline(char name[]);
void insertline(char name[]);
void showline(char name[]);
void line_op();
void general_op();
void search();

int main(){
  int attemps;
  char mode[2];
  time(&tm);
  fpLog=fopen("logfile", "a+");
  while(1){
    attemps=0;
    do{
      if(attemps==1){
        printf("\n----- Invalid mode entered. Try again! -----\n");}
      print_index();
      //fseek(stdin,0,SEEK_END); //clears buffer
      fgets(mode, sizeof(mode), stdin);
      fseek(stdin,0,SEEK_END); //clears buffer
      //fflush();
      attemps=1;
    }while((mode[0]<'1' || mode[0]>'5') && mode[0]!='x');
    if(mode[0] == 'x'){
      printf("\n - - - - - - - - - - - - - - - - -  -\n");
      printf("|                                    |\n");
      printf("| Program terminated successfully! :)|\n");
      printf("|                                    |\n");
      printf(" - - - - - - - - - - - - - - - - -  -\n");
      //printf("\n\n-----------------------------\n");
      break;
    }
    switch(mode[0]){
      case '1': file_op();
      break;
      case '2': line_op();
      break;
      case '3' : general_op();
      break;
      case '4': search();
      break;
      case '5': show_dir();
      break;
    }
  }
  fclose(fpLog);
  return 0;
}

void print_index(){
  printf("\n----- Main Menu -----, \n\n");
  printf("\n1 - file operations\n\n");
  printf("2 - line operations\n\n");
  printf("3 - general operations\n\n");
  printf("4 - search a string in a file\n\n");
  printf("5 - show directories\n\n");
  printf("x - terminate program\n\n" );
  printf("Choose operation mode: ");
}
void terminate_op(){
  printf("\n\n----- Operation terminated ----- \n" );
}
void show_dir() {
  DIR *d;
  struct dirent *dir;
  d = opendir(".");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      printf("%s\n", dir->d_name);
    }
    closedir(d);
  }
}
void createfile(){
  FILE *fp;
  char name[255];
  char content[255];
  int i=0;
  int counter=0;
  int counter2=0;
  char countin='2';
  char operationlog[255];
  char operationlog2[255];
    printf("\n\nInsert file name to create or press enter to terminate operation: ");
    fgets(name, sizeof(name), stdin);
    fseek(stdin,0,SEEK_END); //clears buffer
    name[strlen(name)-1]='\0';
    if(name[0]=='\0'){
      return;
    }
    else{
      fp= fopen(name,"w");
      if(fp == NULL){ //https://www.quora.com/How-do-I-write-a-program-in-C-to-create-a-new-file-with-a-name-taken-from-the-user
        printf("\n----- Could not create file. Maybe locked or being used by another application? ------\n");
        return;
      }
      else{
       // fclose(fp);
        fprintf(fpLog,"Created %s file, %s \n",name,ctime(&tm));
        counter2=0;
        while(1){
          if(counter2==0)
            printf("\n\nEnter 1 if you want to write a line to the new file or enter 0 to terminate: ");
          else printf("\n\nEnter 1 if you want to write another line to the new file or enter 0 to terminate: ");
          scanf("%c",&countin );
          fseek(stdin,0,SEEK_END); //clears buffer
        if(countin=='1'){
          printf("Enter a line content you want to add:\n");
          fgets(content, sizeof(content), stdin);
          fseek(stdin,0,SEEK_END); //clears buffer
          fputs(content, fp);
         // operationlog[0]='\0';
          fprintf(fpLog,"Added a line to the %s file, %s \n",name,ctime(&tm));
          counter2++;
        }
        else if(countin=='0'){
          break;
        }
      }
      fclose (fp);
    }
  }
}
void copyfile(){ //this function will have parameters but can also work without parameters
  FILE *fp;
  char name[255];
  char name2[255];
  FILE *fp2;
  int counter=0;
  int counter2=0;
  char data;
  fp=NULL;
  fp2=NULL;
    do{
      if(counter>0){
        printf("\nCould not open file. Maybe locked or being used by another application?\n");
        printf("\n\nInsert another file name you want to copy or press enter to terminate: " );
      }
      else printf("\n\nInsert file name you want to copy or press enter to terminate: ");
      fgets(name, sizeof(name), stdin);
      fseek(stdin,0,SEEK_END); //clears buffer
      name[strlen(name)-1]='\0';
      if(name[0]=='\0')
        return;
      fp= fopen(name,"r");
      counter++;
    }while(fp==NULL);
    do{
        if(counter2>0){
          //  fseek(stdin,0,SEEK_END); //clears buffer
          printf("\nCould not open file. Maybe locked or being used by another application?\n");
          printf("\nInsert another file name you want to paste or press enter to terminate: ");

        }
        else  printf("\nInsert file name you want to paste or press enter to terminate: ");
        fgets(name2, sizeof(name2), stdin);
        fseek(stdin,0,SEEK_END); //clears buffer
        name2[strlen(name2)-1]='\0';
        if(name2[0]=='\0'){
          fclose(fp); //close the already open file since no needed
          return; //operation terminated
        }
        counter2++;
        fp2= fopen(name2,"w");
    }while(fp2==NULL);
    while ((data = getc(fp)) != EOF){
      fputc(data,fp2);
    }
  printf("\nFile copied successfully!");
  fprintf(fpLog,"Copied the content of the %s the file to the %s file, %s \n",name,name2,ctime(&tm));
  fclose (fp);
  fclose(fp2);
}
void deletefile(){
  int counter=0;
  char name[255];
  char operationlog[256];
  FILE *fp;
 /* if(counter>0)
    printf("|\n|\nEnter another file name to delete or press enter to terminate:\n"); */
  printf("\nEnter file name to delete or press enter to terminate: ");
  fgets(name, sizeof(name), stdin);
  fseek(stdin,0,SEEK_END); //clears buffer
  name[strlen(name)-1]='\0';
  if(name[0]=='\0')
    return;
  if (remove(name) == 0){
    printf("\n----- Deleted successfully -----\n\n");
    fprintf(fpLog,"Deleted the %s file, %s\n",name,ctime(&tm));
  }
  else
    printf("\nUnable to delete the file\n\n");
}
void showfile(){
  int counter;
  FILE *fp;
  char name[255];
  char data;
  char operationlog[256];
    counter=0;
    do{
      if(counter>0)
        printf("\n----- Error! File does not exist -----\n\nEnter another file name to show or press enter to terminate:\n");
      else printf("\n\nEnter file name to show or press enter to terminate:\n");
      fgets(name, sizeof(name), stdin);
      fseek(stdin,0,SEEK_END); //clears buffer
      name[strlen(name)-1]='\0';
      if(name[0]=='\0')
        return;
      fp= fopen(name,"r");
      counter++;
    }while(fp==NULL);
    printf("\n----- Beginning of File -----\n\n");
    //fseek(stdin,0,SEEK_END); //clears buffer
    while ((data = getc(fp)) != EOF)
        printf("%c", data);
    printf("\n-------- End of File ---------\n\n");
     fprintf(fpLog,"Showed the %s file, %s\n",name,ctime(&tm));
    fclose(fp);
}
void file_op(){
  char mode[2];
  while (1) {
    printf("\n----- File Menu -----\n" );
    printf("\n1 - create file\n\n");
    printf("2 - copy file\n\n");
    printf("3 - delete file\n\n");
    printf("4 - show file\n\n");
    printf("x - terminate file operation\n\n" );
    printf("Choose operation: ");
    fgets(mode, sizeof(mode), stdin);
    fseek(stdin,0,SEEK_END); //clears buffer
    if(mode[0]=='x')
      return ;
    //fseek(stdin,0,SEEK_END); //clears buffer
    switch(mode[0]){
      case '1': createfile();
        break;
      case '2':  copyfile();
        break;
      case '3' : deletefile();
        break;
      case '4' : showfile();
    }
  }
}
void appendline(char name[]){
  FILE *fp;
  int counter=0;
  char countin;
  char content[1024];
  char operationlog[256];
  fp= fopen(name,"a");//open a filestream to append data to the file - pointer is at the last position of the file
  printf("\n\nEnter line content you want to write to the end of the file or press enter to terminate\n");
  fgets(content, sizeof(content), stdin); //user inserts content that wants to add to the end of the file
  fseek(stdin,0,SEEK_END); //clears buffer
  if(content[0]=='\n') //when the user wants to terminate function
    return;
  fputs(content, fp);
  printf("\nLine entered successfully!\n");
 fprintf(fpLog,"Added a line at the end of the file %s, %s \n",name,ctime(&tm));
  fclose(fp); //close file
  appendline(name);//call the function again
}

void deleteline(char name[]){
  FILE *fp;
  FILE *fp2;
  fp= fopen(name,"r");
  int counter=0;
  char data;
  int linenum=0;
  int num;
  int i=0;
  char operationlog[256];
  printf("\nEnter number of line you want to delete or enter 0 to terminate: ");
  scanf("%d",&num);
  if(num==0){
    fclose(fp); //close file
    return; //exit function
  }
  fp2= fopen(".new","w"); //choosing this name because in linux it means invisible file- no chance this is used by others
  while ((data = getc(fp)) != EOF){
    if(i!=(num-1))
        fputc(data,fp2);
    if(data== '\n')
      i++;
    }
    fclose(fp); //close first file
    fclose(fp2); //close second file
    fp=fopen(name,"w");
    fp2= fopen(".new","r");
    while ((data = getc(fp2)) != EOF)
      fputc(data,fp);
    remove(".new");
    fprintf(fpLog,"Deleted line %d from the %s file, %s \n",num,name,ctime(&tm));
    fclose(fp);
    fclose(fp2);
    deleteline(name); //call the function again
}

void insertline(char name[]){
  FILE *fp;
  FILE *fp2;
  fp= fopen(name,"r+");
  int counter=0;
  char data;
  int linenum=0;
  int num;
  int i=0;
  char content[1024];
  char operationlog[256];
  printf("\n\nEnter number of line you want to create or enter 0 to terminate: ");
  //fseek(stdin,0,SEEK_END); //clears buffer
  scanf("%d",&num);
  fseek(stdin,0,SEEK_END); //clears buffer
  if(num==0){
    fclose(fp);
    return;
  }
  printf("\nEnter line content or press enter to terminate:\n");
  //fseek(stdin,0,SEEK_END); //clears buffer
  fgets(content, sizeof(content), stdin); //inputs line
  fseek(stdin,0,SEEK_END); //clears buffer
   if(content[0]=='\n'){
    fclose(fp); //close file
    return ; //exit function
  }
  fp2= fopen(".new","w"); //choosing this name because in linux it means invisible file- no chance this is used by others
  while (i!=(num-1)){
   // fseek(stdin,0,SEEK_END); //clears buffer
    data=getc(fp);
    if(data==EOF){ //if the number of line entered exceeds the numbers of the lines of the file
     fputc('\n', fp2); //create a new line until the one entered is found
    }
    else {
    //  fseek(stdin,0,SEEK_END); //clears buffer
      fputc(data,fp2);
    }
    if(data=='\n' || data==EOF)
      i++;
  }

  fprintf(fp2,"%s",content);//adds the new line to the new file
  fseek(stdin,0,SEEK_END); //clears buffer
  while((data=getc(fp))!=EOF){ //then adds the rest of the file to the new file
    // fseek(stdin,0,SEEK_END); //clears buffer
    fputc(data,fp2);
  }
  fclose(fp); //close first file
  fclose(fp2); //close second file
  //copies the new file with the new line to the existing one
  fp=fopen(name,"w"); 
  fp2= fopen(".new","r");
  while ((data = getc(fp2)) != EOF){
      fputc(data,fp);
  }

  fclose(fp);
  fclose(fp2);
  remove(".new"); //removes the new file
  printf("\nLine created successfully!\n" );
 fprintf(fpLog,"Added a string in the line line %d of the %s file, %s \n",num,name,ctime(&tm));
  insertline(name);
}
void showline(char name[]){
  FILE *fp;
  int i=0;
  char data;
  int isfound;
  int num;
  char operationlog[256];
  FILE *fp2;
  fp2=fp;
  fp= fopen(name,"r");
  i=0;
  isfound=0;
  printf("\n\nEnter number of line you want to show or enter 0 to terminate: ");
  //fseek(stdin,0,SEEK_END); //clears buffer
  scanf("%d",&num);
//  fseek(stdin,0,SEEK_END); //clears buffer
  if(num==0){ //if the user inputs 0 - means end function
    fclose(fp);
    return;
  }
  while ((data = getc(fp)) != EOF){ //read every character until the end of the file
    if(data== '\n'){ //if the end of line
      if(isfound==1){ //and it's the line that we wanted to print
        fprintf(fpLog,"Showed the line %d of the file %s, %s\n",num,name,ctime(&tm));
        fclose(fp); //close open file stream
        return; //terminate line operation
      }
      i++; //increment line counter
    }
    else if(i==(num-1)) { //if it's the line the user wants to output
      printf("%c",data); //print the character
      isfound=1;
    }
  }
  if(isfound==0){ //if the line has not been found
    printf("\n------Line number not found------ \n");
  }
  fclose(fp); // close open file stream
  showline(name); //call the function again
}

void line_op(){
  int attemps=0;
  int counter=0;
  int size;
  char mode[2];
  char name [255];
  FILE *fp;
    do{
      if(counter==1)
          printf("\n----- Error - No such a file exists! -----\n\n" );
      printf("\n>>>Enter file name to access line operations or press enter to terminate:\n");
     // fseek(stdin,0,SEEK_END); //clears buffer
      fgets(name, sizeof(name), stdin); //inputs file name
      fseek(stdin,0,SEEK_END); //clears buffer
      name[strlen(name)-1]='\0';
      if(name[0]=='\0')
        return;
      fp= fopen(name,"r"); //opens file that the name has just been inputted
      counter=1;
    }while(fp==NULL); //while the the file entered cannot be opend
    fclose(fp); //close file
    do{
      if(attemps==1)
        printf("\n----- Invalid operation entered -----\n\n");
      printf("\n----- Line Menu -----\n" );
      printf("1 - append line\n\n");
      printf("2 - delete line\n\n");
      printf("3 - insert line\n\n");
      printf("4 - show line\n\n");
      printf("x - terminate line operation\n\n");
      printf("Choose operation: ");
     // fseek(stdin,0,SEEK_END); //clears buffer
      fgets(mode, sizeof(mode), stdin); //Inputs operation number by the user
      fseek(stdin,0,SEEK_END); //clears buffer
        attemps=1;
      if(mode[0] == 'x'){ //if the user inputs x
        printf("\n----- Operation terminated successfully -----\n");
        return; //terminate line operations
      }
    }while(mode[0]<'1' || mode[0]>'4'); //while the user has inputted a non existant operation mode- ask them to input again
     
  switch(mode[0]){
    case '1': appendline(name);
      break;
    case '2': deleteline(name);
      break;
    case '3': insertline(name);
      break;
    case '4': showline(name);
      break;
  }
  return line_op();
}

void general_op(){
  int attemps=0;
  char mode[2];
  int counter=0;
  char data;
  FILE *fp;
  do{
    if(attemps==1)
      printf("\n----- Invalid operation entered -----\n\n");
    printf("\n\n----- General Menu -----\n" );
    printf("\n1 - show change log\n\n");
    printf("2 - show number of lines\n\n");
    printf("x - terminate general operation\n\n");
    printf("Choose operation: ");
    fgets(mode, sizeof(mode), stdin);
    fseek(stdin,0,SEEK_END); //clears buffer
    attemps=1;
    if(mode[0] == 'x'){ //if the user inputs x
        printf("\n\n----- Operation terminated successfully ------\n\n");
        return; //terminate line operations
    }
  }while((mode[0]<'1' || mode[0]>'2') );
  if(mode[0]=='1'){
    fseek(fpLog, 0, SEEK_SET);//set the pointer to the beggining of the file
    //print all the characters until reach the End of the File
    printf("------ Change Log ------\n");
    while((data=getc(fpLog)) !=EOF)
      printf("%c",data);
  }
  else if(mode[0]=='2'){
    fp=NULL;
    int line=0;
    char name[256];
    do{
      if(counter>0){
        printf("\nCould not open file. Maybe locked or being used by another application?\n");
        printf("\nInsert another file name to see the number of the lines that it has or press enter to terminate:\n" );
      }
      else printf("Insert file name to see the number of the lines that it has or press enter to terminate:\n");
      fgets(name, sizeof(name), stdin);
      fseek(stdin,0,SEEK_END); //clears buffer
      name[strlen(name)-1]='\0';
      if(name[0]=='\0') //if asked to terminate operation
        return; //return to main function
      fp= fopen(name,"r");
      counter++;
    }while(fp==NULL);
    while ((data = getc(fp)) != EOF){ 
      if(data== '\n')
        line++;
   }
   printf("\nThe file %s has %d lines.\n",name,line);
  }
  general_op();
}
void search(){
  int counter=0;
  char name [255];
  FILE *fp;
  FILE *fp2;
  int linenum;
  char linebuffer[1024]; //Maximum number of chars per line in Notepad-microsoft
  int charnum;
  char data;
  char word[255]; 
  int isfound;
  int num;
  do{
      if(counter==1)
          printf("\n----- Error - No such a file exists! -----\n\n" );
      printf("\n>>>Enter file name to access search operation or press enter to terminate:\n");
     // fseek(stdin,0,SEEK_END); //clears buffer
      fgets(name, sizeof(name), stdin); //inputs file name
      fseek(stdin,0,SEEK_END); //clears buffer
      name[strlen(name)-1]='\0';
      if(name[0]=='\0')
        return ;
      fp= fopen(name,"r+"); //opens file that the name has just been inputted
      counter=1;
    }while(fp==NULL); //while the the file entered cannot be opend
  while(1){
    charnum=0;
    isfound=0;
    linenum=0;
    fp2=fopen(".buffer","w+");
    printf("\nInsert string you want to find or press enter to terminate: ");
    //fgets(word, sizeof(word), stdin);
    fseek(stdin,0,SEEK_END); //clears buffer
    fgets(word, sizeof(word), stdin); //inputs file name
    fseek(stdin,0,SEEK_END); //clears buffer
     word[strlen(word)-1]='\0';
    if(word[0]=='\0'){
      fclose(fp);
      fclose(fp2);
      return ;
    }
    printf("\n");
    while((data=getc(fp))!=EOF){
        //checks line by line
        if(data=='\n'){ 
            linenum++;
            linebuffer[charnum]='\0';//sets last string element
            if(strstr(linebuffer,word) != NULL){
              if(isfound==0)
                printf(">>>String was found here:\n\n");
                //fprintf(fp2,"%d\n",linenum);
                printf("Line %d: %s\n\n",linenum,linebuffer);// prints the number and the line that the string is located in the file
                isfound=1;
            }
            //need to empty the string  
           linebuffer[0]='\0';
           charnum=0;
        }
        else{
             linebuffer[charnum]=data;
             charnum++;
        }
    }
    if(isfound==0)
        printf("\n----- String not found -----\n\n");
    else{
      char new_string[256];
      printf(" Write in which line you want to replace that string or enter 0 if you don't want to: ");
      scanf("%d",&linenum);
      fseek(stdin,0,SEEK_END); //clears buffer
      printf("\nEnter the the string: ");
      fgets(new_string, sizeof(new_string), stdin); //inputing the new string
      fseek(stdin,0,SEEK_END); //clears buffer
      if(linenum!=0){
        int i;
        int replaced=0;
        long int size;
        long int pos;
        fseek(fp, 0, SEEK_SET);//set the pointer to the beggining of the file
        num=1;
        //fp0=fopen(name,"r");
        
        while((data=getc(fp))!=EOF){
          replaced=0;
          pos = ftell(fp); //storing current position of pointer to another variable
          if(data=='\n')
            num++; //next line
          if(num==linenum){
            if(data==word[0]){
              for(i=1;i<strlen(word);i++)
                if((data=getc(fp))!=word[i]){
                  fseek (fp, pos, SEEK_SET); //Move pointer to previous position:https://stackoverflow.com/questions/55777956/move-the-file-pointer-back-after-fseek
                  break;  //means that it's not the matching string
                }
              if(i==strlen(word)){
                replaced=1;
                for(i=0;i<(strlen(new_string)-1);i++) //put the new string to the buffer file. Do not include the last character which is '\0'
                fputc(new_string[i],fp2);
              }     
            }
          }
          if(replaced==0) 
            fputc(data,fp2);
        }
        fseek(fp, 0, SEEK_SET);//set the pointer to the beggining of the file
        fseek(fp2, 0, SEEK_SET);//set the pointer to the beggining of the file
        while((data=getc(fp2))!=EOF)
          fputc(data,fp);
      }
      fprintf(fpLog,"Replaced %s int the line %d of the %s file.\n",word,linenum,name);
    }
    fclose(fp); 
    fclose(fp2);
    remove(".buffer");
    }
   search();
}