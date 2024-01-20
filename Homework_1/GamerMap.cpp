#include "GamerMap.h"
GamerMap::GamerMap(){
};
bool GamerMap::addGamer(std::string name){
    return m_map.insert(name,0);
}
double GamerMap::hoursSpent(std::string name) const{
    if(!m_map.contains(name)){
        return -1;
    }
    else{
        double hours = 0.0;
        m_map.get(name,hours); 
        return hours;
    }
}
bool GamerMap::play(std::string name, double hours){
    if(hours<0){
        return false;
    }
    return m_map.update(name,hours);
}
int GamerMap::numGamers() const{
    return m_map.size();
}  
void GamerMap::print() const{
    string key="";
    double value=0.0;
    for(int i=0;i<numGamers();i++){
        m_map.get(i,key,value);
        cout << key << " " << value <<endl;
    }
}
