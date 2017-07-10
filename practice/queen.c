#include<stdio.h>

#define LEN 8

int cal(int row, int col, int (*pos)[2]);
void pri_position(int (*pos)[2]);

int main()
{
//	char check_board[LEN][LEN];
//	char result[LEN][LEN];
	int position[LEN][2];
	cal(0,0,position);
	pri_position(position);



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
		printf("%d %d\n",pos[i][1],pos[i][2]);
}

int cal(int row,int col,int (*pos)[2])
{
	int j,critical;
	if(row==0)
	{
		pos[row][1]=row;
		pos[row][2]=col;
		cal(row+1,0,pos);
	}

	for(j=col;j<LEN;j++)  //row 0-7
	{
		for(int i=0;i<row;i++)
		{
			if(row!=pos[i][1] && j!=pos[i][2] && (row+j)!=(pos[i][1]+pos[i][2]) && (row-j)!=(pos[i][1]-pos[i][2]))
				critical=1;
			else
			{
				critical=0;
				break;
			}

		}
		if(critical)
		{
			pos[row][1]=row;
			pos[row][2]=j;
			if(row==(LEN-1))
				return 0;
			cal(row+1,0, pos);
		}
		else
			continue;
	}
	if(pos[row-1][2]+1<LEN)
		cal(row-1,pos[row-1][2]+1,pos);
	else
		cal(row-2,pos[row-2][2]+1,pos);
}








