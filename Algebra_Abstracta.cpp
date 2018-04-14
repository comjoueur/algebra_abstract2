#include<iostream>
#include<string>
using namespace std;
int min(int a,int b){
	if(a<b)return a;
	return b;
}
int valor(int a){
	if(a<0)a=a*-1;
	return a;
}
int pedido(int clave,int f,int c,int p=0){
	f++;c++;
	int k=min(min(c,clave-c+1),min(f,clave-f+1));
	int tmp=4*(clave*(k-1)-(k-1)*(k-1))+p;
	if(c+f>=clave+1)
		tmp+=valor(f-k)+valor(c-(clave-k+1))+1;
	else
		tmp+=4*(clave-(2*k-1))-valor(f-k)-valor(c-(clave-k+1))+1;
	tmp--;
	return tmp;
}
string  pedido2(int clave,int f,string p,int y=0){
	string r;
	f++;
	if(f==1){
		if((clave+1)/2+clave-1+y-1<p.size())r+=p[(clave+1)/2+clave-1+y-1];
	}
	else if(f<=clave/2){
		if((clave+1)/2+clave-f+y-1<p.size())r+=p[(clave+1)/2+clave-f+y-1];
		if((clave+1)/2+clave+f-2+y-1<p.size())r+=p[(clave+1)/2+clave+f-2+y-1];
	}
	else if(f<clave){
		if(f-clave/2+y-1<p.size())r+=p[f-clave/2+y-1];
		if((clave+1)/2+clave-f+y-1<p.size())r+=p[(clave+1)/2+clave-f+y-1];
		if((clave+1)/2+clave+f-2+y-1<p.size())r+=p[(clave+1)/2+clave+f-2+y-1];
	}
	else{
		if((clave+1)/2+y-1<p.size())r+=p[(clave+1)/2+y-1];
		if((clave+1)/2+2*clave-2+y-1<p.size())r+=p[(clave+1)/2+2*clave-2+y-1];
	}
	return r;
}
int pedido3(int clave,int f,int c,int y=0){
	if(clave%2==0){
		return clave*clave-(pedido(clave,c,f))-1+y;
	}
	else{
		return clave*clave-(pedido(clave,clave-c-1,clave-f-1))-1+y;
	}
}
string pedido4(int clave,int f,string p,int y=0){
	string r;
	f++;
	if(f==1){
		if(clave+y-1<p.size())r+=p[clave+y-1];
		if(3*clave-2+y-1<p.size())r+=p[3*clave-2+y-1];
	}
	else if(f<clave){
		if(clave-f+1+y-1<p.size())r+=p[clave-f+1+y-1];
		if(clave+f-1+y-1<p.size())r+=p[clave+f-1+y-1];
		if(3*clave-2-f+1+y-1<p.size())r+=p[3*clave-2-f+1+y-1];
	}
	else{
		if(0+y<p.size())r+=p[0+y];
		if(2*clave-1+y-1<p.size())r+=p[2*clave-1+y-1];
	}
	return r;
}
string cifrar(string p,int clave,int cuadrados){
	string r;
	int s=0;
	for(int i=0;i<clave;i++){
		for(int j=0;j<cuadrados;j++){
			if(j%4==0){
				for(int k=0;k<clave;k++){
					int y=pedido(clave,i,k,s);
					if(y<p.size())r+=p[y];
				}
				s+=clave;
			}
			else if(j%4==1){
				r+=pedido2(clave,i,p,s);
				if(i==0)s++;
				else if(i<clave/2)s+=2;
				else if(i<clave)s+=3;
				else s+=2;
			}
			else if(j%4==2){
				for(int k=0;k<clave;k++){
					int y=pedido3(clave,i,k,s);
					if(y<p.size())r+=p[y];
				}
				s+=clave;
			}
			else if(j%4==3){
				r+=pedido4(clave,i,p,s);
				if(i==0||i==clave-1)s+=2;
				else s+=3;
			}
			cout<<j<<" "<<s<<endl;
		}
	}
	return r;
}
int main(){
	int clave,cuadrado;
	string p;
	cin>>p>>clave>>cuadrado;
	cout<<cifrar(p,clave,cuadrado)<<endl;
	for(int t=0;t<clave;t++){
		cout<<pedido(clave,0,t)<<endl;
	}
	return 0;
}
