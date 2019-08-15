#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int neqs=4;
double L1,L2,m1,m2,g;

double f(int i,double y1,double y2,double y3,double y4) {
    double resultat=4;
    switch(i) {
        case 0:
            resultat=y3;
            break;
        case 1:
            resultat=y4;
            break;
        case 2:
            resultat=(-g*sin(y1)*(m1+m2)-m2*L2*y4*y4*sin(y1-y2)-m2*cos(y1-y2)*(L1*y3*y3*sin(y1-y2)-g*sin(y2)))/(L1*(m1+m2-m2*cos(y1-y2)*cos(y1-y2)));
            break;
        case 3:
            resultat=(-cos(y1-y2)*(-g*sin(y1)*(m1+m2)-m2*L2*y4*y4*sin(y1-y2))+(m1+m2)*(L1*y3*y3*sin(y1-y2)-g*sin(y2)))/(L2*(m1+m2-m2*cos(y1-y2)*cos(y1-y2)));
            break;
    }
    return resultat;
}

int main(void) {
    int iteracions;
    printf("Nombre d'iteracions: ");
    if(scanf("%d",&iteracions));
    
    double y0[neqs];
    for(int i=0; i<neqs; i++) {
        double cinicial;
        printf("y%d(0)=",i+1);
        if(scanf("%lf",&cinicial));
        y0[i]=cinicial;
    }
    
    double h;
    printf("Step: ");if(scanf("%lf",&h));
    printf("L1: ");if(scanf("%lf",&L1));
    printf("L2: ");if(scanf("%lf",&L2));
    printf("m1: ");if(scanf("%lf",&m1));
    printf("m2: ");if(scanf("%lf",&m2));
    printf("g: ");if(scanf("%lf",&g));
    
    FILE *dt1;FILE *dt2;
    dt1=fopen("interior.dat","w");
    dt2=fopen("exterior.dat","w");
    
    fprintf(dt1,"Recorregut interior\n");
    fprintf(dt2,"Recorregut exterior\n");
    
    double y[neqs],A[neqs],B[neqs],C[neqs],D[neqs];
    for(int i=0; i < neqs; i++) {
        y[i]=y0[i];
    }
    for(int i=0; i<iteracions; i++) {
        for(int j=0; j<neqs; j++) {
            A[j]=f(j,y[0],y[1],y[2],y[3]);
            B[j]=f(j,y[0]+(h/2.)*A[0],y[1]+(h/2.)*A[1],y[2]+(h/2.)*A[2],y[3]+(h/2.)*A[3]);
            C[j]=f(j,y[0]+(h/2.)*B[0],y[1]+(h/2.)*B[1],y[2]+(h/2.)*B[2],y[3]+(h/2.)*B[3]);
            D[j]=f(j,y[0]+h*C[0],y[1]+h*C[1],y[2]+h*C[2],y[3]+h*C[3]);
            y[j]=y[j]+(h/6.)*( A[j]+2*B[j]+2*C[j]+D[j] );
        }
        fprintf(dt1,"%lf\t%lf\n",L1*sin(y[0]),-L1*cos(y[0]));
        fprintf(dt2,"%lf\t%lf\n",L1*sin(y[0])+L2*sin(y[1]),-L1*cos(y[0])-L2*cos(y[1]));
    }
    fclose(dt1);fclose(dt2);
    return 0;
}
