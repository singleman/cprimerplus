#include<stdio.h>

#define LEN 8

void pri_position(int (*pos)[2]);
int cal(int row, int col, int (*pos)[2]);
int count=0;

int main()
{
//	char check_board[LEN][LEN];
//	char result[LEN][LEN];

	int position[LEN][2];
	int i;

//	for(i=0;i<LEN;i++)
		cal(0,i,position);
		printf("%d\n",count);



	return 0;
}

/*
void output(char (*pt)[LEN])
{

}

*/

void pri_position(int (*pos)[2])
{
	int i;
	for(i=0;i<LEN;i++)
		printf("%d %d	",pos[i][0],pos[i][1]);
}

int cal(int row,int col,int (*pos)[2])
{
	int j,critical;

	for(j=col;j<LEN;j++)  //row 0-7
	{
		critical=1;
		/*if(row==0)
		{
			pos[row][0]=row;
			pos[row][1]=j;
			//cal(row+1,0,pos);
		}
		*/
		for(int i=0;i<row;i++)
		{
			if(row!=pos[i][0] && j!=pos[i][1] && (row+j)!=(pos[i][0]+pos[i][1]) && (row-j)!=(pos[i][0]-pos[i][1]))
				critical=1;
			else
			{
				critical=0;
				break;
			}

		}
		if(critical)
		{
			pos[row][0]=row;
			pos[row][1]=j;
			if(row==(LEN-1))
			{
				pri_position(pos);
				count++;
				printf("\n");
				return 0;
			}
			cal(row+1,0, pos);
		}
		else
			continue;
	}
	/*if(pos[row-1][1]+1<LEN)
		cal(row-1,pos[row-1][1]+1,pos);
	else
		cal(row-2,pos[row-2][1]+1,pos);
		*/
}








