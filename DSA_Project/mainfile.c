#include<stdio.h>
#include<stdlib.h>
#include"header_main.h"
#include<string.h>



struct process plist[1000];
int i=-1;




void input_single()
{
    i=i+1;
    int checkIfprinted=0;
    printf("\tEnter the Process ID : ");
    scanf("%d",&plist[i].process_id);
    fflush(stdin);

    printf("\tEnter the Runtime : ");
    scanf("%d",&plist[i].runtime);
    fflush(stdin);


    printf("\tEnter the Priority Class : ");
    scanf("%c",&plist[i].priority_class);
    fflush(stdin);


    printf("\tEnter the Priority : ");
    scanf("%d",&plist[i].priority);
    fflush(stdin);

    
    for(int j=0;j<i;j++)
    {
        if(plist[j].process_id==plist[i].process_id)
        {
            plist[j]=plist[i];
            i=i-1;
            quickSort_key(plist,0,i);
            printf("\t\tData has been sucessfully Updated\n");
            checkIfprinted=1;
            return;
        }
    }

    if(checkIfprinted==0)
    {
    quickSort_key(plist,0,i);
    }

    

    
    
    FILE *file_pointer;
    file_pointer=fopen("output_main.txt","w");
    for(int j=0;j<=i;j++)
    {
        fprintf(file_pointer,"%d %d %c %d\n",plist[j].process_id,plist[j].runtime,plist[j].priority_class,plist[j].priority);
    }

    fclose(file_pointer);



    if(checkIfprinted==0)
    {
        printf("\tData has been added to list sucesfully\n");
    }


    



}



void input_multiple()
{

    char check='n';
    printf("\tEnter the processes that should be inserted, in file 'input_main.txt' \n");
    printf("\tEnter 'y' if entered  :  ");
    scanf("%c",&check);
    fflush(stdin);
    

    
    FILE *fp;
    fp=fopen("input_main.txt","r");
    
    i=i+1;
    while(fscanf(fp,"%d %d %c %d",&plist[i].process_id,&plist[i].runtime,&plist[i].priority_class,&plist[i].priority)!=EOF)
    {
        i=i+1;
    }
    
    fclose(fp);
    i=i-1;

    
    
    mergeSort_id(plist,0,i);
    
    i=remove_duplicate(plist,i);
    quickSort_key(plist,0,i);
    

    FILE *file_pointer;
    file_pointer=fopen("output_main.txt","w");
    for(int j=0;j<=i;j++)
    {
        fprintf(file_pointer,"%d %d %c %d\n",plist[j].process_id,plist[j].runtime,plist[j].priority_class,plist[j].priority);
    }

    fclose(file_pointer);

    

    printf("\t\tList has been sucesfully updated \n");



}





void delete()
{
    printf("\tIf Multiple process to be deleted Enter 'm' ");
    printf("\n\tIf a Single process to deleted Enter 's'\n");
    printf("\t");
    

    char s_m;
    scanf("%c",&s_m);
    fflush(stdin);

    if(s_m=='s'||s_m=='S')
    {
        int delete_id,checkIfDelete=0;
        printf("\tEnter the Process ID : ");
        scanf("%d",&delete_id);
        fflush(stdin);
        if(i<0)
        {
            printf("\n\t\tUNDERFLOW : List is Empty \n");
            return;
        }

        for(int j=0;j<=i;j++)
        {
            if(plist[j].process_id==delete_id)
            {
                for(int k=j;k<=i-1;k++)
                {
                    plist[k]=plist[k+1];
                }
                i=i-1;
                checkIfDelete=1;
                break;
            }
        }
        if(checkIfDelete)
        {
            
            FILE *file_pointer;
            file_pointer=fopen("output_main.txt","w");
            for(int j=0;j<=i;j++)
            {
                fprintf(file_pointer,"%d %d %c %d\n",plist[j].process_id,plist[j].runtime,plist[j].priority_class,plist[j].priority);
            }

            fclose(file_pointer);

            printf("\t\tProcess id %d is Deleted sucessfully\n",delete_id);
        }
        else
        {
            printf("\t\tProcess id %d is NOT FOUND in list\n",delete_id);
        }
    

    }
    if(s_m=='m'||s_m=='M')
    {

        char check='n';
        printf("\tEnter the id's of that should be deleted in file 'input_delete.txt' \n");
        printf("\tEnter 'y' if entered id's of that should be deleted :  \n");
        scanf("%c",&check);
        fflush(stdin);

        if(i<0)
            {
                printf("\t\tUNDERFLOW : List is Empty \n");
                return;
            }
        
    
        FILE *file_pointer;
        int delete;


        mergeSort_id(plist,0,i);


        int delete_psn[i+1];
        memset(delete_psn,0,sizeof(delete_psn));

        file_pointer=fopen("input_delete.txt","r");
        

        while(fscanf(file_pointer,"%d",&delete)!=EOF)
        {
            
            
            int mid=binary_search(plist,0,i,delete);

            if(mid!=-1)
            {
                delete_psn[mid]=1;
            }

            
        
        }

        fclose(file_pointer);

        int x=0;
        struct process temp[i+1];

        for(int j=0;j<=i;j++)
        {
            if(delete_psn[j]==1)
            {
                continue;
            }
            temp[x]=plist[j];
            x=x+1;
        }
        x=x-1;
        for(int j=0;j<=x;j++)
        {
            plist[j]=temp[j];
        }
        i=x;

        quickSort_key(plist,0,i);
        FILE *file_pointer_1;
        file_pointer_1=fopen("output_main.txt","w");


        for(int j=0;j<=i;j++)
        {
            fprintf(file_pointer_1,"%d %d %c %d\n",plist[j].process_id,plist[j].runtime,plist[j].priority_class,plist[j].priority);
        }

        fclose(file_pointer_1);

    

        printf("\t\tList has been sucesfully updated \n");

        
    }
  
}


int get_no_of_process()
{
    FILE *file_pointer;
    file_pointer=fopen("output_main.txt","r");
        struct process temp;
        int counter=0;
        
        while(fscanf(file_pointer,"%d %d %c %d",&temp.process_id,&temp.runtime,&temp.priority_class,&temp.priority)!=EOF)
        {
            counter+=1;
        }

        fclose(file_pointer);
        printf("\n\t\tNumber of elements in list : %d\n",counter);

return counter;
}


int isEmpty()
{
    if(i==-1)
    {
        printf("\t\tList is Empty\n");
        return 1;
    }

    printf("\t\tList is NOT empty \n");
return 0;
}

void isFull()
{
    if(i==999)
    {
        printf("\t\tList is Full\n");
        return;
    }

    printf("\t\tList is NOT Full \n");
    
}

void Update_priority()
{
    char check='n';
        printf("\tEnter the id's,priority class and priority of that should be updated in file 'input_update.txt' \n");
        printf("\tEnter 'y' if entered  :  ");
        scanf("%c",&check);
        fflush(stdin);
    


    mergeSort_id(plist,0,i);
    struct process temp;
    FILE *file_pointer_1;
    file_pointer_1=fopen("input_update.txt","r");
    while(fscanf(file_pointer_1,"%d %c %d",&temp.process_id,&temp.priority_class,&temp.priority)!=EOF)
    {
        int temp_posn;
        temp_posn=binary_search(plist,0,i,temp.process_id);
        if(temp_posn!=-1)
        {
            plist[temp_posn].priority=temp.priority;
            plist[temp_posn].priority_class=temp.priority_class;
        }
    }
    fclose(file_pointer_1);

    quickSort_key(plist,0,i);
    
    FILE *file_pointer;
    file_pointer=fopen("output_main.txt","w");
    for(int j=0;j<=i;j++)
    {
        fprintf(file_pointer,"%d %d %c %d\n",plist[j].process_id,plist[j].runtime,plist[j].priority_class,plist[j].priority);
    }

    fclose(file_pointer);

    

    printf("\t\tList has been sucesfully updated \n");




}


void run_Process()
{
    int n;
    printf("\tEnter the number of processes to be runned : ");
    scanf("%d",&n);
    fflush(stdin);
    if(n>=(i+1))
    {
        i=-1;
    }
    else
    {
        for(int j=0;j<=i-n;j++)
        {
            plist[j]=plist[j+n];
        }
        i=i-n;
    }


    FILE *file_pointer;
    file_pointer=fopen("output_main.txt","w");
    for(int j=0;j<=i;j++)
    {
        fprintf(file_pointer,"%d %d %c %d\n",plist[j].process_id,plist[j].runtime,plist[j].priority_class,plist[j].priority);
    }

    fclose(file_pointer);

    

    printf("\t\tList has been sucesfully updated \n");

}


void unique_update()
{
    char check='n';
        printf("\tEnter the processes that should be updated in file 'input_Unique.txt' \n");
        printf("\tEnter 'y' if entered  :  ");
        scanf("%c",&check);
        fflush(stdin);
    

    FILE *fp;
    fp=fopen("input_Unique.txt","r");
    
    i=i+1;
    while(fscanf(fp,"%d %d %c %d",&plist[i].process_id,&plist[i].runtime,&plist[i].priority_class,&plist[i].priority)!=EOF)
    {
        i=i+1;
    }
    
    fclose(fp);
    i=i-1;

    mergeSort_id_unique(plist,0,i);
    i=remove_duplicate(plist,i);
    quickSort_key(plist,0,i);



    FILE *file_pointer;
    file_pointer=fopen("output_main.txt","w");
    for(int j=0;j<=i;j++)
    {
        fprintf(file_pointer,"%d %d %c %d\n",plist[j].process_id,plist[j].runtime,plist[j].priority_class,plist[j].priority);
    }

    fclose(file_pointer);

    

    printf("\t\tList has been sucesfully updated \n");


}

void union_list()
{
    char check='n';
        printf("\tEnter the processes of list1 and list2 in 'z_List_1.txt' and 'z_List_1.txt' \n");
        printf("\tEnter 'y' if entered  :  ");
        scanf("%c",&check);
        fflush(stdin);
    


    int n=0;
    struct process temp;

    FILE *fp_3;
    fp_3=fopen("z_List_2.txt","r");
    
    
    while(fscanf(fp_3,"%d %d %c %d",&temp.process_id,&temp.runtime,&temp.priority_class,&temp.priority)!=EOF)
    {
        n=n+1;
    }
    
    fclose(fp_3);
    
    FILE *fp_4;
    fp_4=fopen("z_List_1.txt","r");
    
    
    while(fscanf(fp_4,"%d %d %c %d",&temp.process_id,&temp.runtime,&temp.priority_class,&temp.priority)!=EOF)
    {
        n=n+1;
    }
    
    fclose(fp_4);
    

    struct process plist_1[n+1];
    
    n=-1;


    FILE *fp_2;
    fp_2=fopen("z_List_2.txt","r");
    
    n=n+1;
    while(fscanf(fp_2,"%d %d %c %d",&plist_1[n].process_id,&plist_1[n].runtime,&plist_1[n].priority_class,&plist_1[n].priority)!=EOF)
    {
        n=n+1;
    }
    
    fclose(fp_2);
    n=n-1;





    FILE *fp_1;
    fp_1=fopen("z_List_1.txt","r");
    
    n=n+1;
    while(fscanf(fp_1,"%d %d %c %d",&plist_1[n].process_id,&plist_1[n].runtime,&plist_1[n].priority_class,&plist_1[n].priority)!=EOF)
    {
        n=n+1;
    }
    
    fclose(fp_1);
    n=n-1;

    mergeSort_id(plist_1,0,n);
    n=remove_duplicate(plist_1,n);
    quickSort_key(plist_1,0,n);



    FILE *file_pointer;
    file_pointer=fopen("z_List_3.txt","w");
    for(int j=0;j<=n;j++)
    {
        fprintf(file_pointer,"%d %d %c %d\n",plist_1[j].process_id,plist_1[j].runtime,plist_1[j].priority_class,plist_1[j].priority);
    }

    fclose(file_pointer);

    

    printf("\t\tUnion of list 1 and list 2 are sucessfully printed in list 3\n");



}


void intersection()
{
    char check='n';
        printf("\tEnter the processes of list1 and list2 in 'z_List_1.txt' and 'z_List_1.txt' \n");
        printf("\tEnter 'y' if entered  :  ");
        scanf("%c",&check);
        fflush(stdin);
    
    int n1=0,n2=0,n3=0;
    struct process temp;

    FILE *fp_3;
    fp_3=fopen("z_List_1.txt","r");
    
    
    while(fscanf(fp_3,"%d %d %c %d",&temp.process_id,&temp.runtime,&temp.priority_class,&temp.priority)!=EOF)
    {
        n1=n1+1;
    }
    
    fclose(fp_3);
    
    FILE *fp_4;
    fp_4=fopen("z_List_2.txt","r");
    
    
    while(fscanf(fp_4,"%d %d %c %d",&temp.process_id,&temp.runtime,&temp.priority_class,&temp.priority)!=EOF)
    {
        n2=n2+1;
    }
    
    fclose(fp_4);






    struct process plist_1[n1];
    struct process plist_2[n2];
    struct process plist_3[n2+n1];
    
    int n=-1;


    FILE *fp_2;
    fp_2=fopen("z_List_1.txt","r");
    
    n=n+1;
    while(fscanf(fp_2,"%d %d %c %d",&plist_1[n].process_id,&plist_1[n].runtime,&plist_1[n].priority_class,&plist_1[n].priority)!=EOF)
    {
        n=n+1;
    }
    
    fclose(fp_2);
    
    
    
    
    
    
    n=-1;
    FILE *fp_1;
    fp_1=fopen("z_List_2.txt","r");
    
    n=n+1;
    while(fscanf(fp_1,"%d %d %c %d",&plist_2[n].process_id,&plist_2[n].runtime,&plist_2[n].priority_class,&plist_2[n].priority)!=EOF)
    {
        n=n+1;
    }
    
    fclose(fp_1);
    
    
    
    mergeSort_id(plist_1,0,n1-1);
    mergeSort_id(plist_2,0,n2-1);
    
    
    if(n2>=n1)
    {
        for(int j=0;j<n1;j++)
        {
            int x=-1;
            x=binary_search(plist_2,0,n2-1,plist_1[j].process_id);
            if(x!=-1)
            {
                if(compare_struct(plist_1[j],plist_2[x])==1)
                {
                    plist_3[n3]=plist_1[j];
                }
                else
                {
                    plist_3[n3]=plist_2[x];
                }
                n3=n3+1;
            }
        }
    }
    else
    {
        for(int j=0;j<n2;j++)
        {
            int x=-1;
            x=binary_search(plist_1,0,n1-1,plist_2[j].process_id);
            if(x!=-1)
            {
                if(compare_struct(plist_2[j],plist_1[x])==1)
                {
                    plist_3[n3]=plist_2[j];
                }
                else
                {
                    plist_3[n3]=plist_1[x];
                }
                n3=n3+1;
            }
        }
    }
    quickSort_key(plist_3,0,n3-1);

    FILE *file_pointer;
    file_pointer=fopen("z_List_3.txt","w");
    for(int j=0;j<=n3-1;j++)
    {
        fprintf(file_pointer,"%d %d %c %d\n",plist_3[j].process_id,plist_3[j].runtime,plist_3[j].priority_class,plist_3[j].priority);
    }

    fclose(file_pointer);

    

    printf("\t\tIntersection of list 1 and list 2 are sucessfully printed in list 3\n");

    
}


void difference_list()
{
    char check='n';
        printf("\tEnter the processes of list1 and list2 in 'z_List_1.txt' and 'z_List_1.txt' \n");
        printf("\tEnter 'y' if entered  :  ");
        scanf("%c",&check);
        fflush(stdin);
    
    int n1=0,n2=0,n3=0;
    struct process temp;

    FILE *fp_3;
    fp_3=fopen("z_List_1.txt","r");
    
    
    while(fscanf(fp_3,"%d %d %c %d",&temp.process_id,&temp.runtime,&temp.priority_class,&temp.priority)!=EOF)
    {
        n1=n1+1;
    }
    
    fclose(fp_3);
    
    FILE *fp_4;
    fp_4=fopen("z_List_2.txt","r");
    
    
    while(fscanf(fp_4,"%d %d %c %d",&temp.process_id,&temp.runtime,&temp.priority_class,&temp.priority)!=EOF)
    {
        n2=n2+1;
    }
    
    fclose(fp_4);

    struct process plist_1;
    struct process plist_2[n2];
    struct process plist_3[n1];
    
    int n=0;

    FILE *fp_1;
    fp_1=fopen("z_List_2.txt","r");
    

    while(fscanf(fp_1,"%d %d %c %d",&plist_2[n].process_id,&plist_2[n].runtime,&plist_2[n].priority_class,&plist_2[n].priority)!=EOF)
    {
        n=n+1;
    }
    
    fclose(fp_1);
    
    
    mergeSort_id(plist_2,0,n2-1);
    

    FILE *fp_2;
    fp_2=fopen("z_List_1.txt","r");
    

    while(fscanf(fp_2,"%d %d %c %d",&plist_1.process_id,&plist_1.runtime,&plist_1.priority_class,&plist_1.priority)!=EOF)
    {
        int x=0;
        x=binary_search(plist_2,0,n2-1,plist_1.process_id);
        if(x==-1)
        {
            plist_3[n3]=plist_1;
            n3=n3+1;
        }
    }
    
    fclose(fp_2);
    
    quickSort_key(plist_3,0,n3-1);

    FILE *file_pointer;
    file_pointer=fopen("z_List_3.txt","w");
    for(int j=0;j<=n3-1;j++)
    {
        fprintf(file_pointer,"%d %d %c %d\n",plist_3[j].process_id,plist_3[j].runtime,plist_3[j].priority_class,plist_3[j].priority);
    }

    fclose(file_pointer);

    

    printf("\t\tDifference of list 1 and list 2 are sucessfully printed in list 3\n");

    


}

void symmetric_difference()
{
    char check='n';
        printf("\tEnter the processes of list1 and list2 in 'z_List_1.txt' and 'z_List_1.txt' \n");
        printf("\tEnter 'y' if entered  :  ");
        scanf("%c",&check);
        fflush(stdin);
    


    int n1=0,n2=0,n3=0;
    struct process temp;

    FILE *fp_3;
    fp_3=fopen("z_List_1.txt","r");
    
    
    while(fscanf(fp_3,"%d %d %c %d",&temp.process_id,&temp.runtime,&temp.priority_class,&temp.priority)!=EOF)
    {
        n1=n1+1;
    }
    
    fclose(fp_3);
    
    FILE *fp_4;
    fp_4=fopen("z_List_2.txt","r");
    
    
    while(fscanf(fp_4,"%d %d %c %d",&temp.process_id,&temp.runtime,&temp.priority_class,&temp.priority)!=EOF)
    {
        n2=n2+1;
    }
    
    fclose(fp_4);

    
    struct process plist_1;
    struct process plist_2[n2];
    struct process plist_3[n1+n2];
    int list2[n2];
    memset(list2,0,sizeof(list2));
    
    int n=0;

    FILE *fp_1;
    fp_1=fopen("z_List_2.txt","r");
    

    while(fscanf(fp_1,"%d %d %c %d",&plist_2[n].process_id,&plist_2[n].runtime,&plist_2[n].priority_class,&plist_2[n].priority)!=EOF)
    {
        n=n+1;
    }
    
    fclose(fp_1);
    
    
    mergeSort_id(plist_2,0,n2-1);
    

    FILE *fp_2;
    fp_2=fopen("z_List_1.txt","r");
    

    while(fscanf(fp_2,"%d %d %c %d",&plist_1.process_id,&plist_1.runtime,&plist_1.priority_class,&plist_1.priority)!=EOF)
    {
        int x=-1;
        x=binary_search(plist_2,0,n2-1,plist_1.process_id);
        
        if(x==-1)
        {
            plist_3[n3]=plist_1;
            n3=n3+1;
            
        }
        else
        {
            list2[x]=1;
        }
    }
    
    fclose(fp_2);
    for(int j=0;j<n2;j++)
    {
        if(list2[j]==1)
        {
            continue;
        }
        plist_3[n3]=plist_2[j];
        n3=n3+1;
            

    }
    
    quickSort_key(plist_3,0,n3-1);

    FILE *file_pointer;
    file_pointer=fopen("z_List_3.txt","w");
    for(int j=0;j<=n3-1;j++)
    {
        fprintf(file_pointer,"%d %d %c %d\n",plist_3[j].process_id,plist_3[j].runtime,plist_3[j].priority_class,plist_3[j].priority);
    }

    fclose(file_pointer);

    

    printf("\t\tSYMMETERIC DIFFERENCE of list 1 and list 2 are sucessfully printed in list 3\n");

    

}

int main()
{

    
    printf("\t************************************************************************************************\n");
    printf("\t********************************   PROCESS MANAGEMENT SYSTEM   ********************************");
    printf("\n");
    printf("\t================================================================================================");
    printf("\n\n\t\t\t***********************   MAIN MENU   ***********************\n");
    printf("\tChoose the index numbers of options from the following to run it \n");
    printf("\t\t1.  Single process Input\n");
    printf("\t\t2.  Multiple processes Input\n");
    printf("\t\t3.  Delete process\n");
    printf("\t\t4.  To get Number of processes in List\n");
    printf("\t\t5.  To know if the List is Empty\n");
    printf("\t\t6.  To know if the List is Full\n");
    printf("\t\t7.  Update Process Priority\n");
    printf("\t\t8.  Run Process\n");
    printf("\t\t9.  Unique - list with Duplicates (for duplicate ,retains that in list 1)\n");
    printf("\t\t10. Union of Two Lists\n");
    printf("\t\t11. Intersection of Two Lists\n");
    printf("\t\t12. Difference of Two Lists\n");
    printf("\t\t13. Symmetric Difference of of Two Lists\n");
    printf("\t\t14. Exit\n");

    int choice =0;

    while(choice != 14)
    {
        printf("Enter thr Choice : ");
        scanf("%d",&choice);
        fflush(stdin);
            


        switch(choice)
        {
            case 1:
            input_single();
            break;
            case 2:
            input_multiple();
            break;
            case 3:
            delete();
            break;
            case 4:
            get_no_of_process();
            break;
            case 5:
            isEmpty();
            break;
            case 6:
            isFull();
            break;
            case 7:
            Update_priority();
            break;
            case 8:
            run_Process();
            break;
            case 9:
            unique_update();
            break;
            case 10:
            union_list();
            break;
            case 11:
            intersection();
            break;
            case 12:
            difference_list();
            break;
            case 13:
            symmetric_difference();
            break;
            case 14:
            break;
            default:
            printf("----Invalid Choice----");

            
        }
    }
    

return 0;
}