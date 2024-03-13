#include "geodb.h"
#include "geotools.h"
#include<string>
#include "router.h"
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
GeoPoint test1("34.0602175","-118.4464952" );
GeoPoint test2("34.0599361","-118.4469479");

cout <<"mid: " <<midpoint(test1,test2).sLatitude << " " << midpoint(test1,test2).sLongitude<< endl;
GeoPoint p5=midpoint(test1,test2);
//GeoPoint p5("-118.4467216","34.0600768");
v = g.get_connected_points(p5);
for(int i=0;i<v.size();i++){
        cout <<v[i].sLatitude << " " << v[i].sLongitude<<endl;
    }

Router r(g);
GeoPoint diddy("34.0851358", "-118.3845655");
GeoPoint sushi("34.0464796", "-118.4554219");
//cout << diddy.latitude << " " << diddy.longitude<<endl;
vector<GeoPoint> result = r.route(diddy,sushi);
cout << " start " << endl;
cout << result.empty() << endl;
for(auto a : result){
    cout << a.latitude << " " << a.longitude <<endl;
}
}