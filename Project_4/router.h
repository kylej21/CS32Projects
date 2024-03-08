#include "base_classes.h"
#include "geodb.h"
#include "geotools.h"
class Router: public RouterBase
{
    public:
        Router(GeoDatabaseBase& geo_db):
            m_geoDB(&geo_db){}
        virtual ~Router() {}
        virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2);
    private:
        GeoDatabaseBase *m_geoDB;
        double dist(GeoPoint pt1, GeoPoint pt2){
            return distance_earth_km(pt1,pt2);
        }
};