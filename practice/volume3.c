#include<stdio.h>
#include<math.h>

struct data{
        double BaseRadius;
        double BaseHeight;
        double ColumnRadius;
        double ColumnOut;

        double Center,CoMin,CoMax; //上圆柱参数
        double SectorMin,SectorMax;
};
struct integration{
        double Xmax;
        double Ymin,Ymax;
        double Zmin,Zmax;//扇形界限，区分6种情况
        double VolBase,VolCol;
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

double SectorArea(double radius,double distance)
{
    double CircleArea;
    CircleArea=acos(distance/radius)*pow(radius,2)-radius*distance;
    return CircleArea;
}

double Pytha(double hypo,double ang)
{
    return sqrt(hypo*hypo-ang*ang);
}

void ProcessPara(struct data *pst,struct integration *i)
{
    double disH,disL;               //上圆柱下沉的位置，和扇形上下限的距离
    double HighCol,HighBase;        //圆柱体的高
    HighCol=Pytha(pst->BaseRadius,pst->BaseRadius-pst->BaseHeight); //定值？

    if(pst->Center>=pst->SectorMax){    //注意0有没有影响
        if(pst->CoMin>=pst->SectorMin){
            disH=pst->Center-pst->SectorMax;

            i->Ymin=pst->CoMin;
            i->Ymax=pst->SectorMax;
            i->Zmin=0;
            i->Zmax=Pytha(pst->ColumnRadius,disH);
            i->Xmin=0;
            i->Xmax=Pytha(pst->BaseRadius,pst->CoMin);
            i->VolCol=3.14*pow(pst->ColumnRadius,2)*HighCol;
            HighBase=2*i->Zmax;
            i->VolBase=SectorArea(pst->BaseRadius,pst->BaseRadius-pst->CoMin);

        }

    }
    else if(pst->Center<=pst->SectorMin){

    }
    else{

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
    if((y-pst->ColumnCenter)*(y-pst->ColumnCenter)+z*z>(pst->ColumnRadius)*(pst->ColumnRadius))
        return 1;
    else
        return 0;
}

int main()
{
    struct data L;
    InitPara(&L);
    double x,y,z,step,result;
    result=0;
    printf("please input the step of Microelement:");
    scanf("%lf",&step);
    for(x=0;x<L.Xrange;x=x+step)
    {
        for(z=0;z<L.Zrange;z=z+step)
        {
             for(y=L.Yinit;y<L.Yrange;y=y+step)
                {
                    if(base(x,y,L.BaseRadius)&&column(y,z,&L))
                        result=result+step*step*step;
                }
        }
    }
    printf("the Volumn is %f\n",4*result);
    return 0;
}
