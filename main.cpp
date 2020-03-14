#include <iostream>
#include <cmath>

using namespace std;

void func(double x, double *y, double *res){
    if(x==0) res[0]=(-1)*y[0]*y[1];
    else res[0]=(-1)*y[0]*y[1]+sin(x)/x;
    //cout<<y[0]<<endl;
    //cout<<y[1]<<endl;
    res[1]=(-1)*y[1]*y[1]+(2.5+25/40)*x/(1+x*x);
    //cout<<res[0]<<endl;
    //cout<<res[1]<<endl;
}

void reverse_matr(double **Ai, int n, double **res){
    double **A = new double*[n];
    double **B = new double*[n];
    double temp;

    for(int i=0; i<n; i++){
        A[i] = new double[n];
        for(int j=0; j<n; j++) A[i][j]=Ai[i][j];
    }
    for(int i=0; i<n; i++){
        B[i] = new double[n];
        for(int j=0; j<n; j++){
            B[i][j]=0;
            if(i==j) B[i][j]=1;
        }
    }
    for(int k=0; k<n; k++){
        temp = A[k][k];
        for(int j=0; j<n; j++){
            A[k][j]/=temp;
            B[k][j]/=temp;
        }
        for(int i=k+1; i<n; i++){
            temp = A[i][k];
            for(int j=0; j<n; j++){
                A[i][j]-=A[k][j]*temp;
                B[i][j]-=B[k][j]*temp;
            }
        }
    }
    for(int k=n-1; k>0; k--){
        for(int i=k-1; i>=0; i--){
            temp = A[i][k];
            for (int j=0; j<n; j++){
                A[i][j]-=A[k][j]*temp;
                B[i][j]-=B[k][j]*temp;
            }
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            res[i][j]=B[i][j];
        }
    }
    for(int i=0; i<n; i++){
        delete[] A[i];
        delete[] B[i];
    }
}

void mult(double **A, double *B, int n, double *res){
    for(int i=0; i<n; i++)
        for(int k=0; k<n; k++)
            res[i]=res[i]+A[i][k]*B[k];
}

void jacobi(double **a, double *f, double *x, int n, double e){
    double *buff = new double[n];
    double nr;
    int counter=0;
    for(int i=0; i<n; i++) x[i]=0;
    do{
        for(int i=0; i<n; i++){
            buff[i]=f[i];
            for(int j=0; j<n; j++){
                if(i!=j) buff[i]-=a[i][j]*x[j];
            }
            buff[i]/=a[i][i];
        }
        nr=fabs(x[0]-buff[0]);
        for(int i=0; i<n; i++){
            if(fabs(x[i]-buff[i])>nr) nr=fabs(x[i]-buff[i]);
            x[i]=buff[i];
        }
        counter++;
    } while(nr>e);
    delete[] buff;
}

double func_diff(int i, int j, double *y){
    if(i==0 && j==0)
        return y[1]*(-1);
    if(i==0 && j==1)
        return y[0]*(-1);
    if(i==1 && j==0)
        return 0;
    if(i==1 && j==1)
        return (-2)*y[1];
    return 0;
}

void wron(double *y, double **res, int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            res[i][j]=func_diff(i, j, y);
        }
    }
}

void func_new(double tk1, double etk, double *yk, double *yk1, int n, double *res){
    double *F = new double[n];
    func(tk1, yk1, F);
    for(int i=0; i<n; i++)
        res[i]=yk1[i]-yk[i]-etk*F[i];
    delete[] F;
}

void Newt(double etk, double tk1, double *yk, double *yk1, double *x0, int n, double eps){
    double *F = new double[n];
    double **W = new double*[n];
    double **tW = new double*[n];
    double *x = new double[n];
    double *x1 = new double[n];
    double *buff = new double[n];
    bool trigger = true;
    int iter = 0;
    double maxe;
    for(int i=0; i<n; i++){
        W[i] = new double[n];
        tW[i] = new double[n];
        x[i]=x0[i];
    }
    wron(yk, W, n);
    func_new(tk1, etk, yk, x, n, F);
    for(int i=0; i<n; i++)
        buff[i]=(-1)*F[i];
    jacobi(W, buff, x1, n, eps);
    //reverse_matr(W, n, tW);
    /*while(trigger){
        cout<<"!"<<endl;
        func_new(tk1, etk, yk, x, n, F);
        mult(tW, F, n, buff);

        for(int i=0; i<n; i++){
            x1[i]=x[i]-buff[i];
            F[i]=fabs(x1[i]-x[i]);
        }

        maxe=F[0];
        for(int i=0; i<n; i++)
            if(F[i]>maxe) maxe=F[i];
        if(maxe<eps) trigger=false;
        for(int i=0; i<n; i++)
            x[i]=x1[i];
        iter++;
    }*/
    for(int i=0; i<n; i++)
        yk1[i]=x1[i]-x[i];
    for(int i=0; i<n; i++){
        delete[] W[i];
        delete[] tW[i];
    }
    delete[] F;
    delete[] x;
    delete[] x1;
    delete[] buff;
}

void y_eiler(double *u0, double T, double ei, double tm, int n){
    double tk=0.0001;
    double etkmin;
    int iter=1;

    double *f = new double[n];
    double *f1 = new double[n];
    double *etkv = new double[n];
    double *yk = new double[n];
    for(int i=0; i<n; i++)
        yk[i]=u0[i];

    cout<<"Yavniy Metod:"<<endl;
    while(tk<T){
        func(tk, yk, f1);
        for(int i=0; i<n; i++)
            f[i]=yk[i];
        for(int i=0; i<n; i++)
            etkv[i]=ei/(fabs(f1[i])+ei/tm);
        etkmin=etkv[0];
        for(int i=0; i<n; i++)
            if(etkv[i]<etkmin) etkmin=etkv[i];
        for(int i=0; i<n; i++)
            yk[i]=f[i]+etkmin*f1[i];
        tk=tk+etkmin;
        if(tk>T) tk=T;
        iter++;
    }
    cout<<iter-1<<") yk = {";
    for(int i=0; i<n; i++)
        cout<<yk[i]<<"  ";
    cout<<"}; tk = "<<tk<<endl;

    delete[] f;
    delete[] f1;
    delete[] etkv;
    delete[] yk;
}

void ny_eiler(double *u0, double T, double ei, double tmin, double tmax, int n){
    double *f = new double[n];
    double *f1 = new double[n];
    double *etkv = new double[n];
    double *yk = new double[n];
    double *yk0 = new double[n];
    double *x0 = new double[n];
    double *yk1 = new double[n];
    double *eik = new double[n];
    for(int i=0; i<n; i++){
        yk[i]=u0[i];
        yk0[i]=u0[i];
        yk1[i]=u0[i];
        x0[i]=1;
    }

    double etk=tmin;
    double etk0=tmin;
    double etk1;
    double tk=0.0001;
    double tk1;
    double etkmin=T;
    double eikmax;
    int iter = 1;

    while(tk<T){
        eikmax=ei*2;
        while(fabs(eikmax)>ei){
            tk1=tk+etk;
            Newt(etk, tk1, yk, yk1, x0, n, 0.01);
            for(int i=0; i<n; i++){
                cout<<yk1[i]<<" | ";
            } cout<<endl;
            for(int i=0; i<n; i++){
                cout<<yk[i]<<" ";
            } cout<<endl;
            for(int i=0; i<n; i++){
                cout<<yk0[i]<<" ] ";
            } cout<<endl;
            for(int i=0; i<n; i++)
                eik[i]=(-1)*(etk/(etk+etk0))*(yk1[i]-yk[i]-(etk/etk0)*(yk[i]-yk0[i]));
            eikmax=fabs(eik[0]);
            for(int i=0; i<n; i++)
                if(fabs(eik[i])>eikmax) eikmax=fabs(eik[i]);
            if(fabs(eikmax)>ei){
                etk=etk/2;
                cout<<etk<<endl;
                tk1=tk;
                for(int i=0; i<n; i++){
                    yk1[i]=yk[i];
                }
            }
        }
        for(int i=0; i<n; i++){
            etkv[i]=sqrt(ei/fabs(eik[i]))*etk;
            cout<<etkv[i]<<" ";
        } cout<<endl;
        etkmin=etkv[0];
        for(int i=0; i<n; i++)
            if(etkv[i]>etkmin) etkmin=etkv[i];
        etk1=etkmin;
        if(etk1>tmax){
            etk1=tmax;
        }

        cout<<iter<<") yk = {";
        for(int i=0; i<n; i++)
            cout<<yk1[i]<<"  ";
        cout<<"}; tk = "<<tk1<<endl;
        iter++;
        for(int i=0; i<n; i++){
            yk0[i]=yk[i];
            x0[i]=yk1[i];
            yk[i]=yk1[i];
            yk1[i]=0;
        }
        etk0=etk;
        etk=etk1;
        if(iter>10) break;
    }
    delete[] f;
    delete[] f1;
    delete[] etkv;
    delete[] yk;
    delete[] yk0;
    delete[] yk1;
    delete[] x0;
}

int main(){
    double u0[2] = {0, -0.412};
    //y_eiler(u0, 1, 0.01, 1, 2);
    ny_eiler(u0, 1, 0.01, 0.1, 1, 2);
    return 0;
}
