#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <cmath>
#include <iostream>

using namespace std;

// See the explanations of these typedefs and constants in the starter for friend_suggestion
typedef vector<vector<vector<int>>> Adj;
typedef long long Len;
typedef vector<priority_queue<pair<Len, int>,vector<pair<Len,int>>,greater<pair<Len,int>>>> Queue;

const Len INF = numeric_limits<Len>::max() / 4;

class AStar {
    // See the descriptions of these fields in the starter for friend_suggestion
    int n_;
    Adj adj_;
    Adj cost_;
    vector<vector<Len>> distance_;
    vector<int> workset_;
    vector<bool> visited_;
    // Coordinates of the nodes
    std::vector<std::pair<Len,Len>> xy_;
		vector<vector<bool>> vis_;

public:
    AStar(int n, Adj adj, Adj cost, std::vector<std::pair<Len,Len>> xy)
        : n_(n), adj_(adj), cost_(cost), distance_(2, vector<Len>(n_, INF)), visited_(n), xy_(xy), vis_(2,vector<bool>(n,false))
    { workset_.reserve(n); }

    // See the description of this method in the starter for friend_suggestion
    void clear() {
			for (int i = 0; i < workset_.size(); ++i) {
					int v = workset_[i];
					distance_[0][v] = distance_[1][v] = INF;
					visited_[v] = false;
					vis_[0][v]=vis_[1][v]=false;
			}
			workset_.clear();
    }

		Len heu_f(int s, int t, int u){
			Len PI_f = sqrt( pow((xy_[t].first - xy_[u].first),2) + pow((xy_[t].second - xy_[u].second),2) );
			Len PI_r = sqrt( pow((xy_[s].first - xy_[u].first),2) + pow((xy_[s].second - xy_[u].second),2) );
			return (PI_f - PI_r)/2 ;
 
		}

    // See the description of this method in the starter for friend_suggestion
    void visit(Queue& q, int side, int v, int s, int t, Len dist, Len &bp) {
        // Implement this method yourself
				int i =0;
				for(auto u:adj_[side][v]){
					if(distance_[side][u]> (dist+cost_[side][v][i])){
							distance_[side][u] = dist+cost_[side][v][i];
							Len heu = 0;
							if(0==side){
								heu = heu_f(s,t,u);
							}else{
								heu = -heu_f(s,t,u);
							}
							Len f = distance_[side][u]+heu;
							//Key of A* - evaluate distance with heuristic
							q[side].push(make_pair(f,u));
							if(!visited_[u]){
								visited_[u]=true;
								workset_.push_back(u);
							}
							if(!vis_[side][u]){
								vis_[side][u] = true;
							}
							if(vis_[1-side][u]){
								Len f_b = distance_[1-side][u] - heu;
								if(f+f_b<bp)
									bp = f+f_b;
							}
					}
					++i;
				}
    }

    // Returns the distance from s to t in the graph
    Len query(int s, int t) {
        clear();
				if (s==t) return 0;
        Queue q(2);
        // Implement the rest of the algorithm yourself
				distance_[0][s] = 0;
				distance_[1][t] = 0;
				Len btph = INF;

				//all queues using the f = g + h function to prioritize nodes
				q[0].push(make_pair(distance_[0][s]+heu_f(s,t,s),s));
				if(!visited_[s]){
					visited_[s]=true;
					workset_.push_back(s);
				}
				if(!vis_[0][s])	vis_[0][s]=true;

				q[1].push(make_pair(distance_[1][t]-heu_f(s,t,t),t));
				if(!visited_[t]){
					visited_[t]=true;
					workset_.push_back(t);
				}
				if(!vis_[1][t]) vis_[1][t] = true;
				
				pair<Len,int> nf,nb; 

				while(!q[0].empty()||!q[1].empty()){
					//debug
					//cout<<nf.second+1<<" "<<nb.second+1<<endl;
					if(!q[0].empty()){
						nf = q[0].top();
						q[0].pop();
						visit(q,0,nf.second,s,t,distance_[0][nf.second],btph);
					}
					if(!q[1].empty()){
						nb = q[1].top();
						q[1].pop();
						visit(q,1,nb.second,s,t,distance_[1][nb.second],btph);
					}
					if(nf.first+nb.first >= btph){
						#if 0
						cout<<nf.first<<" "<<nb.first<<" "<<btph<<endl;
						cout<<nf.second+1<<" "<<nb.second+1<<endl;
						#endif
						return btph;
					}
				}
        return -1;
    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<std::pair<Len,Len>> xy(n);
    for (int i=0;i<n;++i){
        int a, b;
        scanf("%d%d", &a, &b);
        xy[i] = make_pair(a,b);
    }
    Adj adj(2, vector<vector<int>>(n));
    Adj cost(2, vector<vector<int>>(n));
    for (int i=0; i<m; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        adj[0][u-1].push_back(v-1);
        cost[0][u-1].push_back(c);
        adj[1][v-1].push_back(u-1);
        cost[1][v-1].push_back(c);
    }

    AStar astar(n, adj, cost, xy);

    int t;
    scanf("%d", &t);
    for (int i=0; i<t; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%lld\n", astar.query(u-1, v-1));
    }
}
