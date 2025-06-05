#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>
#include<queue>
#include<algorithm>
using namespace std;
class Graph{
    int i;
    vector<string> cities;
    unordered_map<string,int> cities_map;
    unordered_map<int,vector<pair<int,int>>> adjlist;
public:
    Graph(){
        i=0;
    }
    void add_edge(string u,string v,int w){
        if(cities_map.find(u)==cities_map.end()){
            cities_map[u]=i++;
            cities.push_back(u);
        }
        if(cities_map.find(v)==cities_map.end()){
            cities_map[v]=i++;
            cities.push_back(v);
        }
        adjlist[cities_map[u]].push_back({cities_map[v],w});
        adjlist[cities_map[v]].push_back({cities_map[u],w});
    }
    vector<string> dijkstra(string src,string dest){
        if(cities_map.find(src)==cities_map.end() || cities_map.find(dest)==cities_map.end()){
            cout<<"Invalid city name"<<endl;
            return {};
        }
        vector<vector<string>> paths(i,vector<string>({}));
        paths[cities_map[src]]={src};
        int source=cities_map[src];
        vector<int> distance(i,INT32_MAX);
        queue<int> q;
        distance[source]=0;
        q.push(source);
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(auto i:adjlist[u]){
                int v=i.first;
                int w=i.second;
                if(distance[v]>distance[u]+w){
                    distance[v]=distance[u]+w;
                    paths[v]=paths[u];
                    paths[v].push_back(cities[v]);
                    q.push(v);
                }
            }
        }
        return paths[cities_map[dest]];
    }
    void print(){
        for(auto i:adjlist){
            cout<<cities[i.first]<<" : ";
            for(auto j:i.second){
                cout<<cities[j.first]<<" "<<j.second<<", ";
            }
            cout<<endl;
        }
    }
};
int main(){
    Graph g;
    char ch='y';
    while(ch!='n'){
        string u,v;
        int w;
        cout<<"Enter the starting city of the edge : ";
        cin>>u;
        while(u.size()<1){
            cout<<"Enter a valid city name: ";
            cin>>u;
        }
        cout<<"Enter the ending city of the edge : ";
        cin>>v;
        while(v.size()<1){
            cout<<"Enter a valid city name: ";
            cin>>v;
        }
        cout<<"Enter the Distance between them : ";
        cin>>w;
        while(w<0){
            cout<<"Enter a valid Distance: ";
            cin>>w;
        }
        g.add_edge(u,v,w);
        cout<<"do you want to add more edges? (y/n): ";
        cin>>ch;
    }
    g.print();
    while(true){
        string src,dest;
        cout<<"Enter the source city: ";
        cin>>src;
        cout<<"Enter the destination city: ";
        cin>>dest;
        vector<string> path=g.dijkstra(src,dest);
        cout<<"The shortest distance between "<<src<<" and "<<dest<<" is: ";
        if(path.size()==0){
            cout<<"No path exists"<<endl;
        }else{
            int dist=path.size();
            for(int i=0;i<dist-1;i++){
                cout<<path[i]<<" -> ";
            }
            cout<<path[dist-1]<<endl;
        }
        cout<<"Do you want to find another distance? (y/n): ";
        cin>>ch;
        if(ch=='n') break;
    }
    return 0;
}


