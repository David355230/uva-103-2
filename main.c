#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
//c

typedef struct Box
{
	int arr[10];
}Box;

Box box[30];


int compare(const void* num1, const void* num2) 
{  
    int a = *(int*) num1;  
    int b = *(int*) num2;  
    if(a > b)  
    {  
        return 1;  
    }  
    else if(a < b)  
    {  
        return -1;  
    }  
    return 0;  
}  

int check(Box  *box,int s,int temp)
{
	int i=0;
	int ans=1;
	for(i=0;i<s;i++)
	{
		if(box[temp].arr[i]>box[temp-1].arr[i])
		{
			ans=0;
			break;
		}
	}
	return ans;
}

void colsort(Box *box,int n,int dim,int pos[n],int s)
{
	int k; 
	int i,j;
	k=0;
	while(k<n-1)
	{
		i=n-1;
		while(i>k)
		{
			if(box[i].arr[s]<box[i-1].arr[s])
			{
				if(check(box,s,i)==1)
				{
				int temp,temp1;
				for(j=s;j<dim;j++)
				{
					temp=box[i].arr[j];
				    box[i].arr[j]=box[i-1].arr[j];
				    box[i-1].arr[j]=temp;
				}
				temp1=pos[i];
				pos[i]=pos[i-1];
				pos[i-1]=temp1;
				}
			}
			i--;
		}
		k++; 
	}
}

int max(int a ,int b)
{
	if(a>b)
	return a;
	else
	return b;
}

int checkLIS(Box *box,int a,int b,int dim)
{
	int i;
	int ans;
	ans=1;
	for(i=0;i<dim;i++)
	{
		if(box[a].arr[i]<=box[b].arr[i])
		{
			ans=0;
			break;
		}
	}
	return ans;
	
}

int LIS(Box *box,int pos[],int pos1[],int n,int dim)
{
	
	int LISlen[n],i,j,temp,tp;
	
	for(i=0;i<n;i++)
	LISlen[i]=1;
	

	for(i=1;i<n;i++)
	{
		for(j=0;j<i;j++)
		{
			if(checkLIS(box,i,j,dim)==1)
			{
				if(LISlen[i]<LISlen[j]+1)
				{
					LISlen[i]=LISlen[j]+1;
					pos1[i]=j;
				}
			}
			
		}
	}
	
	temp=0;
	for(i=0;i<n;i++)
	{
		if(LISlen[i]>temp)
		{
			temp=LISlen[i];
			tp=i;
		}
	}
	
	int out[temp];
	printf("%d\n",temp);
	
	for(i=temp-1;i>=0;i--)
	{
		out[i]=pos[tp];
		tp=pos1[tp];
	}
	
	for(i=0;i<temp;i++)
	{
		if(i==temp-1)
		printf("%d\n",out[i]);
		else
		printf("%d ",out[i]);
	}

	
}

void stack( Box *box ,int n ,int dim,int pos[n])
{
	int i,pos1[n];
	for(i=0;i<n;i++)
	{
		pos1[i]=0;
		qsort(box[i].arr,dim,sizeof(int),compare);
	}
	printf("\n");
	
	i=0;
	while(i<dim) 
	{
		colsort(box,n,dim,pos,i);
		i++;
	}
	 LIS(box,pos,pos1,n,dim);
}

int main()
{
	int n,dim,i,j;
	while(scanf("%d",&n)!=EOF)
	{
		int *pos = malloc(n * sizeof(int));
		scanf("%d ",&dim);
		for(i=0;i<n;i++)
		{
			pos[i]=i+1;
			for(j=0;j<dim;j++)
			{
				scanf("%d",&box[i].arr[j]);
			}
		}
		stack(box,n,dim,pos);
		free(pos);
	}
	return 0;
}
