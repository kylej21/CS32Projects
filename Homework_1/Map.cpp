#include<iostream>
#include "Map.h"
using namespace std;

Map::Map(){
    m_size=0;
}
bool Map::empty() const{
    if(m_size==0){
        return true;
    }
    else{
        return false;
    }
}
int Map::size() const{
    return m_size;
}
bool Map::insert(const KeyType& key, const ValueType& value){
    if(m_size==DEFAULT_MAX_ITEMS){
        return false;
    }
    for(int i=0;i<m_size;i++){
        if(Pairs[i].key == key){
            return false;
        }
    }
    KeyValuePair k;
    k.key=key;
    k.value=value;
    for(int i=0;i<m_size;i++){
        if(key<Pairs[i].key){
            for(int j=m_size-1;j>=i;j--){
                Pairs[j+1]=Pairs[j];
            }
            Pairs[i]=k;
            m_size++;
            return true;
        }
    }
    Pairs[m_size]=k;
    m_size++;
    return true;
}
bool Map::update(const KeyType& key, const ValueType& value){
    for(int i=0;i<m_size;i++){
        if(Pairs[i].key==key){
            Pairs[i].value=value;
            return true;
        }
    }
    return false;
}
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value){
    if(update(key,value)){
        return true;
    }
    else if(insert(key,value)){
        return true;
    }
    else{
        return false;
    }
}
bool Map::erase(const KeyType& key){
    for(int i=0;i<m_size;i++){
        if(Pairs[i].key==key){
            for(int j=i;j<m_size-1;j++){
                Pairs[j]=Pairs[j+1];
            }
            m_size--;
            return true;
        }
    }
    return false;
}
bool Map::contains(const KeyType& key) const{
    for(int i=0;i<m_size;i++){
        if(Pairs[i].key==key){
            return true;
        }
    }
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const{
    for(int i=0;i<m_size;i++){
        if(Pairs[i].key==key){
            value = Pairs[i].value;
            return true;
        }
    }
    return false;
}
bool Map::get(int i, KeyType& key, ValueType& value) const{
    if(i<0){
        return false;
    }
    if(i>=size()){
        return false;
    }
    key = Pairs[i].key;
    value = Pairs[i].value;
    return true;
}
void Map::swap(Map& other){
    KeyValuePair k;
    int temp=0;
    for(int i=0;i<DEFAULT_MAX_ITEMS;i++){
       k=other.Pairs[i];
       other.Pairs[i]=Pairs[i];
       Pairs[i]=k;
    }
    temp=m_size;
    m_size=other.m_size;
    other.m_size=temp;
}
void Map::dump() const{
    for(int i=0;i<m_size;i++){
        cerr << "Key " <<i << " : "<< Pairs[i].key<<endl;
        cerr << "Value " <<i << " : "<< Pairs[i].value<<endl;
    }
}


