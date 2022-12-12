#include<iostream>
#include<string>
#include<math.h>

using namespace std;

int ipToInt(string s,int &a,int &b,int &c,int &d);	// assigns xxx.yyy.zzz.aaa ip address into int a = xxx, b=yyy, c=zzz, d=aaa

char typeClass(int a);					// returns class for given address a

int intToBin(int num);					// converts integer num to binary representation

void netAdd(int a,int b,int c);				// prints network address

void broadAdd(int a,int b,int c);			// prints boradcast address

//----------------------------Main Function------------------------------------

int main(){

    string s;
    int a=0,b=0,c=0,d=0;
    int k;
    cout << "Enter IP Address: ";
    getline(cin,s);
    k = ipToInt(s,a,b,c,d);
    if(k<0 || a>255 || b>255 || c>255 ||d>255){
	cout << "\nInvalid IP address.." << endl;
	return -1;
    }

    //cout << a << "." << b << "." << c << "." << d << endl;

    cout << "Binary Notion: " ;
    cout << intToBin(a) << "." << intToBin(b) << "." << intToBin(c) << "." << intToBin(d) << endl; 

    cout << "\nCLASS: " << typeClass(a) << endl;

    cout << "\nNetwork Address: " ;
    netAdd(a,b,c);

    cout << "\nBroadCast Address: " ;
    broadAdd(a,b,c);
}

//-------------------------------------FUNCTION DEFINATIONS------------------------------

int ipToInt(string s,int &a,int &b,int &c,int &d){	// assigns xxx.yyy.zzz.aaa ip address into int a = xxx, b=yyy, c=zzz, d=aaa
    int count=0;
    for(int i=0;i<s.length();i++){
	if(s[i]=='-')
	    return -1;
	if(s[i]=='.'){
	    count++;
	    continue;
	}

	else if(s[i]>='0' && s[i]<='9'){
	    int num=0;
	    while(s[i]>='0' && s[i]<='9'){
		num = num*10 + (int)(s[i]-'0');
		i++;
	    }
	    i--;
	    switch (count){
		case 0 : a = num;
			 break;
		case 1 : b = num;
			 break;
		case 2 : c = num;
			 break;
		case 3 : d = num;
			 break;
	    }
	}
   }
    return 1;
}

char typeClass(int a){
    if(a>=0 && a<=127)
	return 'A';
    else if(a>=128 && a<=191)
	return 'B';
    else if(a>=192 && a<=223)
	return 'C';
    else if(a>=224 && a<=239)
	return 'D';
    else if(a>=240 && a<=255)
	return 'E';
    return '0';
}

int intToBin(int num){
    int b[8];
    int c=0,bin=0;
    for(int i=num;i>0;i=i/2){
	b[c] = i%2;
	c++;
    }
    c--;
    for(int i=0,j=c;i<=c && j>=0;i++,j--){
	bin = bin*10 + b[j];
    }
    return bin;
}

void netAdd(int a,int b,int c){
    char ch = typeClass(a);
    if(ch=='A'){
	cout << a << ".0.0.0" << endl;
    }
    else if(ch=='B'){
	cout << a << "." << b << ".0.0" << endl;
    }
    else if(ch=='C'){
	cout << a << "." << b << "." << c << ".0"<< endl;
    }
    else{
	cout << "Not defined." << endl;
    }
}

void broadAdd(int a,int b,int c){
    char ch = typeClass(a);

    if(ch=='A'){
	cout << a << ".255.255.255" << endl;
    }
    else if(ch=='B'){
	cout << a << "." << b << ".255.255"<< endl;
    }
    else if(ch=='C'){
	cout << a << "." << b << "." << c << ".255"<< endl;
    }
    else{
	cout << "Not defined." << endl;
    }

}

