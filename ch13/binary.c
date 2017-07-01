#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
	FILE *fp;
	float coef[3];
	float result;
	int i=0,line=0;
	int ch;

	fp = fopen ("coefficient","r");
	while( (ch = fgetc(fp)) != EOF)
		if(ch=='\n')
			count++;
/*	while(!feof(fp))
		fscanf(fp,"%f",coef[i++]);

	fclose(fp);
	for(i=0;i++;i<3)
		printf("%f\n",coef[i]);
*/
	return 0;
}
