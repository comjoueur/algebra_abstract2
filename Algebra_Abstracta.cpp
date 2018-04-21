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
string relleno(string p,int clave,int cuadrados){
	int t=(cuadrados/4)*(clave*(2*clave+5)+clave/2-3);
	if(cuadrados%4>0){
		t+=clave*clave;
	}
	if(cuadrados%4>1){
		t+=2*clave+clave/2-1;
	}
	if(cuadrados%4>2){
		t+=clave*clave;
	}
	while(p.size()<t)p+='s';
	return p;
}
string cifrar(string p,int clave,int cuadrados){
	string r;
	p=relleno(p,clave,cuadrados);
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
			}
			else if(j%4==1){
				string y=pedido2(clave,i,p,s);
				r+=y;
				s+=clave-((clave+1)/2)+1+2*(clave-1);
			}
			else if(j%4==2){
				for(int k=0;k<clave;k++){
					int y=pedido3(clave,i,k,s);
					if(y<p.size())r+=p[y];
				}
				s+=clave*clave;
			}
			else if(j%4==3){
				string t=pedido4(clave,i,p,s);
				r+=t;
				s+=3*clave-2;
			}
		}
	}
	return r;
}
string descifrar(string p,int clave,int cuadrados){
	string r(p.size(),'x');
	bool b;
	int k=0,f=1,s=0,t=(cuadrados/4)*(clave*(2*clave+5)+clave/2-3);
	if(cuadrados%4>0)
		t+=clave*clave;
	if(cuadrados%4>1)
		t+=2*clave+clave/2-1;
	if(cuadrados%4>2)
		t+=clave*clave;
	while(k<p.size()){
		if(k<p.size()){
			for(int i=0;i<clave;i++){
				int x=pedido(clave,f-1,i,s);
				r[x]=p[k++];
			}
			s+=clave*clave;
			b=1;
		}
		if(s==t){f++;s=0;b=0;}
        	if(k<p.size() && b){
			if(f==1){
				r[2*clave-(clave+1)/2-1+s]=p[k++];
			}
			else if(f<=(clave-1)/2){
				r[2*clave-(clave+1)/2+-f+s]=p[k++];
				r[2*clave-(clave+1)/2+f-2+s]=p[k++];
			}
			else if(f<clave){
				r[f-clave/2+s-(clave&1)]=p[k++];
				r[(clave+1)/2+clave-f+s-(clave&1)]=p[k++];
				r[(clave+1)/2+clave+f-2+s-(clave&1)]=p[k++];
			}
			else{
				r[(clave+1)/2+s-(clave&1)]=p[k++];
				r[(clave+1)/2+2*clave-2+s-(clave&1)]=p[k++];
			}
			s+=2*clave+clave/2-1;
		}
		if(s==t){f++;s=0;b=0;}
		if(k<p.size() && b){
			for(int i=0;i<clave;i++){
				int x=pedido3(clave,f-1,i,s);
				r[x]=p[k++];
			}
			s+=clave*clave;
		}
		if(s==t){f++;s=0;b=0;}
		if(k<p.size() && b){
			if(f==1){
				r[clave+s-1]=p[k++];
				r[3*clave+s-3]=p[k++];
			}
			else if(f<clave){
				r[clave-f+s]=p[k++];
				r[clave+f+s-2]=p[k++];
				r[3*clave-2-f+s]=p[k++];
			}
			else{
				r[s]=p[k++];
				r[2*clave+s-2]=p[k++];
			}
			s+=3*clave-2;
		}
		if(s==t){f++;s=0;b=0;}
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
	cout<<relleno(p,clave,cuadrados)<<endl;
	p=cifrar(p,clave,cuadrados);
	cout<<p<<endl;
	cout<<descifrar(p,clave,cuadrados)<<endl;
	return 0;
}
