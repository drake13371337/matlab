#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double rectangle(double a, double b, double e);
double trapeze(double a, double b, double e);
double simpson(double a, double b, double e);
double func(double x);

int main(){
    double a, b;
    a=0.6;
    b=1.724;
    double e = 0.0001;
    double e1 = 0.00001;

    trapeze(a, b, e);
    rectangle(a, b, e);
    simpson(a, b, e);
    cout<<endl;
    trapeze(a, b, e1);
    rectangle(a, b, e1);
    simpson(a, b, e1);

    return 0;
}

double func(double x){
    return pow((x+pow(x, 3)), 0.5);
}

double trapeze(double a, double b, double e){
    double res, h, buff;
    int n=1;
    res=0;
    buff=0;
    while(true){
        h=(b-a)/n;
        for(int i=1; i<n; i++)
            res=res+func(a+h*i);
        res=(res*2+func(a)+func(b))*h/2;
        if(abs(buff-res)<=(e*3)){
            cout<<"Trapeze: res = "<<setprecision(8)<<res<<", n = "<<n<<", e = "<<e<<endl;
            return 0;
        }
        buff=res;
        res=0;
        n++;
    }
    return 0;
}

double rectangle(double a, double b, double e){
    double res, h, buff;
    int n=1;
    int trg = 1;
    while(trg){
        h=(b-a)/n;

        for(int i=0; i<n; i++)
            res=res+func(a+h*i);
        res=res*h;

        if(abs(buff-res)<=(e*3)){
            cout<<"Rectangle(left): res = "<<setprecision(8)<<res<<", n = "<<n<<", e = "<<e<<endl;
            n=1;
            trg=0;
        } else n++;
        buff=res;
        res=0;
    }
    trg=1;
    while(trg){
        h=(b-a)/n;

        for(int i=1; i<n+1; i++)
            res=res+func(a+h*i);
        res=res*h;

        if(abs(buff-res)<=(e*3)){
            cout<<"Rectangle(right): res = "<<setprecision(8)<<res<<", n = "<<n<<", e = "<<e<<endl;
            trg=0;
            n=1;
        } else n++;
        buff=res;
        res=0;
    }
    trg=1;
    while(trg){
        h=(b-a)/n;

        for(int i=1; i<n; i++)
            res=res+func(a+h*i);
        res=(res+(func(a)+func(b))/2)*h;

        if(abs(buff-res)<=(e*3)){
            cout<<"Rectangle(middle): res = "<<setprecision(8)<<res<<", n = "<<n<<", e = "<<e<<endl;
            trg=0;
        } else n++;
        buff=res;
        res=0;
    }
    return 0;
}

double simpson(double a, double b, double e){
    double res, res1, h, buff;
    int n=2;
    res=0;
    buff=0;
    res1=0;

    while(true){
        h=(b-a)/n/2;

        for(int i=1; i<n+1; i++)
            res=res+func(a+h*(2*i-1));
        res=res*4;
        for(int i=1; i<n; i++)
            res1=res1+func(a+h*2*i);
        res1=res1*2;
        res=res+res1;

        res=(res+func(a)+func(b))*h/3;

        if(abs(buff-res)<=(e*15)){
            cout<<"Simpson: res = "<<setprecision(8)<<res<<", n = "<<n<<", e = "<<e<<endl;
            return 0;
        }
        buff=res;
        res=0;
        res1=0;
        n=n+2;
    }
    return 0;
}
