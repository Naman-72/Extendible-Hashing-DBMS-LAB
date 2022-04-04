#include <bits/stdc++.h>
typedef long long int ll;
using namespace std;
void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
class Bucket
{
private:
    
public:
    int size;
    vector<int> A;
    int localDepth;
    Bucket()
    {
    }
    Bucket(int a,int b)
    {
        localDepth = a;
        size = b;
    }
};
class Directory
{
private:
    
public:
    map<int,Bucket*> B;
    int globalDepth;
    int BucketSize;
    int noofBuckets;
    vector<Bucket*> Buckets;
    Directory(int a)
    {
        BucketSize = a;
        globalDepth = 1;
        Bucket* X = new Bucket(1,BucketSize);
        Buckets.push_back(X);
        Bucket* Y = new Bucket(1,BucketSize);
        Buckets.push_back(Y);
        noofBuckets = 2;
        B[0] = X;
        B[1] = Y;
    }
    Directory(int gD,int C)
    {
        BucketSize = C;
        globalDepth = gD;
        noofBuckets= pow(2,gD);
        for(int i = 0 ; i< noofBuckets;i++)
        {
            Bucket* X = new Bucket(gD,C);
            Buckets.push_back(X);
            B[i] = X;
        }
    }
    bool add(int n)
    {
        int z = (pow(2,globalDepth));
        int t = n%z;
        //search
        for(auto it = B[t]->A.begin();it!=B[t]->A.end();it++)
        {
            if(n==*it)
            {
                cout<<"ALREADY PRESENT"<<endl;
                return false;
            }
        }
        if(B[t]->A.size()==BucketSize)
        {
            // DOUBLING NO OF BUCKETS
            if(B[t]->localDepth==globalDepth)
            {
                int earlier = globalDepth;
                globalDepth++;
                for(int i = pow(2,earlier);i<pow(2,globalDepth);i++)
                {
                    int e = pow(2,earlier);
                    B[i] = B[i%e];
                }
                // SPLIT OF THAT BUCKET
                Bucket* A1 = new Bucket(B[t]->localDepth+1,BucketSize);
                Bucket* A2 = new Bucket(B[t]->localDepth+1,BucketSize);
                int v1 = t;
                int v2 = pow(2,B[t]->localDepth)+t;
                z = (pow(2,globalDepth));
                v2 = v2%z;
                if(v1<v2)
                {
                    replace(Buckets.begin(),Buckets.end(),B[t],A1);
                // replace(Buckets.begin(),Buckets.end(),*B[t],*A1);
                    Buckets.push_back(A2);
                }
                else
                {
                    replace(Buckets.begin(),Buckets.end(),B[t],A2);
                // replace(Buckets.begin(),Buckets.end(),*B[t],*A1);
                    Buckets.push_back(A1);              
                }
                int u = pow(2,B[t]->localDepth);
                noofBuckets = noofBuckets+1;
                int r =B[t]->localDepth;
                for(auto it = B[t]->A.begin();it!=B[t]->A.end();it++)
                {
                    if(*it%(2*u)==v1)
                    {
                        // cout<<"A";
                        A1->A.push_back(*it);
                    }
                    else if(*it%(2*u)==v2)
                    {
                        // cout<<"B";
                        A2->A.push_back(*it);
                    }
                }
                for(int i = 0 ;i<pow(2,globalDepth);i++)
                {
                    if(i%(2*u)==v1)
                    {
                        B[i] = A1;
                    }
                    else if(i%(2*u)==v2)
                    {
                        B[i] = A2;
                    }
                }
            }
            else if(B[t]->localDepth<globalDepth)
            {
                // SPLIT OF THAT BUCKET
                Bucket* A1 = new Bucket(B[t]->localDepth+1,BucketSize);
                Bucket* A2 = new Bucket(B[t]->localDepth+1,BucketSize);
                int v1 = t;
                int v2 = ((pow(2,B[t]->localDepth)+t));
                z = (pow(2,globalDepth));
                v2 = v2%z;
                if(v1<v2)
                {
                replace(Buckets.begin(),Buckets.end(),B[t],A1);
                // replace(Buckets.begin(),Buckets.end(),*B[t],*A1);
                Buckets.push_back(A2);
                }
                else
                {
                replace(Buckets.begin(),Buckets.end(),B[t],A2);
                // replace(Buckets.begin(),Buckets.end(),*B[t],*A1);
                Buckets.push_back(A1);              
                }
                int u = pow(2,B[t]->localDepth);
                noofBuckets = noofBuckets+1;
                int r =B[t]->localDepth;
                // cout<<"EARLY ARRAY \n";
                for(auto it = B[t]->A.begin();it!=B[t]->A.end();it++)
                {
                    // cout<<*it<<" ";
                    if(*it%(2*u)==v1)
                    {
                        // cout<<"A1 ->"<<*it<<endl;
                        A1->A.push_back(*it);
                    }
                    else if(*it%(2*u)==v2)
                    {
                        // cout<<"A2 ->"<<*it<<endl;
                        // cout<<"B";
                        A2->A.push_back(*it);
                    }
                }
                // cout<<endl;

                // CHECK FOR A PARTICULAR TESTCASE
                // if(n==60)
                // {
                //     cout<<v2<<endl;
                //     cout<<"EARLY ARRAY \n";
                //     for(auto it = B[t]->A.begin();it!=B[t]->A.end();it++)
                //     {
                //         cout<<*it<<" ";
                //     }
                //     cout<<endl;
                //     cout<<t<<endl;
                //     cout<<"A1 "<<v1<<endl;
                //     for (auto it = A1->A.begin(); it != A1->A.end(); it++)
                //     {
                //         cout<<*it<<" ";
                //     }
                //     cout<<endl;
                //     cout<<"A2 "<<v2<<endl;
                //     for (auto it = A2->A.begin(); it != A2->A.end(); it++)
                //     {
                //         cout<<*it<<" ";
                //     }
                //     cout<<endl;
                // }


                //JUST FOR DEBUGGING
                    // cout<<"A1"<<endl;
                    // for(int i = 0 ; i<A1->A.size();i++)
                    // {
                    //     cout<<A1->A[i]<<" ";
                    // }
                    // cout<<"A2"<<endl;
                    // for(int i = 0 ; i<A2->A.size();i++)
                    // {
                    //     cout<<A2->A[i]<<" ";
                    // }
                // SPLITTED BUCKETS 
                // ALLOT 
                
                for(int i = 0 ;i<pow(2,globalDepth);i++)
                {
                    if(i%(2*u)==v1)
                    {
                        B[i] = A1;
                    }
                    else if(i%(2*u)==v2)
                    {
                        B[i] = A2;
                    }
                }
            }
        }
        z =  (pow(2,globalDepth));
        t = n%z;
        // very imp recursive case
        if(B[t]->A.size()==BucketSize)
        {
            add(n);
        }
        else
        {
            B[t]->A.push_back(n);
        }
        return true;
    }
    void displayStatus()
    {
        // cout<<endl<<"Global Depth -> "<<globalDepth<<" "<<"No of Buckets -> "<<noofBuckets<<endl;
            // for(int i = 0;i< pow(2,globalDepth);i++)
            // {
            //     cout<<"Hashing at "<<i<<" "<<" LocalDepth : "<<B[i]->localDepth<<endl;
            //     int y = B[i]->A.size();
            //     for(int j = 0 ; j<y;j++)
            //     {
            //         cout<<B[i]->A[j]<<" ";
            //     }
            //     cout<<endl;
            // }
            // // cout<<"DESIRED ORDER";
            cout<<globalDepth<<endl<<noofBuckets<<endl;
            for(int i = 0 ; i<Buckets.size();i++)
            {
                cout<<Buckets[i]->A.size()<<" "<<Buckets[i]->localDepth<<endl;
                // for(auto it = Buckets[i]->A.begin();it!=Buckets[i]->A.end();it++)
                // {
                //     cout<<*it<<" ";
                // }
                // cout<<endl;
            }
    }
    bool find(int n)
    {
        int z = (pow(2,globalDepth));
        int t = n%z;
        //search
        for(auto it = B[t]->A.begin();it!=B[t]->A.end();it++)
        {
            if(n==*it)
            {
                return true;
            }
        }
        return false;
    }
    bool deleteValue(int n)
    {
        if(!find(n))
        {
            cout<<"NOT PRESENT "<<n<<" SO CAN'T BE DELETED"<<endl;
        }
        else
        {
            int z = (pow(2,globalDepth));
            int t = n%z;
            //search
            for(auto it = B[t]->A.begin();it!=B[t]->A.end();it++)
            {
                if(n==*it)
                {
                    cout<<"DELETED "<<n<<endl;
                    // cout<<*it<<endl;
                    B[t]->A.erase(it);
                    break;
                    // BREAK IS NEEDED VERY MUCH BECAUSE WE ARE CHANGING SIZE OF BUCKET
                }
            }
            // for(int i = 0;i<B[t]->A.size();i++)
            // {
            //     if(n==B[t]->A[i])
            //     {
            //         B[t]->A.erase(B[t]->A.begin()+i);
            //         break;
            //     }
            // }
            return true;
        }
        return true;
    }
};

int main()
{
    int globalDepth,Capacity;
    cin>>globalDepth>>Capacity;
    Directory A(globalDepth,Capacity);
    int x;
    while (cin>>x)
    {
        if(x==2)
        {
            int y;
            cin>>y;
            A.add(y);
        }
        else if(x==3)
        {
            int y;
            cin>>y;
            if(A.find(y))
            {
                cout<<"PRESENT IN HASH"<<endl;
            }
            else
            {
                cout<<"NOT PRESENT IN HASH"<<endl;
            }
        }
        else if(x==4)
        {
            int y;
            cin>>y;
            A.deleteValue(y);
            // cout<<y<<endl;
        }
        else if(x==5)
        {
            A.displayStatus();
        }
        else if(x==6)
        {
            return 0;
        }
        else
        {
            cout<<"SOME MISTAKE U HAVE DONE IN INPUT"<<endl;
        }
    }
    return 0;
}