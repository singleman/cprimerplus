#include<stdio.h>
#include<math.h>
#include<time.h>

struct data{
        double BaseRadius;
        double BaseHeight;
        double ColumnRadius;
        double ColumnOut;

        double Center,CoMin,CoMax; //上圆柱参数
        double SectorMin,SectorMax;
};
struct integration{
        double Xmin,Xmax;
        double Ymin,Ymax;
        double Zmin,Zmax;//扇形界限，区分6种情况
        double VolBase,VolCol;
        int sign;
};

void InitPara(struct data *pst)
{
    printf("please input the BaseRadius:"); //input the four parameter
    scanf("%lf",&pst->BaseRadius);
    printf("please input the BaseHeight:");
    scanf("%lf",&pst->BaseHeight);
    printf("please input the ColumnRadius:");
    scanf("%lf",&pst->ColumnRadius);
    printf("please input the ColumnOut:");
    scanf("%lf",&pst->ColumnOut);

    pst->Center=pst->BaseRadius+pst->ColumnOut-pst->ColumnRadius; //上圆柱参数
    pst->CoMin=pst->Center-pst->ColumnRadius;
    pst->CoMax=pst->Center+pst->ColumnRadius;

    pst->SectorMax=pst->BaseRadius;                             //扇形上下限
    pst->SectorMin=pst->BaseRadius-pst->BaseHeight;
}

double SectorArea(double radius,double distance)	//弧顶面积=扇形面积-三角形面积 
{
    double CircleArea;
    CircleArea=acos(distance/radius)*pow(radius,2)-radius*distance;
    return CircleArea;
}

double Pytha(double hypo,double ang)		//勾股定理 
{
    return sqrt(hypo*hypo-ang*ang);
}

void ProcessPara(struct data *pst,struct integration *i)
{
    double disH,disL;               //上圆柱下沉的位置，和扇形上下限的距离
    double HighCol,HighBase;        //圆柱体的高
    HighCol=2*Pytha(pst->BaseRadius,pst->BaseRadius-pst->BaseHeight); //定值？

    if(pst->Center>=pst->SectorMax){    //情况1：圆心高于扇形(注意0有没有影响) 
        disH=pst->Center-pst->SectorMax;
        disL=pst->Center-pst->SectorMin;
        
		if(pst->CoMin>=pst->SectorMin){					//1A圆柱沉入扇形区域 
            i->Ymin=pst->CoMin;							//积分范围 
            i->Ymax=pst->SectorMax;
            i->Zmin=0;
            i->Zmax=Pytha(pst->ColumnRadius,disH);
            i->Xmin=0;
            i->Xmax=Pytha(pst->BaseRadius,i->Ymin);
            i->VolCol=M_PI*pow(pst->ColumnRadius,2)*HighCol;	//体积 
            HighBase=2*i->Zmax;
            i->VolBase=SectorArea(pst->BaseRadius,i->Ymin)*HighBase;
            i->sign=1;
        }
        else{										//1B圆柱沉入底座 
			i->Ymin=pst->SectorMin;
			i->Ymax=pst->SectorMax;
			i->Zmin=Pytha(pst->ColumnRadius,disL);
			i->Zmax=Pytha(pst->ColumnRadius,disH);
			i->Xmin=0;
			i->Xmax=Pytha(pst->BaseRadius,i->Ymin); 
			i->VolCol=(M_PI*pow(pst->ColumnRadius,2)-SectorArea(pst->ColumnRadius,disL))*HighCol;
			HighBase=2*i->Zmax;
			i->VolBase=SectorArea(pst->BaseRadius,i->Ymin)*HighBase;
			i->sign=2;
		} 
    }
    else if(pst->Center<=pst->SectorMin){	//情况2：圆心沉入底座
	 		disH=pst->SectorMax-pst->Center;
        	disL=pst->SectorMin-pst->Center;
			 
			if(pst->CoMax<=pst->SectorMax){					//2A圆柱低于扇形区域 
	            i->Ymin=pst->SectorMin;							//积分范围 
	            i->Ymax=pst->CoMax;
	            i->Zmin=0;
	            i->Zmax=Pytha(pst->ColumnRadius,disL);
	            i->Xmin=0;
	            i->Xmax=Pytha(pst->BaseRadius,i->Ymin);
	            i->VolCol=SectorArea(pst->ColumnRadius,disL)*HighCol;	//体积 
	            HighBase=2*i->Zmax;
	            i->VolBase=(SectorArea(pst->BaseRadius,i->Ymin)-SectorArea(pst->BaseRadius,i->Ymax))*HighBase;
	            i->sign=3;
	        }
	        else{										//2B圆柱高于扇形 
				i->Ymin=pst->SectorMin;
				i->Ymax=pst->SectorMax;
				i->Zmin=Pytha(pst->ColumnRadius,disH);
				i->Zmax=Pytha(pst->ColumnRadius,disL);
				i->Xmin=0;
				i->Xmax=Pytha(pst->BaseRadius,i->Ymin); 
				i->VolCol=SectorArea(pst->ColumnRadius,disL)*HighCol;
				HighBase=2*i->Zmax;
				i->VolBase=SectorArea(pst->BaseRadius,i->Ymin)*HighBase;
				i->sign=4;
			} 

    }
    else{
		disH=pst->SectorMax-pst->Center;
        disL=pst->Center-pst->SectorMin;								//情况3：圆心位于扇形区域 
		if((pst->CoMax>pst->SectorMax)&&(pst->CoMin<pst->SectorMin))	//3A:圆柱覆盖三个区域
		{
			i->Ymin=pst->SectorMin;
			i->Ymax=pst->SectorMax;
			if(disH>disL)
				i->Zmin=Pytha(pst->ColumnRadius,disH);
			else
				i->Zmin=Pytha(pst->ColumnRadius,disL);
			i->Zmax=pst->ColumnRadius;
			i->Xmin=0;
			i->Xmax=Pytha(pst->BaseRadius,i->Ymin);
			i->VolCol=(M_PI*pow(pst->ColumnRadius,2)-SectorArea(pst->ColumnRadius,disL))*HighCol;
			HighBase=2*i->Zmax;
			i->VolBase=SectorArea(pst->BaseRadius,i->Ymin)*HighBase;
			i->sign=5;
		} 
		if((pst->CoMax<=pst->SectorMax)&&(pst->CoMin>=pst->SectorMin))	//3B:圆柱位于扇形区域
		{
			i->Ymin=pst->CoMin;
			i->Ymax=pst->CoMax;
			i->Zmin=0;
			i->Zmax=pst->ColumnRadius;
			i->Xmin=0;
			i->Xmax=Pytha(pst->BaseRadius,i->Ymin);
			i->VolCol=M_PI*pow(pst->ColumnRadius,2)*HighCol;
			HighBase=2*i->Zmax;
			i->VolBase=(SectorArea(pst->BaseRadius,i->Ymin)-SectorArea(pst->BaseRadius,i->Ymax))*HighBase;
			i->sign=6;
		} 
		if((pst->CoMax<=pst->SectorMax)&&(pst->CoMin<pst->SectorMin))	//3C:圆柱覆盖下方两个区域
		{
			i->Ymin=pst->SectorMin;
			i->Ymax=pst->CoMax;
			i->Zmin=0;
			i->Zmax=pst->ColumnRadius;
			i->Xmin=0;
			i->Xmax=Pytha(pst->BaseRadius,i->Ymin);
			i->VolCol=(M_PI*pow(pst->ColumnRadius,2)-SectorArea(pst->ColumnRadius,disL))*HighCol;
			HighBase=2*i->Zmax;
			i->VolBase=(SectorArea(pst->BaseRadius,i->Ymin)-SectorArea(pst->BaseRadius,i->Ymax))*HighBase;
			i->sign=7;
		}
		if((pst->CoMax>pst->SectorMax)&&(pst->CoMin>=pst->SectorMin))	//3D:圆柱覆盖上方两个区域
		{
			i->Ymin=pst->CoMin;
			i->Ymax=pst->SectorMax;
			i->Zmin=0;
			i->Zmax=pst->ColumnRadius;
			i->Xmin=0;
			i->Xmax=Pytha(pst->BaseRadius,i->Ymin);
			i->VolCol=M_PI*pow(pst->ColumnRadius,2)*HighCol;
			HighBase=2*i->Zmax;
			i->VolBase=SectorArea(pst->BaseRadius,i->Ymin)*HighBase;
			i->sign=8;
		}
    }

}



int base(double x,double y,double radius)   //在下底座扇形内部
{
    if(x*x+y*y<radius*radius)
        return 1;
    else
        return 0;
}
int column(double y,double z,struct data *pst) //在上底座圆柱外面
{
    if((y-pst->Center)*(y-pst->Center)+z*z>(pst->ColumnRadius)*(pst->ColumnRadius))
        return 1;
    else
        return 0;
}

int main()
{
	time_t first,second;
		
    struct data L;
    struct integration M; 
    InitPara(&L);
    ProcessPara(&L,&M);
    printf("M.sign=%d\n",M.sign);
    double x,y,z,step,result;
    result=0;
    //printf("please input the step of Microelement:");
    //scanf("%lf",&step);
    for(step=0.1;step>0.000001;step=step/10)
	{
		first=time(NULL);
	    for(x=M.Xmin;x<M.Xmax;x=x+step)
	    {
	        for(z=M.Zmin;z<M.Zmax;z=z+step)
	        {
	             for(y=M.Ymin;y<M.Ymax;y=y+step)
	                {
	                    if(base(x,y,L.BaseRadius)&&column(y,z,&L))
	                        result=result+pow(step,3);
	                }
	        }
	    }
	    second=time(NULL);
    	printf("step= %lf the volumn is %f,time is %d\n",step,M.VolCol-(M.VolBase-4*result),second-first);
	}
    return 0;
}
