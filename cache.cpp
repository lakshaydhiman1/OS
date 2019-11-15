#include <bits/stdc++.h> 
using namespace std; 
class base {
    public: 
        double hit;
        double access;
        virtual int refer(int)=0;
        void looping(){
            hit=0;
            access=0;
            int x[10000],i;
            for(i=0;i<10000;i++){
              x[i]=i%50;
              hit+=refer(x[i]);
              access++;
            }
            return;
        }
        void nocality(){
            hit=0;
            access=0;
            int x[10000],i;
            for(i=0;i<10000;i++){
              x[i]=rand()%100;
              access++;
              hit+=refer(x[i]);  
            }
            return;
        }
        void eightytwenty(){
            hit=0;
            access=0;
            int x[10000],i;
            for(i=0;i<10000;i++){
              if(i<8000){
                x[i]=rand()%20;
                access++;
                hit+=refer(x[i]);  
              }
              else{
                x[i]=20+rand()%80;
                access++;
                hit+=refer(x[i]);
              }
              return;  
            }
            return;
        }
        float hitrate(){
          float x=hit/access;
          return x;
        }
};


class fifoCache : public base { 
    list<int> dq; 
    map<int,int> m;
    int csize; 
    public: 
        fifoCache(int); 
        int refer(int); 
        void display(); 
};    

fifoCache::fifoCache(int n) 
{ 
    csize = n; 
} 

int fifoCache::refer(int x) 
{ 
    if (m[x] == 0) { 
        if (dq.size() == csize) { 
            int last = dq.back();  
            dq.pop_back(); 
            m[last] = 0;
        } 
    } 
    else
        return 1;
    dq.push_front(x); 
    m[x] = 1; 
    return 0;
} 
  
void fifoCache::display() 
{ 
  
    for (auto it = dq.begin(); it != dq.end(); it++) 
        cout << (*it) << " "; 
  
    cout << endl; 
} 

class lfucache: public base { 
    list<int> dq; 
    std::map <int,int> freq;
    int csize; 
    public: 
        lfucache(int); 
        int refer(int); 
        void display(); 
};    

lfucache::lfucache(int n) 
{ 
    csize = n; 
} 

int lfucache::refer(int x) 
{ 
    if (freq[x]==0) { 
        list<int>::iterator itr,h;
        h=dq.begin();
        if (dq.size() == csize) { 
            for (itr = dq.begin(); itr != dq.end(); ++itr) { 
                if(freq[*h] > freq[*itr]){
                  h=itr;
                }
            }
            freq[*h]=0; 
            dq.remove(*h);
        } 
        dq.push_front(x);
        freq[x]=1;
        return 0;
    } 
    else{   
        freq[x]=freq[x]+1; 
        return 1; 
    }
} 
  
void lfucache::display() 
{ 
    for (auto it = dq.begin(); it != dq.end(); it++) 
        cout << (*it)<< " "; 
  
    cout << endl; 
} 
class LRUCache : public base{ 
    // store keys of cache 
    list<int> dq; 

    // store references of key in cache 
  map<int,int> m;
    int csize; // maximum capacity of cache 

public: 
    LRUCache(int); 
    int refer(int); 
    void display(); 
}; 

// Declare the size 
LRUCache::LRUCache(int n) 
{ 
    csize = n; 
} 

// Refers key x with in the LRU cache 
int LRUCache::refer(int x) 
{  
    if (m[x] == 0) { 
        if (dq.size() == csize) { 
            int last = dq.back();  
            dq.pop_back(); 
            m[last] = 0;
        } 
    } 
    else{
        dq.remove(x);
        dq.push_front(x); 
        return 1;
    }    
    dq.push_front(x); 
    m[x] = 1; 
    return 0;
} 

// Function to display contents of cache 
void LRUCache::display() 
{ 

    // Iterate in the deque and print 
    // all the elements in it 
    for (auto it = dq.begin(); it != dq.end(); it++) 
        cout << (*it) << " "; 

    cout << endl; 
}  
class oraclecache{ 
    list<int> dq;  
    int csize; 
    public: 
        oraclecache(int); 
        float refer(int x[], int); 
        void display(); 
};    

oraclecache::oraclecache(int n) 
{ 
    csize = n; 
} 

float oraclecache::refer(int x[],int n) 
{ 
    list<int>::iterator itr,h;
    map<int,int> m;
    int i,j,t=-1,l=0;
    float hit=0,tot=0,rate;
    for(i=0;i<n;i++){
        if (m[x[i]]==0) { 
            tot++;
            if(dq.size()==csize){
                t=0;
                for(itr=dq.begin();itr!=dq.end();itr++){
                  for(j=i+1;j<n;j++){
                    if(*itr==x[j]){
                      if(j>t){
                        t=j;
                        h=itr;
                      } 
                      break;     
                    }
                  }
                }
                if(t==0){
                  m[*(dq.begin())]=0;
                  dq.remove(*(dq.begin()));
                }
                else{
                  m[*h]=0;
                  dq.remove(*h);
                }
            }
            dq.push_back(x[i]);
            m[x[i]]=1; 

        }
        else{
            tot++;
            hit++;
        }
    }
    rate= hit/tot;
    return rate;
}  
 
void oraclecache::display() 
{ 
    for (auto it = dq.begin(); it != dq.end();it++) 
        cout << (*it) << " "; 
  
    cout << endl; 
} 
class randomcache: public base { 
    list<int> dq; 
    std::map<int, int> freq;
    int csize; 
    public: 
        randomcache(int); 
        int refer(int); 
        void display(); 
};    

randomcache::randomcache(int n) 
{ 
    csize = n; 
} 

int randomcache::refer(int x) 
{ 
    if (freq[x]==0) {
        list<int>::iterator itr;
        if(dq.size()==csize){  
          int h=rand()%csize;
          itr=dq.begin();
          while(h>0){
              h--;
              itr++;
          } 
          dq.remove(*itr);
          freq[*itr]=0;
        }  
        dq.push_front(x);
        freq[x]=1;
        return 0;
    } 
    else{    
        return 1;  
    }
} 
  
void randomcache::display() 
{ 
    for (auto it = dq.begin(); it != dq.end(); it++) 
        cout << (*it) <<"  "; 
  
    cout << endl; 
} 
  
void randomcache::display() 
{ 
    for (auto it = dq.begin(); it != dq.end(); it++) 
        cout << (*it) <<"  "; 
  
    cout << endl; 
} 

int main(){
    fifoCache a(3); 
  
    a.refer(1); 
    a.display();
    a.refer(2); 
    a.display();
    a.refer(3); 
    a.display();
    a.refer(4); 
    a.display();
    a.refer(1); 
    a.display();
    a.refer(2); 
    a.display();
    a.refer(3); 
    a.display();
    a.refer(4); 
    a.display();
    a.refer(3); 
    a.display();
    a.refer(2); 
    a.display();
    a.refer(1); 
    a.display(); 
    cout<<"fifo finished"<<endl;
    lfucache b(3);
    b.refer(1); 
    b.display();
    b.refer(2); 
    b.display();
    b.refer(3); 
    b.display();
    b.refer(4); 
    b.display();
    b.refer(1); 
    b.display();
    b.refer(2); 
    b.display();
    b.refer(3); 
    b.display();
    b.refer(4); 
    b.display();
    b.refer(3); 
    b.display();
    b.refer(2); 
    b.display();
    b.refer(1); 
    b.display(); 
    cout<<"lfu finished"<<endl;
    LRUCache c(3);
    c.refer(1); 
    c.display();
    c.refer(2); 
    c.display();
    c.refer(3); 
    c.display();
    c.refer(4); 
    c.display();
    c.refer(1); 
    c.display();
    c.refer(2); 
    c.display();
    c.refer(3); 
    c.display();
    c.refer(4); 
    c.display();
    c.refer(3); 
    c.display();
    c.refer(2); 
    c.display();
    c.refer(1); 
    c.display(); 
    cout<<"Lru finished"<<endl;
    randomcache d(3);
    d.refer(1); 
    d.display();
    d.refer(2); 
    d.display();
    d.refer(3); 
    d.display();
    d.refer(4); 
    d.display();
    d.refer(1); 
    d.display();
    d.refer(2); 
    d.display();
    d.refer(3); 
    d.display();
    d.refer(4); 
    d.display();
    d.refer(3); 
    d.display();
    d.refer(2); 
    d.display();
    d.refer(1); 
    d.display();
    cout<<"random finished"<<endl;
    oraclecache ca(3); 
    int x[11];
    x[0]=1;
    x[1]=2;
    x[2]=3;
    x[3]=4;
    x[4]=1;
    x[5]=2;
    x[6]=3;
    x[7]=4;
    x[8]=3;
    x[9]=2;
    x[10]=1;
    ca.refer(x,11);
    ca.display();
    cout<<"oracle finished"<<endl;
    return 0;
}
