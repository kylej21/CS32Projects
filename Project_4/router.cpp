#include "router.h"
#include<queue>
#include<vector>
#include<unordered_set>
using namespace std;

std::vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const{
    unordered_set<string> closedList;
    unordered_map<string, double> g_value;
    unordered_map<string,GeoPoint> cameFrom;
    vector<GeoPoint> path;
    cost compareEnd(pt2); // struct that will compare any points distances from end. 
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
        if(current.to_string() == pt2.to_string()){
            while (current.to_string() != pt1.to_string()) {
                path.push_back(current);
                current = cameFrom[current.to_string()];
            }
            // Add the source point
            path.push_back(pt1);
            // Reverse the path to get the correct order
            reverse(path.begin(), path.end());
            return path;
        }
        vector<GeoPoint> adjacent = m_geoDB->get_connected_points(current);
        for(auto a : adjacent){
            if(closedList.find(a.to_string())!=closedList.end()){
                // if value is in CLOSED list we already checked and dont do it again
                continue;
            }
            double newG = g_value[current.to_string()]+distance_earth_miles(current,a);
            
            if(openListSet.find(a.to_string())!=openListSet.end()){
                
                if(newG>g_value[a.to_string()] && g_value[a.to_string()]!=0){
                    
                    continue;
                }
            }
            g_value[a.to_string()]=newG;
            cameFrom[a.to_string()] = current;
            openList.push(a);
            openListSet.insert(a.to_string());
           
        }
    }
    return {};
}