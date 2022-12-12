#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

int main(){

    int nf,ws;
    srand(time(NULL));
    cout<<"Enter number of frames: ";
    cin>>nf;
    cout<<"Enter the Window Size : ";
    cin>>ws;
    int i=1;

    while(i<=nf){
	int x=0;
	for(int j=i;j<i+ws && j<=nf;j++){
	    cout<<"Sent Frame "<<j<<endl;
	}
	for(int j=i;j<i+ws && j<=nf;j++){
	    int flag = rand()%2;
	    if(!flag){
		cout << "\t----Case 1: Frame recieved successfully----" << endl;
		cout<<"Acknowledgment for Frame "<<j<<endl;
		x++;
	    }
	    else{
		cout << "\t----Case 2: Frame Lost----" << endl;
		cout<<"Frame "<<j<<" Not Received"<<endl;
		cout<<"Retransmitting Window"<<endl;
		break;
	    }
     }
     cout<<endl;
     i+=x;
    }
    return 0;
}
