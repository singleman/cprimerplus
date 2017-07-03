#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
	int count,Maxsize;
	Maxsize=3;
	struct student *pt
	pt=Maxsize*malloc(sizeof(struct student));

	
	printf("please input the student name:\n");	
	while(s_get((pt->stu[0]).name,LEN) != NULL)
		printf("%s\n",(pt->stu[0]).name);





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
			*find = '\n';
		else
			while(getchar() != '\n')
				continue;
	}
	return ret_val;

}

