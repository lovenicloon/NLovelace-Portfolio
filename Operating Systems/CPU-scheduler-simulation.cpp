//Nicolas Lovelace
//OPERATING SYSTEMS PROJECT 4
//11/20/22
//CPU Scheduler Simulation program - run simulations of processes through various scheduling algorithms.

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int x;
ofstream file;

struct process{
  int ID;
  int time;
  int pri;
};

process* getProcesses(){ //used to create each group of processes (size 10)
  process *temp = new process[5];
  for(int i=0; i<5; i++){
    temp[i].ID = i;
    temp[i].time = (int)rand()%20 + 1; //randomizing cpu time
    temp[i].pri = i+1;
  }
  for(int i=0; i<5; i++){ //switching priority numbers around to make them more randomized without repeating
    int o = (int)rand()%5;
    int t = temp[i].pri;
    temp[i].pri = temp[o].pri;
    temp[o].pri = t;
  }
  return temp;
}

void FCFS(process *b, double &FCFSawt, double &FCFSatt){ //first come first serve
  double awt = 0;
  double att = 0;
  for(int i=0; i<5; i++){
    att+=b[i].time;
    if(i!=0)
    for(int o=i-1; o>=0; o--){ //add up the length of all the ones completed before it started
      awt+=b[o].time;
      att+=b[o].time;
    }
  }
  FCFSawt+=awt; //adding to the total for the algorithm
  FCFSatt+=att;
  awt/=5;
  att/=5;
  cout << "FCFS: AWT " << awt << " ATT " << att << "\n";
  file.open("output.txt", fstream::app);
  file << "FCFS: AWT " << awt << " ATT " << att << "\n";
  file.close();
}

void SJF(process *b, double &SJFawt, double &SJFatt){ //shortest job first
  double awt = 0;
  double att = 0;
  process *d = new process[5];

  for(int i=0; i<5; i++){ //went ahead and made a copy of the process array
    d[i].ID = b[i].ID;
    d[i].time = b[i].time;
    d[i].pri = b[i].pri;
  }
  
  for(int i = 0; i<5; i++) { //move things around based on size
    for(int j = i+1; j<5; j++)
    {
      if(d[j].time < d[i].time) {
         process temp = d[i];
         d[i] = d[j];
         d[j] = temp;
      }
    }
  }

  /*for(int i=0; i<5; i++){
    cout << endl;
    cout << d[i].ID << " "<< d[i].time << " "<< d[i].pri;
  }*/
  
  for(int i=0; i<5; i++){ //this part is exactly the same as the FCFS
    att+=d[i].time;
    if(i!=0)
    for(int o=i-1; o>=0; o--){
      awt+=d[o].time;
      att+=d[o].time;
    }
  }
  delete d; //freeing up space
  SJFawt+=awt; //adding to the total for the algorithm
  SJFatt+=att;
  awt/=5;
  att/=5;
  cout << "SJF: AWT " << awt << " ATT " << att << "\n";
  file.open("output.txt", fstream::app);
  file << "SJF: AWT " << awt << " ATT " << att << "\n";
  file.close();
}

void PRIO(process *b, double &PRIOawt, double &PRIOatt){ //priority
  double awt = 0;
  double att = 0;
  process *d = new process[5];

  for(int i=0; i<5; i++){ //creating a copy of processes
    d[i].ID = b[i].ID;
    d[i].time = b[i].time;
    d[i].pri = b[i].pri;
  }
  
  for(int i = 0; i<5; i++) { //sorting by priority
    for(int j = i+1; j<5; j++)
    {
      if(d[j].pri < d[i].pri) {
         process temp = d[i];
         d[i] = d[j];
         d[j] = temp;
      }
    }
  }

  /*for(int i=0; i<5; i++){
    cout << endl;
    cout << d[i].ID << " "<< d[i].time << " "<< d[i].pri;
  }*/
  
  for(int i=0; i<5; i++){ //counting the same as FCFS
    att+=d[i].time;
    if(i!=0)
    for(int o=i-1; o>=0; o--){
      awt+=d[o].time;
      att+=d[o].time;
    }
  }
  delete d;
  PRIOawt+=awt; //adding to overall time for algorithm
  PRIOatt+=att;
  awt/=5;
  att/=5;
  cout << "PRIO: AWT " << awt << " ATT " << att << "\n";
  file.open("output.txt", fstream::app);
  file << "PRIO: AWT " << awt << " ATT " << att << "\n";
  file.close();
}

void RR(process *b, double &RRawt, double &RRatt, int q){ //round robin
  double awt = 0;
  double att = 0;
  process *d = new process[5];
  int wait[] = {0, 0, 0, 0, 0}; //wait array for saving wait times per process

  for(int i=0; i<5; i++){ //making a copy
    d[i].ID = b[i].ID;
    d[i].time = b[i].time;
    d[i].pri = b[i].pri;
    att+=b[i].time; //adding these here since the times get messed with in my algorithm
  }
  while(1){
    bool done = true;
    for(int i=0; i<5; i++){
      if(d[i].time > 0){ //if process is not finished, continue
        done = false;
        if(d[i].time <= q){ //if process is going to be finished this run
            for(int o=i+1; o<i+5; o++){
              if(d[o%5].time > 0)
                wait[o%5]+=d[i].time; //adding the wait of this process to every other process that is still alive
            }
            d[i].time = 0; //sets time to 0
          
        }
        else{ //if process has more time after this run
          d[i].time-=q; //subtracting cpu time used
            for(int o=i+1; o<i+5; o++){
              if(d[o%5].time > 0)
                wait[o%5]+=q; //adding wait of this process to every other process that is still alive
            }
        }
      }
      //cout << i << " " << d[i].time << " wait " << wait[i] << endl;
    }
    if(done) break;
  }

  for(int i=0; i<5; i++){
    awt+=wait[i]; //collecting the wait times from the wait array
    att+=wait[i];
  }
  
  delete d;
  RRawt+=awt; //adding to overall averages
  RRatt+=att;
  awt/=5;
  att/=5;
  cout << "RR " << q << ": AWT " << awt << " ATT " << att << "\n";
  file.open("output.txt", fstream::app);
  file << "RR " << q << ": AWT " << awt << " ATT " << att << "\n";
  file.close();
}

int main() {
  double FCFSawt = 0;
  double FCFSatt = 0;

  double SJFawt = 0;
  double SJFatt = 0;

  double PRIOawt = 0;
  double PRIOatt = 0;

  double RR4awt = 0;
  double RR4att = 0;

  double RR8awt = 0;
  double RR8att = 0;
  
  for(x=0; x<100; x++){
    process *p = getProcesses();
    
    /*for(int i=0; i<5; i++){
      cout << p[i].ID << ", " << p[i].time << ", " << p[i].pri << endl;
    }*/

    file.open("output.txt", fstream::app);
    file << "Run " << x+1 << endl;
    file.close();

    cout << "Run " << x+1 << endl; //running all the alg's
    FCFS(p, FCFSawt, FCFSatt);
    SJF(p, SJFawt, SJFatt);
    PRIO(p, PRIOawt, PRIOatt);
    RR(p, RR4awt, RR4att, 4);
    RR(p, RR8awt, RR8att, 8);
  }
  
  FCFSawt/= 500; //averaging all the overalls
  FCFSatt/= 500;

  SJFawt/= 500;
  SJFatt/= 500;

  PRIOawt/= 500;
  PRIOatt/= 500;

  RR4awt/= 500;
  RR4att/= 500;

  RR8awt/= 500;
  RR8att/= 500;

  file.open("output.txt", fstream::app);
  file << "TOTAL FCFS: AWT " << FCFSawt << " ATT " << FCFSatt << "\n";
  file << "TOTAL SJF: AWT " << SJFawt << " ATT " << SJFatt << "\n";
  file << "TOTAL PRIO: AWT " << PRIOawt << " ATT " << PRIOatt << "\n";
  file << "TOTAL RR 4: AWT " << RR4awt << " ATT " << RR4att << "\n";
  file << "TOTAL RR 8: AWT " << RR8awt << " ATT " << RR8att << "\n";
  file.close(); //finishing up the file output
  
  cout << "TOTAL FCFS: AWT " << FCFSawt << " ATT " << FCFSatt << "\n";
  cout << "TOTAL SJF: AWT " << SJFawt << " ATT " << SJFatt << "\n";
  cout << "TOTAL PRIO: AWT " << PRIOawt << " ATT " << PRIOatt << "\n";
  cout << "TOTAL RR 4: AWT " << RR4awt << " ATT " << RR4att << "\n";
  cout << "TOTAL RR 8: AWT " << RR8awt << " ATT " << RR8att << "\n";
}
