#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

class Network;

class Sender {
	string *data;
	int frames,currFrame, timer=0,ack=1,seq=1;
	Network *n;
	public:
		Sender(Network *net) {
			n = net;
			currFrame = 0;

			cout << "Enter the message to be sent: ";
			string message,sub;
			getline(cin,message);

			char c= ' ';
			int len=message.size();
			int found;
			frames=0;
			for(int i=0;i<=len;i++)
			{
				if (message[i]==' '|| message[i]=='\0') ++frames;	
			}

			data = new string[frames];

			for(int i=0;i<frames;i++)
			{
				if(i!=frames)
				{
					found=message.find(c);
					sub=message.substr(0,found);
					data[i]=sub;
					message=message.substr(found+1,len);  
				}
				else
				{
					sub=message.substr(found,len);
					data[i]=sub;
				}	 
			}
		}
		void transmit() 
		{
			cout<<"\n-------Sender---------";
			if(timer==1)
			{
				cout<<"\nTimer out";
				cout<<"\nRetransmitting frame";
				timer=0;	
			}
			else if (ack!=seq)
			{
				cout<<"\nReceived Ack : "<<ack;
				seq = !seq;
				currFrame++;
			}
			if (currFrame >= frames)
			{
				return;
			}	
			cout<<"\nFrame "<<currFrame+1;
			cout<<"\nSending Message |"<<data[currFrame]<<"| with Sequence No. "<<seq;
			
		}
		
		friend class Network;
};

class Receiver {
	string frames[10];
	int totFrames, currFrame;
	int check, ack, seq;
	Network *n;
	public:
		Receiver(Network *net) {
			n = net;
			currFrame = 0;
		}
		void process(string data) 
		{
			cout<<"\n------Receiver------";
			cout<<"\nMessage received : "<<data;
			if (frames[currFrame] == data)
			{
				//ACK was lost
				seq = !seq;
				ack = seq;
				cout<<"\nMessage Discarded  ";
			}
			else
			{
				seq = !seq;
				ack = seq;
				frames[currFrame] = data;
			}
			
			cout<<"\nSending Ack :"<<ack;
		}
		friend class Network;
};

class Network {
	private:
		string frame;
		int random,ack,seq;
		int ch=4, totalFrames;
	public:
		Sender *s;
		Receiver *r;
		Network() {
			
		}
		void start() {
			totalFrames = s->frames;
			r->totFrames = totalFrames;
			
			while (s->currFrame < totalFrames)
			{
				switch(ch)
				{
					case 0:                                                          // Ack lost
					{
						frame = s->data[s->currFrame];
						seq = s->seq;

						r->seq = seq;
						r->process(frame);
						ack = r->ack;

						cout<<"\n---------------------\nAck lost\n---------------------";
						s->timer = 1;
						ch=4;
						break;
					}
					case 1:                                                        //Frame Lost
					{  
						frame = s->data[s->currFrame];
						seq = s->seq;

						cout<<"\n---------------------\n--Frame lost-- \n---------------------";
						s->timer=1;
						ch=4;
						break;
					}
					case 2:                                                       //Frame Damage
						{      
							frame = s->data[s->currFrame];
							seq = s->seq;

							cout<<"\n---------------------\n--Frame damaged-- \n---------------------";
							s->timer=1;
							ch=4;
							break;
						}
					case 3:
						{
							frame = s->data[s->currFrame];
							seq = s->seq;

							r->seq = seq;
							r->process(frame);
							ack = r->ack;
							r->currFrame++;
							s->ack = ack;
							ch = 4;
							break;
						}	  
					case 4:                                                        //Okay
					{
							s->transmit();

							ch=rand()%4;                                         //ch=  0 ,1 ,2 ,4
						}
						
					}
			
			}
			cout<<"\n-------Sender---------";
			cout<<"\nTransmission Complete : ";
		}
		friend class Sender;
		friend class Receiver;
};

int main()
{
	Network n;
	Sender s(&n);
	Receiver r(&n);
	n.s = &s;
	n.r = &r;
	n.start();
}


