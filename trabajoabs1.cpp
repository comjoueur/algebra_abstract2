#include<iostream>
#include<string>
using namespace std;
int min(int a,int b){
	return (a<=b)*a+(a>b)*b;
}
int valor(int a){
	return a-2*(a<0)*a;
}
int pedido(int clave,int f,int c,int p=0){
	f++;c++;
	int k=min(min(c,clave-c+1),min(f,clave-f+1));
	int tmp=4*(k-1)*(clave-k+1)+p;
	if(c+f>=clave+1)
		tmp+=valor(f-k)+valor(c-clave+k-1);
	else
		tmp+=4*(clave-2*k+1)-valor(f-k)-valor(c-clave+k-1);
	return tmp;
}
string  pedido2(int clave,int f,string p,int y=0){
	string r;
	f++;
	if(f==1){
		if(2*clave-(clave+1)/2-1+y)r+=p[2*clave-(clave+1)/2-1+y];
	}
	else if(f<=(clave-1)/2){
		if(2*clave-(clave+1)/2-f+y<p.size())r+=p[2*clave-(clave+1)/2+-f+y];
		if(2*clave-(clave+1)/2+f-2+y<p.size())r+=p[2*clave-(clave+1)/2+f-2+y];
	}
	else if(f<clave){
		if(f-clave/2+y-(clave&1)<p.size())r+=p[f-clave/2+y-(clave&1)];
		if((clave+1)/2+clave-f+y-(clave&1)<p.size())r+=p[(clave+1)/2+clave-f+y-(clave&1)];
		if((clave+1)/2+clave+f-2+y-(clave&1)<p.size())r+=p[(clave+1)/2+clave+f-2+y-(clave&1)];
	}
	else{
		if((clave+1)/2+y-(clave&1)<p.size())r+=p[(clave+1)/2+y-(clave&1)];
		if((clave+1)/2+2*clave-2+y-(clave&1)<p.size())r+=p[(clave+1)/2+2*clave-2+y-(clave&1)];
	}
	return r;
}
int pedido3(int clave,int f,int c,int y=0){
	if((clave&1)==0)return clave*clave-1-pedido(clave,f,c)+y;
	else return clave*clave-1-pedido(clave,clave-f-1,clave-c-1)+y;
}
string pedido4(int clave,int f,string p,int y=0){
	string r;
	f++;
	if(f==1){
		if(clave+y-1<p.size())r+=p[clave+y-1];
		if(3*clave+y-3<p.size())r+=p[3*clave+y-3];
	}
	else if(f<clave){
		if(clave-f+y<p.size())r+=p[clave-f+y];
		if(clave+f+y-2<p.size())r+=p[clave+f+y-2];
		if(3*clave-2-f+y<p.size())r+=p[3*clave-2-f+y];
	}
	else{
		if(y<p.size())r+=p[y];
		if(2*clave+y-2<p.size())r+=p[2*clave+y-2];
	}
	return r;
}
string cifrar(string p,int clave,int cuadrados){
	string r;
	int s=0;
	for(int i=0;i<clave;i++){
		s=0;
		for(int j=0;j<cuadrados;j++){
			if(j%4==0){
				for(int k=0;k<clave;k++){
					int y=pedido(clave,i,k,s);
					if(y<p.size())r+=p[y];
				}
				s+=clave*clave;
				//r+="#";
			}
			else if(j%4==1){
				string y=pedido2(clave,i,p,s);
				r+=y;
				s+=clave-((clave+1)/2)+1+2*(clave-1);
				//r+="#";
			}
			else if(j%4==2){
				for(int k=0;k<clave;k++){
					int y=pedido3(clave,i,k,s);
					if(y<p.size())r+=p[y];
				}
				s+=clave*clave;
				//r+="#";
			}
			else if(j%4==3){
				//r+="/";
				string t=pedido4(clave,i,p,s);
				r+=t;
				s+=3*clave-2;
				//r+="/";
			}
		}
	}
	return r;
}
int main(){
	int clave,cuadrados;
	char oracion[1000];
	cin.getline(oracion,1000);
	string p(oracion);
	cout<<"Ingrese la clave y el numero de cuadrados\n";
	cin>>clave>>cuadrados;
	cout<<"El cifrado es :"<<endl;
	cout<<cifrar(p,clave,cuadrados)<<endl;
	//cin>>p>>clave;
	//for(int i=0;i<clave;i++)cout<<pedido2(clave,i,p)<<endl;
	return 0;
}
