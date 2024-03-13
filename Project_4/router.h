#ifndef ROUTER_H
#define ROUTER_H
#include "base_classes.h"
#include "geodb.h"
#include "geotools.h"
class Router: public RouterBase
{
    public:
        Router(GeoDatabaseBase& geo_db):
            m_geoDB(&geo_db){}
        virtual ~Router() {}
        virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const;
    private:
        GeoDatabaseBase *m_geoDB;
        struct cost{
            GeoPoint m_end;
            cost(const GeoPoint& end) : m_end(end){};
            bool operator()(const GeoPoint& pt1, const GeoPoint& pt2) const{
                return distance_earth_miles(pt1,m_end) >distance_earth_miles(pt2,m_end);
            }
        };
};
#endif