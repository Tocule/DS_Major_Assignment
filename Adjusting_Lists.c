#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct list
{
    char data;
    struct list *next;
}List;

/******************************************Methods***************************************************************************************/

/******************************************Build_Linked_List_of_Characters***************************************************************/

List *build(List *list)
{
   char c;
   List *head,*temp,*ptr;
   head=NULL;
   temp=NULL;
   ptr=NULL;
   c=' ';
   for(int i=32;i<=126;i++)
   {
       ptr=(List *)malloc(sizeof(List));
       ptr->data=c;
       ptr->next=NULL;
       if(head==NULL)
       {
           head=ptr;
       }
       else
       {
           temp->next=ptr;
       }
       temp=ptr;
       c++;
   }

  return(head);
}


/********************************************Get_function**********************************************************************************/

List *get(List *head,FILE *fp,FILE *fp1)
{
   List *temp,*prev;
   int position=0;
   prev=NULL;
   char ch;
   ch=fgetc(fp);
   while(ch!=EOF)
   {
       	   
       temp=head;	   
       while(temp!=NULL)
       {
          if(temp->data==ch)
          {		  
       	     break;
          }
          else
          {
            position++;
          }
          prev=temp;
          temp=temp->next;
      }
      if(ch!='\n')
      {	      
	 fprintf(fp1,"%d ",position);
         if(position>=1)
         {
            prev->next=temp->next;
            temp->next=head;
            head=temp;
	    position=0;
         }
      }	 
         ch=fgetc(fp);
      	 
   }   
  fclose(fp);
  fclose(fp1);
  return(head);
}  

/**************************************print_list*************************************************************************************/
void print_list(List *head)
{
   List *temp;
   temp=head;
   while(temp!=NULL)
   {
      printf("%c ",temp->data);
      temp=temp->next;
   }
   printf("\n");
}
/**************************************get_recover*************************************************************************************/
List *get_recover(List *head1,FILE *fp1,FILE *fp)
{
   List *temp,*prev;
   int position=0;
   prev=NULL;
   int pattern;
   fscanf(fp1,"%d",&pattern);
   while(!feof(fp1))
   {

       temp=head1;
       while(temp!=NULL)
       {
          if(pattern==position)
          {
             break;
          }
          else
          {
            position++;
          }
          prev=temp;
          temp=temp->next;
       }
  
       fprintf(fp,"%c",temp->data);
   
       if(position>=1)
       {
          prev->next=temp->next;
          temp->next=head1;
          head1=temp;
          position=0;
       }
         fscanf(fp1,"%d",&pattern);
   }
  fclose(fp);
  fclose(fp1);
  return(head1);
}

/************************************main**********************************************************************************************/

int main(void)
{
   //////////////////////////////////Convert///////////////////////////////////////////////////////////////////////////////////////////	
   FILE *fp,*fp1;
   fp=fopen("input1.txt","r");
   if(fp==NULL)
   {
      printf("Couldn\'t open the file to read\n");
      exit(0);
   }
   fp1=fopen("input2.txt","w");
   if(fp1==NULL)
   {
     printf("Couldn\'t open the file to write\n");
     exit(0);
   }
   List *head;
   head=build(head);
   print_list(head);
   head=get(head,fp,fp1);
   print_list(head);
   /////////////////////////////////Recover///////////////////////////////////////////////////////////////////////////////////////////
   fp=fopen("input1.txt","w");
   if(fp==NULL)
   {
      printf("Couldn\'t open the file to read\n");
      exit(0);
   }
   fp1=fopen("input2.txt","r");
   if(fp1==NULL)
   {
     printf("Couldn\'t open the file to write\n");
     exit(0);
   }
   List *head1;
   head1=build(head1);
   print_list(head1);
   get_recover(head1,fp1,fp);
   ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
/*************************************************************************************************************************************/
