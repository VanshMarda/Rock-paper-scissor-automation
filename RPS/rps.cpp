#include <bits/stdc++.h>
using namespace std;
#define int long long 

int n;
int cnt=0;
vector<pair<char,vector<int>>> ans;
vector<pair<char,vector<int>>> v;
vector<pair<pair<int,char> , pair<char,int>>> storage;

int check(int a){
    int sum=0;
    for(int i=0;i<storage.size();i++){
        if(storage[i].first.first==a){
            sum++;
        }
    }
    return sum;
}

void loop_solver(vector<pair<pair<int,char>,vector<int>>> arr,vector<pair<char,vector<int>>> arr1){
    int n1=arr.size();
    if(n1>0){
        char ch = arr[n1-1].first.second;
        for(int i=0;i<n1;i++){
            if(arr1[0].first==arr[i].first.second && arr1[0].second==arr[i].second){
                if(ch=='R'){
                    ans[ans.size()-1].second[0]=arr[i].first.first+1;
                }
                else if(ch=='P'){
                    ans[ans.size()-1].second[1]=arr[i].first.first+1;
                }
                else if(ch=='S'){
                    ans[ans.size()-1].second[2]=arr[i].first.first+1;
                }
                return ;
            }
        }
    }
    arr.push_back({{cnt,arr1[0].first},arr1[0].second});
    int curr_state;
    n1=arr.size();
    vector<int> temp1(3);
    temp1[0]=cnt+1;
    temp1[1]=cnt+1;
    temp1[2]=cnt+1;
    if(arr[n1-1].first.second=='R'){
        cnt++;
        temp1[0]=cnt+1;    
        curr_state=1;
        ans.push_back({'P',temp1});
    }
    else if(arr[n1-1].first.second=='P'){
        cnt++;
        curr_state=2;
        temp1[1]=cnt+1;
        ans.push_back({'S',temp1});
    }
    else if(arr[n1-1].first.second=='S'){
        cnt++;
        curr_state=0;
        temp1[2]=cnt+1;
        ans.push_back({'R',temp1});
    }
    vector<pair<char,vector<int>>> arr2;
    arr2.push_back(v[arr1[0].second[curr_state]-1]);
    loop_solver(arr,arr2);
}


void solve(vector<pair<char,vector<int>>> arr){
    n=arr.size();
    if(n==1){
        vector<pair<pair<int,char>,vector<int>>> arr2;
        loop_solver(arr2,arr);
        return;
    }
    //if not same then ...
    int curr_state;
    // puting every state in a different vector
    vector<int> temp1(3);
    int n1=0,n2=0,n3=0;
    for(int i=0;i<n;i++){
        if(arr[i].first=='R'){n1++;}
        else if(arr[i].first=='P'){n2++;}
        else{n3++;}
    }
    char temp2;
    int temp3;
    //identifing the node
    temp1[0]=temp1[1]=temp1[2]=0;
    //R->0 P->1 S->2
    if(n1==max(n1,max(n2,n3))){ //rock are more
        curr_state=1;
        temp2='P';
        ans.push_back({'P',temp1});
        cnt++;
    }
    else if(n2==max(n1,max(n2,n3))){ //paper are more
        curr_state=2;
        temp2='S';
        ans.push_back({'S',temp1});
        cnt++;
    }
    else if(n3==max(n1,max(n2,n3))){ //scissor are more
        curr_state=0;
        temp2='R';
        ans.push_back({'R',temp1});
        cnt++;
    }

    temp3=ans.size();

    //finding the array for rocks paper scissor
    vector<pair<char,vector<int>>> r;
    vector<pair<char,vector<int>>> p;
    vector<pair<char,vector<int>>> s;
    for(int i=0;i<n;i++){
        if(arr[i].first=='R'){
            r.push_back(v[arr[i].second[curr_state]-1]);
        }
        else if(arr[i].first=='P'){
            p.push_back(v[arr[i].second[curr_state]-1]);
        }
        else if(arr[i].first=='S'){
            s.push_back(v[arr[i].second[curr_state]-1]);
        }
    }
    int x=ans.size();
    //for rock
    if(r.size()!=0){
        int flag3=0;
        map<int,int> mp1;
        for(int i=0;i<r.size();i++){
            int flag1=0;
            for(int j=0;j<storage.size();j++){
                if(temp2=='P' && storage[j].first.second==temp2 && storage[j].second.first==r[i].first && storage[j].second.second==r[i].second[0]){
                    mp1[storage[j].first.first]++;
                    flag1=1;
                }
            }
            if(flag1==0){
                flag3=1;
                break;
            }
        }
        int flag=0;
        if(flag3!=1){
            for(auto ele : mp1){
                if(ele.second>=(r.size()) && ans[ele.first-1].second[0]!=0){
                    int y = check(ele.first);
                    if(y==r.size()){
                        flag=1;
                        ans[x-1].second[0]=ans[ele.first-1].second[0]; 
                        break;
                    }
                }
            }
        }
        if(flag!=1){
            //storing the new values in storage // cnt R S 3
            for(int i=0;i<r.size();i++){
                storage.push_back({{temp3,temp2},{r[i].first,r[i].second[0]}});
            }
            ans[x-1].second[0]=cnt+1; //due to indexing
            solve(r);
        }
    }
    else{
        ans[x-1].second[0]=x; //due to indexing
    }
    //for paper
    if(p.size()!=0){
        map<int,int> mp2;
        int flag3=0;
        for(int i=0;i<p.size();i++){
            int flag1=0;
            for(int j=0;j<storage.size();j++){
                if(temp2=='S' && storage[j].first.second==temp2 && storage[j].second.first==p[i].first && storage[j].second.second==p[i].second[1]){
                    mp2[storage[j].first.first]++;
                    flag1=1;
                }
            }
            if(flag1==0){
                flag3=1;
                break;
            }
        }
        int flag=0;
        if(flag3!=1){
            for(auto ele : mp2){
                if(ele.second>=(p.size()) && ans[ele.first-1].second[1]!=0){
                    int y = check(ele.first);
                    if(y==p.size()){
                        flag=1;
                        ans[x-1].second[1]=ans[ele.first-1].second[1]; 
                        break;
                    }
                }
            }
        }
        if(flag!=1){
            for(int i=0;i<p.size();i++){
                    storage.push_back({{temp3,temp2},{p[i].first,p[i].second[1]}});
                }
                ans[x-1].second[1]=cnt+1;
                solve(p);
        }
    }
    else{
        ans[x-1].second[1]=x;
    }
    //for scissor
    if(s.size()!=0){
        map<int,int> mp3;
        int flag3=0;
        for(int i=0;i<s.size();i++){
            int flag1=0;
            for(int j=0;j<storage.size();j++){
                if(temp2=='R' && storage[j].first.second==temp2 && storage[j].second.first==s[i].first && storage[j].second.second==s[i].second[2]){
                    mp3[storage[j].first.first]++;
                    flag1=1;
                }
            }
            if(flag1==0){
                flag3=1;
                break;
            }
        }
        int flag=0;
        if(flag3!=1){
            for(auto ele : mp3){
                if(ele.second>=(s.size()) && ans[ele.first-1].second[2]!=0){
                    int y = check(ele.first);
                    if(y==s.size()){
                        flag=1;
                        ans[x-1].second[2]=ans[ele.first-1].second[2]; 
                        break;
                    }
                }
            }
        }
        if(flag!=1){
            for(int i=0;i<s.size();i++){
                storage.push_back({{temp3,temp2},{s[i].first,s[i].second[2]}});
            }
            ans[x-1].second[2]=cnt+1;
            solve(s);
        }
    }
    else{
        ans[x-1].second[2]=x;
    }
}

signed main(){
    int t;
    cin>>t;
    vector<int> temp1(3);
    while(t!=0){
        char ch;
        int a,b,c;
        cin>>ch>>a>>b>>c;
        temp1[0]=a;
        temp1[1]=b;
        temp1[2]=c;
        v.push_back({ch,temp1});
        t--;
    }
    solve(v);
    int n1=ans.size();
    cout<<n1<<endl;
    for(int i=0;i<n1;i++){
        cout<<ans[i].first<<" "<<ans[i].second[0]<<" "<<ans[i].second[1]<<" "<<ans[i].second[2]<<endl;  
    }
}
