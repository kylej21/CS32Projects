#include "router.h"
#include<queue>
#include<list>
std::vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2){
    vector<GeoPoint> path; // path to store correct steps
    vector<GeoPoint*> open;
    vector<GeoPoint*> close;
    GeoPoint current =pt1;
    open.insert(&pt1);
    while(!open.empty()){
        int minVal= dist(*open[0],pt2) + dist(*open[0],current);
        GeoPoint * min = nullptr;
        for(int i=0;i<open.size();i++){
            if(dist(*open[i],pt2)+dist(*open[0],current)<=minVal){
                minVal = dist(*open[i],pt2)+dist(*open[0],current);
                min = open[i];
            }
        }
        close.push_back(min);

        if(min->latitude = pt2.latitude && min->longitude == pt2.longitude){
            // reached goal
            path.push_back(*min);
            return path;
        }
        current = *min;
        vector<GeoPoint> possibilities = m_geoDB->get_connected_points(current);
        for(int i=0;i<possibilities.size();i++){
            bool skipping = false;
            bool inOpen = false;
            for(int j=0;j<close.size();j++){
                if(close[j]==&possibilities[i]){
                    skipping = true;
                }
                if(open[i]==&possibilities[i]){
                    inOpen=true;
                }
            }
            if(skipping){
                continue;
            }
            if(!inOpen){
                open.push_back(&possibilities[i]);
            }
            else{
                // check if current open value is better
            }

        }

    }
    
}