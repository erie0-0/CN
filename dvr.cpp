#include<stdio.h>
#include<iostream>
using namespace std;

struct node
{
    unsigned dist[10];
    unsigned from[10];
}DVR[10];

int main(){
    int cMat[10][10];	    // cost matrix
    int nodes,ne,i,j,k;
    char ch[10];
    cout<<"Input number of nodes : ";
    cin>>nodes;
    for(i=0;i<nodes;i++){
	cout << "Vertex " << i+1 << " : ";
	cin >> ch[i];
    }

    // initialize
    for(i=0;i<nodes;i++){
	for(j=0;j<nodes;j++){
	    cMat[i][j] = 0;
            DVR[i].dist[j] = 0;
            DVR[i].from[j] = j;
	}
    }
    cout << "Number of edges : ";
    cin >> ne;
    for(i=0;i<ne;i++){

	char ch1,ch2;
        int r=0,c=0,w=0 ;
	
	cout << "Edge " << i+1 << " : " << endl;
        cout<<"\tFirst vertex" << " : ";
        cin >> ch1;
        cout<<"\tSecond vertex" << " : ";
        cin >> ch2;
        
        for(int k=0; k<ne; k++){
            if ( ch[k] == ch1 )
		r = k;
        }
        for(int k=0; k<ne; k++){
            if ( ch[k] == ch2 ) 
		c = k;
        }

        cout << "\tWeight : ";
        cin>>w;

	cMat[r][c] = w;
	cMat[c][r] = w;
	DVR[r].dist[c] = cMat[r][c];
	DVR[c].dist[r] = cMat[c][r];
	
    }

    for(i=0;i<nodes;i++){
	for(j=0;j<nodes;j++){
	    cout << cMat[i][j] << " ";
	}
	cout << endl;
    }
    //cout<<"\n Enter the cost matrix : \n" ;
    //for(i = 0; i < nodes; i++){
        //for(j = 0; j < nodes; j++){
            //cin>>cMat[i][j];
            //cMat[i][i] = 0;
            //DVR[i].dist[j] = cMat[i][j];
            //DVR[i].from[j] = j;
        //}
    //}

    for(i = 0; i < nodes; i++){ 
	for(j = i+1; j < nodes; j++){
	    for(k = 0; k < nodes; k++){
		if(DVR[i].dist[j] > cMat[i][k] + DVR[k].dist[j]){   
		    DVR[i].dist[j] = DVR[i].dist[k] + DVR[k].dist[j];
		    DVR[j].dist[i] = DVR[i].dist[j];
		    DVR[i].from[j] = k;
		    DVR[j].from[i] = k;
		}
	    }
	}
    }

    //for(i = 0; i < nodes; i++){
	//cout<<"\n\n For router: "<<i+1;
	//for(j = 0; j < nodes; j++)
	    //cout<<"\t\n node "<<j+1<<" via "<<DVR[i].from[j]+1<<" Distance "<<DVR[i].dist[j];
    //}
    char s;
    int si;
    cout << "Enter source : ";
    cin >> s;
    for(int k=0; k<ne; k++){
	if ( ch[k] == s ) 
	    si = k;
    }
    cout << "From Source [" << s << "]\nVertex  Distance  Intermidiate" << endl;
    for(i=0;i<nodes;i++){
	cout << ch[i] << "\t  " << DVR[si].dist[i] << "\t\t" << ch[DVR[si].from[i]] << endl; 
    }
    return 0;
}
