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
    vector<int> OverflowBucket;
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
    bool checkFull()
    {
        if(A.size()==size)
        {
            return true;
        }
        else
        {
            return false;
        }
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
    int M;
    vector<Bucket*> Buckets;
    unordered_set<int> Elements;
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
    Directory(int gD,int C,int Q)
    {
        BucketSize = C;
        globalDepth = gD;
        M = Q;
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
        Elements.insert(n);
        int z = pow(2,globalDepth);
        int t = n%z;
        if(B[t]->A.size()==BucketSize)
        {
            if(B[t]->localDepth<globalDepth)
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
                for(auto it = B[t]->OverflowBucket.begin();it!=B[t]->OverflowBucket.end();it++)
                {
                    // cout<<*it<<" ";
                    if(*it%(2*u)==v1)
                    {
                        // cout<<"A1 ->"<<*it<<endl;
                        if(A1->A.size()==BucketSize)
                        {
                            A1->OverflowBucket.push_back(*it);
                        }
                        else
                        {
                            A1->A.push_back(*it);
                        }
                    }
                    else if(*it%(2*u)==v2)
                    {
                        // cout<<"A2 ->"<<*it<<endl;
                        if(A2->A.size()==BucketSize)
                        {
                            A1->OverflowBucket.push_back(*it);
                        }
                        else
                        {
                            A2->A.push_back(*it);
                        }
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
                int op = 0;
                    for(int i  = 0;i<Buckets.size();i++)
                    {
                        if(Buckets[i]->OverflowBucket.size()>0)
                        {
                            op++;
                        }
                    }
                    if(B[t]->A.size()==BucketSize)
                    {
                        if(op*100/z>M)
                        {
                            add(n);
                        }
                        else
                        {
                            B[t]->OverflowBucket.push_back(n);
                        }
                    }
                    else
                    {
                        B[t]->A.push_back(n);
                    }
            }
            else
            {
                B[t]->OverflowBucket.push_back(n);
                // cout<<"JUST PUSHED"<<n<<endl;
                int o = 0;
                for(int i  = 0;i<Buckets.size();i++)
                {
                    if(Buckets[i]->OverflowBucket.size()>0)
                    {
                        o++;
                    }
                }
                // CHECKING THE REQUIRED PERCENTAGE
                if(((o*100)/(z))>=M)
                {
                    //DOUBLING THE DIRECTORY
                    int earlier = globalDepth;
                    globalDepth++;
                    z = (pow(2,globalDepth));
                    for(int i = pow(2,earlier);i<pow(2,globalDepth);i++)
                    {
                        int e = pow(2,earlier);
                        B[i] = B[i%e];
                    }
                    // split of all buckets that has overflow bucket
                    //new container
                    vector<Bucket*> Container;
                    for(auto one : Buckets)
                    {
                        if(one->OverflowBucket.size()>0)
                        {
                        // SPLIT OF THAT BUCKET
                        Bucket* A1 = new Bucket(one->localDepth+1,BucketSize);
                        Bucket* A2 = new Bucket(one->localDepth+1,BucketSize);
                        int rt = pow(2,one->localDepth);
                        t = (one->OverflowBucket[0])%rt;
                        int v1 = t;
                        int v2 = pow(2,one->localDepth)+t;
                        v2 = v2%z;
                        if(v1<v2)
                        {
                            replace(Buckets.begin(),Buckets.end(),one,A1);
                        // replace(Buckets.begin(),Buckets.end(),*B[t],*A1);
                            Container.push_back(A2);
                        }
                        else
                        {
                            replace(Buckets.begin(),Buckets.end(),one,A2);
                        // replace(Buckets.begin(),Buckets.end(),*B[t],*A1);
                            Container.push_back(A1);              
                        }
                        int u = pow(2,one->localDepth);
                        noofBuckets = noofBuckets+1;
                        int r =one->localDepth;
                        for(auto it = one->A.begin();it!=one->A.end();it++)
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
                        for(auto it = one->OverflowBucket.begin();it!=one->OverflowBucket.end();it++)
                        {
                            // cout<<*it<<" ";
                            if(*it%(2*u)==v1)
                            {
                                // cout<<"A1 ->"<<*it<<endl;
                                if(A1->A.size()==BucketSize)
                                {
                                    A1->OverflowBucket.push_back(*it);
                                }
                                else
                                {
                                    A1->A.push_back(*it);
                                }
                            }
                            else if(*it%(2*u)==v2)
                            {
                                // cout<<"A2 ->"<<*it<<endl;
                                if(A2->A.size()==BucketSize)
                                {
                                    A2->OverflowBucket.push_back(*it);
                                }
                                else
                                {
                                    A2->A.push_back(*it);
                                }
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
                    }
                    for (int w = 0; w< Container.size(); w++)
                    {
                        Buckets.push_back(Container[w]);
                    }
                }
            }
        }
        else
        {
            // cout<<"BUCKET IS LESS SO PUSHED EASILY "<<endl;
            B[t]->A.push_back(n);
        }
        // z =  (pow(2,globalDepth));
        // t = n%z;
        // very imp recursive case
        // int op = 0;
        // for(int i  = 0;i<Buckets.size();i++)
        // {
        //     if(Buckets[i]->OverflowBucket.size()>0)
        //     {
        //         op++;
        //     }
        // }

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
            //     cout<<endl<<"OVERFLOW BUCKET SIZE : "<<B[i]->OverflowBucket.size()<<endl;
            //     y = B[i]->OverflowBucket.size();
            //     for(int j = 0 ; j<y;j++)
            //     {
            //         cout<<B[i]->OverflowBucket[j]<<" ";
            //     }
            //     cout<<endl;
            // }
            // // cout<<"DESIRED ORDER";
            // cout<<globalDepth<<endl<<noofBuckets<<endl;
            // for(int i = 0 ; i<Buckets.size();i++)
            // {
            //     cout<<Buckets[i]->A.size()<<" "<<Buckets[i]->localDepth<<endl;
            //     for(auto it = Buckets[i]->A.begin();it!=Buckets[i]->A.end();it++)
            //     {
            //         cout<<*it<<" ";
            //     }
            //     cout<<endl;
            // }
            // if(Buckets.size()==2)
            // {

            // }
            // int x = 0;
            // for (int i = 0; i < Buckets.size(); i++)
            // {
            //     // if(Buckets[i]->A.size()==0)
            //     // {

            //     // }else
            //     // {
            //     //     x++;
            //     // }
            // }
            cout<<globalDepth<<" "<<Buckets.size()<<endl;
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
    int globalDepth,Capacity,M;
    cin>>globalDepth>>Capacity>>M;
    Directory A(globalDepth,Capacity,M);
    int x;
    while (cin>>x)
    {
        if(x==2)
        {
            int y;
            cin>>y;
            A.add(y);
        }
        else if(x==5)
        {
            A.displayStatus();
        }
        else if(x==6)
        {
            return 0;
        }
        // else if(x==3)
        // {
        //     int y;
        //     cin>>y;
        //     if(A.find(y))
        //     {
        //         cout<<"PRESENT IN HASH"<<endl;
        //     }
        //     else
        //     {
        //         cout<<"NOT PRESENT IN HASH"<<endl;
        //     }
        // }
        // else if(x==4)
        // {
        //     int y;
        //     cin>>y;
        //     A.deleteValue(y);
        //     // cout<<y<<endl;
        // }
    }
    return 0;
}