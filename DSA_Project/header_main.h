#include<time.h>

struct process
{
    int process_id;
    int runtime;
    char priority_class;
    int priority;

};

void swap_struct(struct process *a,struct process *b)
{
    struct process t;
    t = *a;
    *a = *b;
    *b = t;
}


int compare_struct(struct process arr,struct process pivot )
{
    if(arr.priority_class<pivot.priority_class)
    {
        return 1;
    }
    if(arr.priority_class>pivot.priority_class)
    {
        return 2;
    }
    if(arr.priority<pivot.priority)
    {
        return 1;
    }
    
    if(arr.priority>pivot.priority)
    {
        return 2;
    }
    

    return 0;
}






int partition_key(struct process arr[], int low, int high)
{
    struct process pivot = arr[low];
    int i = low - 1, j = high + 1;
 
    while (1) {
        
        do 
        {
            i++;
        } while (compare_struct(arr[i],pivot)==1);
 
        
        do 
        {
            j--;
        } while (compare_struct(arr[j],pivot)==2);
 
       
        if (i >= j)
            return j;
 
        swap_struct(&arr[i], &arr[j]);
    }
}


int partition_r_key(struct process arr[], int low, int high)
{
    
    srand(time(NULL));
    int random = low + rand() % (high - low);
 
  
    swap_struct(&arr[random], &arr[low]);
 
    return partition_key(arr, low, high);
}



 

void quickSort_key(struct process arr[], int low, int high)
{
    if (low < high) {
        
        int pi = partition_r_key(arr, low, high);
 
      
        quickSort_key(arr, low, pi);
        quickSort_key(arr, pi + 1, high);
    }
}
 

int binary_search(struct process a[],int l,int r,int x)
{

    if (r >= l) 
    {
        int mid = l + (r - l) / 2;
        
 
       
        if (a[mid].process_id==x)
        {
            
            return mid;
        }
       
        if (a[mid].process_id>x)
            return binary_search(a, l, mid - 1, x);
 
        
        return binary_search(a, mid + 1, r, x);
    }
 
    
    return -1;

}






void merge_id(struct process arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
  
   
    struct process L[n1], R[n2];
  
    
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
  
    
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i].process_id <= R[j].process_id) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
  
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
  
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
  

void mergeSort_id(struct process arr[], int l, int r)
{
    if (l < r) {
       
        int m = l + (r - l) / 2;
  
        
        mergeSort_id(arr, l, m);
        mergeSort_id(arr, m + 1, r);
  
        merge_id(arr, l, m, r);
    }
}



int remove_duplicate(struct process a[],int n)
{
    if(n==0||n==-1)
    {
        return n;
    }
    struct process temp[n+1];
    
    int j=0;
    for(int i=0;i<=n-1;i++)
    {
        if(a[i].process_id!=a[i+1].process_id)
        {
            temp[j++]=a[i];
        }
    }


    temp[j++]=a[n];
    
    for(int i=0;i<j;i++)
    {
        a[i]=temp[i];
    }
    
return j-1;}



void merge_id_unique(struct process arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
  

    struct process L[n1], R[n2];
  
    
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
  
    
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i].process_id < R[j].process_id) 
        {
            arr[k] = L[i];
            i++;
        }
        else if (L[i].process_id > R[j].process_id) 
        {
            arr[k] = R[j];
            j++;
        }
        else
        {
            if (compare_struct(L[i],R[j])==2||compare_struct(L[i],R[j])==0) 
            {
                arr[k] = L[i];
                i++;
            }
            else if (compare_struct(L[i],R[j])==1) 
            {
                arr[k] = R[j];
                j++;
            }

        }
        k++;
    }
  
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
  
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
  

void mergeSort_id_unique(struct process arr[], int l, int r)
{
    if (l < r) {
        
        int m = l + (r - l) / 2;
  
        
        mergeSort_id_unique(arr, l, m);
        mergeSort_id_unique(arr, m + 1, r);
  
        merge_id_unique(arr, l, m, r);
    }
}

