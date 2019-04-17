#include<stdio.h>
#include<math.h>

struct para{
        float BaseRadius;
        float BaseHeight;
        float VolumnRadius;
        float VolumnOut;
        float VolumnCenter;
        float Xrange;
        float Yrange,Yinit;
        float Zrange;
};
void InitPara(struct para *pst)  //input the four parameter
{
    printf("please input the BaseRadius:");
    scanf("%f",pst->BaseRadius);
    printf("please input the BaseHeight:");
    scanf("%f",pst->BaseHeight);
    printf("please input the VolumnRadius:");
    scanf("%f",pst->VolumnRadius);
    printf("please input the VolumnOut:");
    scanf("%f",pst->VolumnOut);
    pst->VolumnCenter=pst->BaseRadius+pst->VolumnOut-pst->VolumnRadius;
    pst->Xrange = sqrt(pst->BaseRadius*pst->BaseRadius-(pst->BaseRadius-pst->BaseHeight)*(pst->BaseRadius-pst->BaseHeight));
    pst->Yrange = pst->BaseRadius+pst->VolumnOut;
    pst->Yinit = pst->BaseRadius-BaseHeight;
    pst->Zrange = pst->VolumnRadius;

}

int base(float x,float y,float z)
int column(float x,float y,float z)

int main()
{
    struct para L;
    InitPara(&L);
    float x,y,z,step;
    printf("please input the step of Microelement:");
    for(x=0;x<L.Xrange;x=x+step)






    return 0;
}
