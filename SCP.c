#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

typedef struct Tree
{
   int permutation_number;
   struct Tree *lchild;
   struct Tree *rchild;
}tree;

int I=0;
int counter=0;

void fill_original_string(char string[],FILE *fp,int character_count)
{
   char ch;
   int count=0;
   ch=fgetc(fp);
   while(count<character_count-1)
   {
      string[count]=ch;
      count++;
      ch=fgetc(fp);
   }
   string[count]='\0';
   fclose(fp);
}   

void number_to_string(char original_string[],char permuted_string[],int number,int character_count)
{
     int i=0;
     while(i!=character_count-1)
     {
	 if(number==character_count-1)
         {
            number=0;
         }    
         permuted_string[i]=original_string[number];
         i++;
         number++;
    }
    permuted_string[i]='\0';
}

void print_string(char string[])
{
   puts(string);
}


tree *build_permutation_binary_tree(char original_string[],int character_count)
{
     tree *root,*ptr,*temp,*prev;
     root=NULL;
     ptr=NULL;
     temp=NULL;
     prev=NULL;
     int i,flag;
     char permuted_string1[character_count];
     char permuted_string2[character_count];
     for(i=0;i<character_count-1;i++)
     {
          ptr=(tree *)malloc(sizeof(tree));
          ptr->permutation_number=i;
          ptr->lchild=NULL;
          ptr->rchild=NULL;
          number_to_string(original_string,permuted_string2,ptr->permutation_number,character_count);
	  temp=root;
	  while(temp!=NULL)
	  {   
	      number_to_string(original_string,permuted_string1,temp->permutation_number,character_count);	  
	      prev=temp;
	      if((strcmp(permuted_string1,permuted_string2))>0)
	      {
	          temp=temp->lchild;
                  flag=1;
              }
              else
	      {
	          temp=temp->rchild;
                  flag=0;
              }
          }
	  if(root==NULL)
	  {
	      root=ptr;
          } 
      	  else
	  {	      
  	      if(flag==1)
  	      {
	      	  prev->lchild=ptr;
              }
	      if(flag==0)
	      {
	      	  prev->rchild=ptr;
              }
	  }	
     }
         return(root);     
}     
      
void print_inorder(char original_string[],tree *root,int character_count,FILE *fp1)
{
    tree *temp;
    temp=root;    
    char permuted_string[character_count];
    if(temp!=NULL)
    {
       print_inorder(original_string,temp->lchild,character_count,fp1);	    
       number_to_string(original_string,permuted_string,temp->permutation_number,character_count);	       
       printf("%c",permuted_string[character_count-2]);
       fputc(permuted_string[character_count-2],fp1);
       if((strcmp(original_string,permuted_string))==0)
       {
           I=counter;
       }
       counter++;       
       print_inorder(original_string,temp->rchild,character_count,fp1);
    }
}


void quicksort_SCP(char sort_string[],int left,int right)  
{  
   int i,j;  
   char pivot,temp;  
  
   i=left;
   j=right;  
   pivot=sort_string[(left+right)/2];  
  
  do 
  {
     while((sort_string[i]<pivot)&&(i<right)) 
       i++;  
     while((pivot<sort_string[j])&&(j>left)) 
       j--;  
  
    if(i<=j) 
    {  
       temp=sort_string[i];  
       sort_string[i]=sort_string[j];  
       sort_string[j]=temp;  
       i++; 
       j--;  
    }

  } while(i<=j);  
  
  if(left<j) 
     quicksort_SCP(sort_string,left,j);  
  if(i<right) 
     quicksort_SCP(sort_string,i,right);  
}

void recover(char sort_string[],char SCP_string[],int character_count,int position[],FILE *fp)
{
   int i,j;
   int flag;
   for(i=0;i<character_count-1;i++)
   {
       for(j=0;j<character_count-1;j++)
       {
            if((sort_string[i]==SCP_string[j])&&(position[j]==-1))
            {
                 flag=1;
                 break;
            }
       }
   
      if(flag==1)
      {
        position[j]=i;
        flag=0;
      }
   }    
   
   printf("Positions for recover are : ");
   for(i=0;i<character_count-1;i++)
   {
       printf("%d ",position[i]);
   }
   printf("\n");
   j=character_count-2;
   i=I; 
   while(j>=0)
   {       
       sort_string[j]=SCP_string[i];
       i=position[i];
       j--;
   }
   printf("Recovered String is : ");
   for(i=0;i<character_count-1;i++)
   {
      printf("%c",sort_string[i]);	   
      fputc(sort_string[i],fp);
   }      
   printf("\n"); 
  fclose(fp);
}  
              	      
int main(void)
{
////////////////////////////////////Convert////////////////////////////////////////////////////////////////////////////////////////////	
    FILE *fp,*fp1;
    fp=fopen("test_SCP.txt","r");
    fseek(fp,0,SEEK_END);
    int character_count=ftell(fp);
    rewind(fp);
    fp1=fopen("write_SCP_string","w");
    char original_string[character_count];
    char permuted_string[character_count]; 
    tree *root;   
    fill_original_string(original_string,fp,character_count);
    printf("The original string is : ");
    print_string(original_string);
    root=build_permutation_binary_tree(original_string,character_count);
    printf("The SCP string is : ");
    print_inorder(original_string,root,character_count,fp1);
    printf("\n");
    fclose(fp1);
////////////////////////////////Recover///////////////////////////////////////////////////////////////////////////////////////////////
 
    fp1=fopen("write_SCP_string","r");
    fp=fopen("test_SCP.txt","w");
    char SCP_string[character_count];
    char sort_string[character_count];
    int position[character_count];
    for(int i=0;i<character_count-1;i++)
    {
        position[i]=-1;
    }       
    fill_original_string(SCP_string,fp1,character_count);
    printf("Read SCP_string is : ");
    puts(SCP_string);
    printf("\n");
    strcpy(sort_string,SCP_string);
    quicksort_SCP(sort_string,0,character_count-2);
    recover(sort_string,SCP_string,character_count,position,fp);    
}    
