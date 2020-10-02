#include<bits/stdc++.h>
using namespace std;

#define ll long long int
#define ull unsigned long long int
#define fo(i,a,n) for(ll i=a;i<n;i++)
#define fo2(i,a,n) for(ll i=n;i>=a;i--)
#define endl "\n"
#define sp " "
#define f first
#define s second
#define pb push_back
#define buffer ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define mod 1000000007
#define lower(str) transform(str.begin(), str.end(), str.begin(), ::tolower);
#define upper(str) transform(str.begin(), str.end(), str.begin(), ::toupper);
#define init(arr,val) memset(arr,val,sizeof(arr))
#define vecl(v) vector<ll> v
#define vecs(v) vector<string> v
#define vecp(v) vector < pair <ll,ll> > v


int main(){
    int a,b,x,y;
    cin>>a>>b;
    vector<vector<int> > v;
    vector<bool> bo;
    v.assign(a,vector<int> ());
    bo.assign(a,false);
    while(b--){
        cin>>x>>y;
        v[x].pb(y);
        v[y].pb(x);
    }
    int luckiness[a];
    init(luckiness,-1);
    queue<int> q;
    q.push(0);
    bo[0] = true;
    luckiness[0] = 0;
    while(!q.empty()){
        int vis = q.front();
        q.pop();
        bo[vis] = true;
        fo(i,0,v[vis].size()){
            if(bo[v[vis][i]] == false){
                luckiness[v[vis][i]] = luckiness[vis] + 1;
                q.push(v[vis][i]);
                bo[v[vis][i]] = true;
                
            }
        }
    }
    fo(i,1,a){
        cout<< luckiness[i] <<endl;
    }
    return 0;
}
