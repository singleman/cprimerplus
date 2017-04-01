#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
	if( argc == 1)
		{
			printf("usage\n");
			exit(1);
		}
	int i;
	char dst[128],*pstr=argv[1];
	for(i=0;*pstr;i++)
		dst[i]=toupper(*pstr++);
	dst[i]='\n';
	printf("%s",dst);
	return 0;

} 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>



#define	MAX	40


int main()
{
	FILE	*in,*out;
	char	line[MAX];
	float	lattice;
	printf("the type of lattice:\n");

	if ((in = fopen("POSCAR", "w")) == NULL)
	{
		fprintf(stderr,"I couldn't open POSCAR\n");
		exit(1);
	}
	printf("please input the first line\n");
	while(fgets(line,MAX,stdin) != NULL && line[0] != '\n')
		fputs(line,in);

	printf("please input the lattice-parameter\n");
	scanf("%f",&lattice);
	fprintf(in, "%.2f",lattice);



	fclose(in);
	return 0;
}
