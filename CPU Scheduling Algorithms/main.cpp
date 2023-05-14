#include <bits/stdc++.h>
using namespace std;
void file() {
#ifndef ONLINE_JUDGE
//    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
}
/*
   artime = Arrival time,
   bt = Burst time,
   ct = Completion time,
   ta = Turn around time,
   wt = Waiting time
   */

struct st{
    int arriv,brust,ct,btt,ta,finishing_time,wt;
};

bool comp(const st &first , const st &second) {
    return first.arriv < second.arriv;
//    return first.brust < second.brust;
}
bool comp1(const st &first , const st &second) {
//    return first.arriv < second.arriv;
    return first.brust < second.brust;
}
bool comp2(const st &first , const st &second) {
    if(first.arriv != second.arriv)
         return first.arriv < second.arriv;
    return first.brust < second.brust;
}


const int n=10;
int ch,c=0,quantum_time;
st p[n];
double wt,tt;
void FCFS(){
    cout<<"FCFS"<<endl;
    sort( p , p+n , comp);
    double sum=0 ;int currTime = p[0].arriv,s=p[0].arriv;
    for(int i=0 ; i < n ; ++i){
//        cout<<p1[i].arriv <<' '<<p1[i].brust<<endl;
        if(p[i].arriv > currTime)currTime=p[i].arriv;
        sum+=abs(currTime-p[i].arriv);
        currTime+=(p[i].brust);
    }
    cout<<"averge watting = "<<sum/(float)(n)<<"m/s"<<endl;;
}
void SjFP(){
    cout<<"SjFP"<<endl;
    int i,j,pcom;

    for(i=0;i<n;i++) p[i].btt = p[i].brust;

    sort(p,p+n,comp);
    i=0;
    pcom=0;
    while(pcom < n)
    {
        for(j = 0 ; j < n ; j++)  if( p[j].arriv > i ) break;

        sort(p,p+j,comp1);

        if(j > 0)
        {
            for(j=0;j < n ; j++)
            {
                if( p[j].brust != 0)
                    break;
            }

            if(p[j].arriv>i)

            {
                i=p[j].arriv;

            }
            p[j].ct=i+1;
            p[j].brust--;
        }
        i++;
        pcom=0;
        for(j=0;j<n;j++)
        {
            if(p[j].brust==0)
                pcom++;
        }
    }

    for(i=0;i<n;i++)
    {
        tt+= p[i].ta = p[i].ct - p[i].arriv;
        wt+=p[i].ta-p[i].btt;
    }

    cout<<"Averge watting = "<<wt/(float)n<<"m/s\nAverge TrunAround = "<<tt/(float)n<<endl;
}
void SjFNP(){
    cout<<"SjFNP"<<endl;
    sort(p, p + n, comp2);
    double sum=0 ;int currTime = p[0].arriv,s=p[0].arriv;
    for(int i=0 ; i < n ; ++i){
       // cout << p[i].arriv << ' ' << p[i].brust << endl;
        if(p[i].arriv > currTime)currTime=p[i].arriv;
        sum+=abs(currTime - p[i].arriv);
        currTime+=(p[i].brust);
    }
    cout<<"Average Waiting Time: "<<sum/(float)n<<"m/s"<<endl  ;
}
void RR(){
    cout<<"RR"<<endl;
    int complete,current_time,change;

    double total_waiting_time = 0.0;
    double total_turn_around_time = 0.0;

    for(int i=0; i< n; i++)
        p[i].btt =  p[i].brust;

    complete = 0;
    current_time = 0;

    while(complete < n)
    {
        change = 0;
        for(int i=0; i< n; i++)
        {
            if(p[i].arriv <= current_time && p[i].btt > 0)
            {
                if(p[i].btt <= quantum_time)
                {
                    complete++;
                    current_time += p[i].btt;

                    p[i].finishing_time = current_time;
                    p[i].ta = p[i].finishing_time - p[i].arriv;
                    p[i].wt = p[i].ta - p[i].brust;

                    total_waiting_time += p[i].wt;
                    total_turn_around_time += p[i].ta;
                    p[i].btt = 0;
                }
                else
                {
                    current_time += quantum_time;
                    p[i].btt -= quantum_time;
                }
                change++;
            }
        }
        if(change == 0)
        {
            current_time++;
        }
    }
    cout<<fixed<<setprecision(5);//to print 5 digit after number
    cout<<"Average Waiting Time: "<<(total_waiting_time/n)<<"\n";
    cout<<"Average Turn Around Time: "<<(total_turn_around_time/n)<<"\n";
}
int main() {
    puts("Choice The Alogrithm You Want To Make Schedule:");
    puts("Choice 1:First come First served");
    puts("Choice 2:Shortest Job First NonPreemtive \"SJfnp\" Scheduler");
    puts("Choice 3:Shortest Job First Preemtive \"SJfp\" Scheduler ");
    puts("Choice 4:Round-Robin \"RR\" scheduler");
    puts("Choice 5:Exit");


    while (true) {
    ifstream InFile("Data.txt");
    while(InFile >>p[c].arriv>>p[c].brust){
        cout<<p[c].arriv<<' '<<p[c].brust<<endl;
        c++;
    }
    InFile.close();

    puts("your Choice = ");
        cin>>ch;
        if (ch == 1) FCFS();
        else if (ch == 2) SjFNP();
        else if (ch == 3) SjFP();
        else if (ch == 4) {
          cout<<"Quantum time: ";
          cin>>quantum_time;
          if(quantum_time == 0 ){
          cout<<"you enter wrong quantum num quantum num must be > 0!!\n";
               continue;
          }
          RR();
         }
        else break;
    //cout<<"Read from file arrival time and  burst time ";

    }
    return 0;
}
