#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct{
	char name[10];
	int arrtime;
	int worktime;
}DataType;

typedef struct node{
	DataType data;
	struct node *next;
}ListNode;

typedef ListNode *LinkList;
LinkList head;

void create_insert_LinkList(int m)；
void pcb_LinkList(int n)

int main()
{
	cout<<"进程调度算法模拟实验"<<endl;
    cout<<endl;
   	int m;
	cout<<"The number of processes:";
	cin>>m;	
	cout<<""<<endl;
    create_insert_LinkList(m);    
	pcb_LinkList(m);
	cout<<"运行结束"<<endl;
	return 0;
}


void create_insert_LinkList(int m)
{	
	ListNode *p,*p1,*p2;
	p=(ListNode*)malloc(sizeof(ListNode));
	head=p;
	p->next=NULL;
	while(m>0)
	{
		p=(ListNode*)malloc(sizeof(ListNode));
		cout<<"Process-Name:";
      	cin>>p->data.name;
	    	cout<<"Arriving-Time:";
    		cin>>p->data.arrtime;
    		cout<<"Running-Time:";
    		cin>>p->data.worktime;
        	cout<<"-------------------"<<endl;
		p->next=NULL;
        	p1=head;
		p2=p1->next;
		while(p2!=NULL&&p2->data.arrtime<p->data.arrtime)
		{
			p1=p2;
			p2=p2->next;
		}
		p1->next=p;
		p->next=p2;
		flag1=flag1-1;
	}
}

void pcb_LinkList(int n)
{   
	LinkList H;
	ListNode *rear,*p,*q;
	int RR,rr,time,m,n;
	p=(ListNode*)malloc(sizeof(ListNode));
	p=NULL;
	H=p;
	RR=1;       
	cout<<"-------------------------"<<endl;
	rr=RR;
	H=head->next;
    	head->next=head->next->next;
	rear=H;
    	rear->next=NULL;
	time=H->data.arrtime;
	while(n!=0)
	{
		n=0;
	    	while(rr!=0)
			{
			    rr=rr-1;
			    time=time+1;
		     	if(head->next!=NULL)
				{
					if(head->next->data.arrtime<=time)
					{
						if(H==NULL)
						{	
							H=head->next;
	                        		head->next=head->next->next;
                        			rear=H;
            	            		rear->next=NULL;
						}
						else
						{
							rear->next=head->next;   
	                    			head->next=head->next->next;
	                    			rear=rear->next;
	                    			rear->next=NULL;
						}
					}
				}
		  	   if(H!=NULL)
			   {
				   H->data.worktime=H->data.worktime-1;
				   m=1;
				   n=n+1;
				   if(H->data.worktime==0)
				   {
					cout<<"在第"<<time-n<<"s"<<endl;
                    		cout<<"进程"<<H->data.name<<" 运行"<<n<<"s"<<"  状态：C  "<<"完成时间："<<time<<endl;
					cout<<endl;
					H=H->next;
					flag2=flag2-1;
					m=0;
                    n=0;
				   }
			   }
			}
			if(m==1)
			{
				cout<<"在第"<<time-n<<"s"<<endl;
				cout<<"进程"<<H->data.name<<" 运行"<<n<<"s"<<"  状态：R  "<<endl;
				cout<<endl;
			}
			if(H==NULL)
			{
		    	if(head->next!=NULL)time=head->next->data.arrtime;
			}
			else
			{
				if(H->next!=NULL&&m==1&&n==RR)
				{
					q=H;
					H=H->next;
					rear->next=q;
					rear=rear->next;
					rear->next=NULL;
				}
			}
			rr=RR;
	}
}
