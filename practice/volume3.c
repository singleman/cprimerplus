#include<stdio.h>
#include<math.h>
#include<time.h>

struct data{
        double BaseRadius;
        double BaseHeight;
        double ColumnRadius;
        double ColumnOut;

        double Center,CoMin,CoMax; //��Բ������
        double SectorMin,SectorMax;
};
struct integration{
        double Xmin,Xmax;
        double Ymin,Ymax;
        double Zmin,Zmax;//���ν��ޣ�����6�����
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

    pst->Center=pst->BaseRadius+pst->ColumnOut-pst->ColumnRadius; //��Բ������
    pst->CoMin=pst->Center-pst->ColumnRadius;
    pst->CoMax=pst->Center+pst->ColumnRadius;

    pst->SectorMax=pst->BaseRadius;                             //����������
    pst->SectorMin=pst->BaseRadius-pst->BaseHeight;
}

void FilePara(struct data *pst,FILE **fp)////????
{
	fscanf(*fp,"%lf",&pst->BaseRadius);
    fscanf(*fp,"%lf",&pst->BaseHeight);
    fscanf(*fp,"%lf",&pst->ColumnRadius);
    fscanf(*fp,"%lf",&pst->ColumnOut);
	
    pst->Center=pst->BaseRadius+pst->ColumnOut-pst->ColumnRadius; //��Բ������
    pst->CoMin=pst->Center-pst->ColumnRadius;
    pst->CoMax=pst->Center+pst->ColumnRadius;

    pst->SectorMax=pst->BaseRadius;                             //����������
    pst->SectorMin=pst->BaseRadius-pst->BaseHeight;
	
}
double SectorArea(double radius,double distance)	//�������=�������-��������� 
{
    double CircleArea;
    CircleArea=acos(distance/radius)*pow(radius,2)-distance*sqrt(pow(radius,2)-pow(distance,2));
    return CircleArea;
}

double Pytha(double hypo,double ang)		//���ɶ��� 
{
    return sqrt(hypo*hypo-ang*ang);
}

void ProcessPara(struct data *pst,struct integration *i)
{
    double disH,disL;               //��Բ���³���λ�ã������������޵ľ���
    double HighCol,HighBase;        //Բ����ĸ�
    HighCol=2*Pytha(pst->BaseRadius,pst->BaseRadius-pst->BaseHeight); //��ֵ��

    if(pst->Center>=pst->SectorMax){    //���1��Բ�ĸ�������(ע��0��û��Ӱ��) 
        disH=pst->Center-pst->SectorMax;
        disL=pst->Center-pst->SectorMin;
        
		if(pst->CoMin>=pst->SectorMin){					//1AԲ�������������� 
            i->Ymin=pst->CoMin;							//���ַ�Χ 
            i->Ymax=pst->SectorMax;
            i->Zmin=0;
            i->Zmax=Pytha(pst->ColumnRadius,disH);
            i->Xmin=0;
            i->Xmax=Pytha(pst->BaseRadius,i->Ymin);
            i->VolCol=M_PI*pow(pst->ColumnRadius,2)*HighCol;	//��� 
            HighBase=2*i->Zmax;
            i->VolBase=SectorArea(pst->BaseRadius,i->Ymin)*HighBase;
            i->sign=1;
        }
        else{										//1BԲ��������� 
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
    else if(pst->Center<=pst->SectorMin){	//���2��Բ�ĳ������
	 		disH=pst->SectorMax-pst->Center;
        	disL=pst->SectorMin-pst->Center;
			 
			if(pst->CoMax<=pst->SectorMax){					//2AԲ�������������� 
	            i->Ymin=pst->SectorMin;							//���ַ�Χ 
	            i->Ymax=pst->CoMax;
	            i->Zmin=0;
	            i->Zmax=Pytha(pst->ColumnRadius,disL);
	            i->Xmin=0;
	            i->Xmax=Pytha(pst->BaseRadius,i->Ymin);
	            i->VolCol=SectorArea(pst->ColumnRadius,disL)*HighCol;	//��� 
	            HighBase=2*i->Zmax;
	            i->VolBase=(SectorArea(pst->BaseRadius,i->Ymin)-SectorArea(pst->BaseRadius,i->Ymax))*HighBase;
	            i->sign=3;
	        }
	        else{										//2BԲ���������� 
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
        disL=pst->Center-pst->SectorMin;								//���3��Բ��λ���������� 
		if((pst->CoMax>pst->SectorMax)&&(pst->CoMin<pst->SectorMin))	//3A:Բ��������������
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
		if((pst->CoMax<=pst->SectorMax)&&(pst->CoMin>=pst->SectorMin))	//3B:Բ��λ����������
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
		if((pst->CoMax<=pst->SectorMax)&&(pst->CoMin<pst->SectorMin))	//3C:Բ�������·���������
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
		if((pst->CoMax>pst->SectorMax)&&(pst->CoMin>=pst->SectorMin))	//3D:Բ�������Ϸ���������
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



int base(double x,double y,double radius)   //���µ��������ڲ�
{
    if(x*x+y*y<radius*radius)
        return 1;
    else
        return 0;
}
int column(double y,double z,struct data *pst) //���ϵ���Բ������
{
    if((y-pst->Center)*(y-pst->Center)+z*z>=(pst->ColumnRadius)*(pst->ColumnRadius))
        return 1;
    else
        return 0;
}

int main()
{
	time_t first,second;
	double x,y,z,step,volume;
	FILE *fp,*dp;
	char c;
	int row=0; 
	int i;
		
    struct data L;
    struct integration M;  
    
    printf("which way do you want to input the data:\n");
    printf("\t1.Manual.\n");
    printf("\t2.FIle:data.txt\n");
    scanf("%d",&i);
    if(i==1){
		InitPara(&L); //�ֶ���������
		ProcessPara(&L,&M);
		for(step=0.1;step>0.0001;step=step/10)
		{
				volume=0;
				first=time(NULL);
			    for(x=M.Xmin;x<M.Xmax;x=x+step)
			    {
			        for(z=M.Zmin;z<M.Zmax;z=z+step)
			        {
			             for(y=M.Ymin;y<M.Ymax;y=y+step)
			                {
			                	if(base(x,y,L.BaseRadius)&&column(y,z,&L)){
			                		volume=volume+pow(step,3);
			                	}
			                }
			        }
			    }
			    second=time(NULL);
		      	printf("step= %lf the volumn is %f,time is %d\n",step,M.VolCol-(M.VolBase-4*volume),second-first);
		}
	}
	else{
	    fp=fopen("result3.txt","a");
	    dp=fopen("data.txt","r");
	     
	    while((c=fgetc(dp))!=EOF){
	    	if(c=='\n')
	    		row++;
		} 
		rewind(dp); 
		for(i=0;i<row;i++){
			FilePara(&L,&dp); 
	    	ProcessPara(&L,&M); 
	
		    fprintf(fp,"The BaseRadius=%f\nThe BaseHeight=%f\nThe ColumnRadius=%f\nThe ColumnOut=%f\n",L.BaseRadius,L.BaseHeight,L.ColumnRadius,L.ColumnOut);
		    fprintf(fp,"M.sign=%d\n",M.sign);
		    for(step=0.1;step>0.0001;step=step/10)
			{
				volume=0;
				first=time(NULL);
			    for(x=M.Xmin;x<M.Xmax;x=x+step)
			    {
			        for(z=M.Zmin;z<M.Zmax;z=z+step)
			        {
			             for(y=M.Ymin;y<M.Ymax;y=y+step)
			                {
			                	if(base(x,y,L.BaseRadius)&&column(y,z,&L)){
			                		volume=volume+pow(step,3);
			                    //	fprintf(lp,"x=%f,y=%f,z=%f,result=%f\n",x,y,z,result);
								}
			                }
			        }
			    }
			    second=time(NULL);
		    	fprintf(fp,"\tstep= %lf the volume is %f,time is %d\n",step,M.VolCol-(M.VolBase-4*volume),second-first);
		    	printf("step= %lf the volumn is %f,time is %d\n",step,M.VolCol-(M.VolBase-4*volume),second-first);
			}
		}
	    
		fclose(fp);
		fclose(dp);
	}
    return 0;
}
