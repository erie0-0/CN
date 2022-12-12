#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

int main(){

    srand(time(NULL));
    int nf,ws;
    cout << "Enter Number of frames: ";
    cin >> nf;
    cout << "Enter window size: ";
    cin >> ws;

    int *frames = new int[nf];
    int *win = new int[ws];
    int *ack = new int[ws];
    int *fr = new int[nf]; //frames recieved..
    int *rack = new int[nf]; //recieved ack

    for(int i=0;i<nf;i++){
	frames[i] = 0;
	fr[i] = 0;
	rack[i] =0;
    }
    for(int i=0;i<ws;i++){
	win[i] = 0;
	ack[i] = 0;
    }

    int lf = rand()%nf;	    //index of lost frame taken randomly
    int la = rand()%nf;	    // index for frame whose ack will be lost
    int i=0;

    while(i<nf){
	
	cout << "\nSender's End: -------" << endl;
	for(int j=i;j<nf && j<i+ws;j++){
	    if(ack[j]==-1)
		cout << "Frame " << j << " resent.." << endl;
	    else if(ack[j]==0)
		cout << "Frame " << j << " sent.." << endl;
	}
	
	//for(int j=i;j<i+ws && j<=nf;j++){
	    //cout<<"Sent Frame "<<j<<endl;
	//}
	
	cout << "\n\t\t\tReciever's End: -------" << endl;
	for(int j=i;j<i+ws && j<nf;j++){

	    if(j!=lf){
		if(rack[j]!=1){
		    if(fr[j]>=1)
			cout << "\t\t\t---Frame " << j << " Discarded !!" << endl;
		    else
			cout<<"\t\t\t---Frame " << j << " Recieved !!"<<endl;
		    cout<<"\t\t\t---ACK for " << j << " Sent !!"<<endl;
		    ack[j] = 1;
		fr[j]++;
		}
	    }
	    else{
		if(fr[j]==0){
		    cout << "\t\t\tFrame "<< j << " Lost.." << endl;	
		    lf = rand()%nf;
		    ack[j] = -1;
		}
	    }
	}
	cout << "\nSender's End: -------" << endl;
	for(int j=i;j<i+ws && j<nf;j++){
	    if(la!=j){
		if(ack[j]==1){
		    cout << "Ack for " << j << " recieved.." << endl; 
		    rack[j] = 1;
		}
		else{
		    cout << "Ack for " << j << " not recieved.." << endl; 
		}
	    }
	    else{
		cout << "ACK for " << j << " lost !!" << endl;
		la = rand()%nf;
		ack[j] = -1;
	    }
	}
	int i2 = i;
	for(int j=0;j<ws && j<nf;j++){
	    if(ack[i2+j]==-1)
		break;
	    i++;
	}
	
    }

    return 0;
}
