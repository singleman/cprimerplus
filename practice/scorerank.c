#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define LEN 40

char *s_get(char *st, int n);

int main()
{
	struct student{
		char name[LEN];
		int liter;
		int math;
		int english;
		int total;
		int n;
	};
	/*struct rank{
		struct student *stu;
		int number;
		int maxsize;
	};

	struct rank *pt;
	pt=malloc(sizeof(struct rank));
	*/


	int i,count,Maxsize;
	char option;

	Maxsize=3;
	struct student *pt,*temp;
	pt=malloc(Maxsize*sizeof(struct student));
	temp=malloc(sizeof(struct student));

	
	//while(s_get((pt->stu[0]).name,LEN) != NULL)
	for(i=0;i<Maxsize;i++)
	{
		printf("please input the student name:\n");	
		s_get((pt+i)->name,LEN);   // pt[0].name (pt+1)->name
					//	printf("%s\n",pt[0].name);
		
			printf("please input the score:\n");	
			scanf("%d %d %d",&((pt+i)->liter),&((pt+i)->math),&((pt+i)->english));
			(pt+i)->total=(pt+i)->liter + (pt+i)->math + (pt+i)->english;
	
		printf("name: %4s; liter: %3d; math: %3d; english: %3d; total: %3d\n",(pt+i)->name,(pt+i)->liter,(pt+i)->math,(pt+i)->english,(pt+i)->total);
		while(getchar()!='\n')
			continue;
	}

	printf("please choose the key to sort\n:");
	//while((option=getchar())!='*')
	scanf("%c",&option);
	{
		//if( option=='\n')
		//	continue;
		if(islower(option))
			switch(option)
			{
			case 't':
				{
				for(i=0;i<Maxsize-1;i++)
					if((pt+i)->total > (pt+i+1)->total)
					{
						*temp=*(pt+i);
						*(pt+i)=*(pt+i+1);
						*(pt+i+1)=*temp;
					}
				}


			}

	}


	for(i=0;i<Maxsize;i++)
		printf("name: %4s; liter: %3d; math: %3d; english: %3d; total: %3d\n",(pt+i)->name,(pt+i)->liter,(pt+i)->math,(pt+i)->english,(pt+i)->total);


	free(pt);
	free(temp);
	return 0;
}

char *s_get(char *st, int n)
{
	char * ret_val;
	char * find;
	ret_val=fgets(st,n,stdin);
	if(ret_val)
	{
		find = strchr(st,'\n');
		if(find)
			*find = '\0';
		else
			while(getchar() != '\n')
				continue;
	}
	return ret_val;

}

