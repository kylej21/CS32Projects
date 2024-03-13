#include "router.h"
#include<queue>
#include<vector>
#include<unordered_set>
using namespace std;

std::vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const{
    unordered_set<string> closedList;
    unordered_map<string, double> g_value;
    vector<GeoPoint> path;
    cost compareEnd(pt2);
    // priority queue not working properly. Seems openList.top() is always just the first checked neighbor
    priority_queue<GeoPoint,vector<GeoPoint>,cost> openList(compareEnd);
    unordered_set<string> openListSet;
    openList.push(pt1);
    openListSet.insert(pt1.to_string());
    g_value[pt1.to_string()] = 0;
    while(!openList.empty()){
        GeoPoint current = openList.top();
        openList.pop();
        openListSet.erase(current.to_string());
        closedList.insert(current.to_string());
        path.push_back(current); 
        if(current.to_string() == pt2.to_string()){
            return path;
        }
        vector<GeoPoint> adjacent = m_geoDB->get_connected_points(current);
        for(auto a : adjacent){
            if(closedList.find(a.to_string())!=closedList.end()){
                // if value is in CLOSED list we already checked and dont do it again
                continue;
            }
            double newG = g_value[current.to_string()]+distance_earth_miles(a,current);
            if(openListSet.find(a.to_string())!=openListSet.end()){
                
                if(newG>g_value[a.to_string()] && g_value[a.to_string()]!=0){
                    
                    continue;
                }
            }
            g_value[a.to_string()]=newG;
            openList.push(a);
            openListSet.insert(a.to_string());
           
        }
    }
    return {};
}