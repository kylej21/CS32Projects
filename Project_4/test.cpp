#include "geodb.h"
#include<string>
using namespace std;
int main() {
 GeoDatabase g;
  cout << "here"<<endl;
 g.load("mapdata.txt"); // assume this works to avoid error checking
 GeoPoint p;
 if (g.get_poi_location("Diddy Riese", p))
 cout << "The PoI is at " << p.sLatitude << ", "
 << p.sLongitude << endl;
 else
 cout << "PoI not found!\n";
 GeoPoint p2("34.0736122" ,"-118.4927669");
 vector<GeoPoint> v = g.get_connected_points(p2);
 for(int i=0;i<v.size();i++){
    cout << v[i].latitude << " " << v[i].longitude <<endl;
 }
 GeoPoint p3("34.0732851", "-118.4931016");
GeoPoint p4("34.0736122", "-118.4927669");
cout << g.get_street_name(p3, p4)<<endl; // writes "Glenmere Way"
cout << g.get_street_name(p4, p3)<<endl; 
GeoPoint hedrick("34.0737070","-118.4525981");
    v = g.get_connected_points(hedrick);
    for(int i=0;i<v.size();i++){
        cout << g.get_street_name(hedrick,v[i])<<endl;
    }
}