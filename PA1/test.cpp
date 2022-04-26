#include<bits/stdc++.h>
using namespace std;

#define pi 3.1415926535
#define endl "\n"
#define yes cout << "YES\n"
#define no cout << "NO\n"
#define ll long long
#define llu unsigned long long
#define pb push_back
#define mp make_pair
#define sz(x) (int)x.size()
#define tc int test_case; cin >> test_case; while(test_case--)
#define f(i,a,n) for(int i = a ; i < n ; i++)
#define rf(i,n,a) for(int i = n-1 ; i >= a ; i--)
#define F first
#define S second
#define all(c) (c).begin(),(c).end()
#define get(a,n) f(i,0,n) cin >> a[i];
#define show(a,n) f(i,0,n) cout << a[i] << " "; cout << endl;
#define fast ios:: sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define trace(x) cerr << '>' << #x << ':' << (x) << "\n"
#define trace2(x,y) cerr<< '>' << #x << ':' << (x) << " | " << #y << ':' << (y) << "\n"
#define trace3(a,b,c) cerr<<#a<<"="<<(a)<<", "<<#b<<"="<<(b)<<", "<<#c<<"="<<(c)<<"\n"
#define trace4(a,b,c,d) cerr<<#a<<"="<<(a)<<", "<<#b<<"="<<(b)<<", "<<#c<<"="<<(c)<<", "<<#d<<"="<<(d)<<"\n"
 
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<pii,int> ppi;
typedef vector<pii> vpi;
typedef map<int,int> mii;
typedef map<ll,ll> mll;
 
const int inf = 1e9;
const ll inf64 = 1e18;
const int mod = inf + 7;
const int N = 1e5 + 10;
 
vi adj[N];
map<int, int> vis;
vi level(N);
 
void bfs(int s)
{
    queue<int> q;
    q.push(s);
    level[s] = 0;
    vis[s] = 1;
 
    while(!q.empty())
    {
        s = q.front();
        q.pop();
 
        for(int i = 0; i < sz(adj[s]); i++)
        {
            if(!vis[adj[s][i]])
            {
                level[adj[s][i]] = level[s] + 1;
                vis[adj[s][i]] = 1;
                q.push(adj[s][i]);
            }
        }
    }
}
 
int main()
{
    fast;
    int n, m;
	cin >> n >> m;
 
	for(int i = 0;i < m; i++)
	{
		int x, y;
		cin >> x >> y;
 
		adj[x].pb(y);
		adj[y].pb(x);
	}
 
	int query;
	cin >> query;
	while(query--)
	{
        int s, d;
        cin >> s >> d;
 
        vis.clear();
        fill(all(level),0);
 
        bfs(s);
        int ans = 0;
        f(i,0,n)
            if(level[i] == d)
                ans++;
        cout << ans << endl;
	}
}