#include "Map.h"
#include<iostream>
#include<cassert>
using namespace std;
int main(){
    Map m1;
    assert(m1.empty()==true);
    assert(m1.insert("Kyle",19)==true);
    assert(m1.insert("Kyle",15)==false);
    assert(m1.insert("Ale",15)==true);
    assert(m1.insert("Avi",20)==true);
    assert(m1.contains("Kyle")==true);
    assert(m1.contains("Antony")==false);
    assert(m1.size()==3);
    assert(m1.empty()==false);
    assert(m1.update("Kyle",21)==true);
    ValueType v;
    KeyType k ="Kyle";
    assert(m1.get(k,v)==true);
    assert(v==21);
    k="Diego";
    assert(m1.get(k,v)==false);
    assert(k=="Diego"&&v==21);
    assert(m1.update("Diego",10)==false);
    assert(m1.insertOrUpdate("Ale",100)==true);
    assert(m1.insertOrUpdate("smallberg",0)==true);
    assert(m1.insert("Carey",50)==true);
    assert(m1.erase("Carey")==true);
    assert(m1.contains("Carey")==false);
    assert(m1.get(0,k,v)==true);
    assert(k=="Ale"&& v==100);
    assert(m1.get(100,k,v)==false);
    assert(k=="Ale"&&v==100);
    assert(m1.get(3,k,v)==true);
    assert(k=="smallberg" && v==0);
    Map m2;
    m2.insert("aaa",10);
    m2.insert("bbb",5);
    m2.insert("ccc",12);
    Map m3;
    m3.insert("ddd",15);
    m3.insert("ccc",14);
    m3.swap(m2);
    assert(m3.contains("aaa")&& m3.contains("bbb")&&m3.contains("ccc")&&m3.size()==3);
    assert(m2.contains("ccc")&& m2.contains("ddd")&&m2.size()==2);
    k="ccc";
    assert(m2.get("ccc",v)==true);
    assert(v==14);
    assert(m3.get("ccc",v)==true);
    assert(v==12);
    Map m4;
    m4.insert("1",1);
    m4.insert("2",2);
    m4.insert("3",3);
    // ask about swapping on itself
    //m4.swap(m4);
    Map m5;
    Map m6;
    m5.insert("5",5);
    m5.insert("1",5);
    m5.insert("3",3);
    assert(merge(m4,m5,m6)==false);
    assert(m6.contains("1")==false&&m6.contains("2")==true&&m6.contains("3")==true&&m6.contains("5")==true);
    Map m7;
    m7.insert("4",4);
    Map m8;
    m8.insert("5",5);
    Map m9;
    assert(merge(m7,m8,m9)==true);
    Map m10;
    Map m11;
    m10.insert("1",1);
    m10.insert("2",2);
    m10.insert("3",3);
    m11.insert("5",5);
    m11.insert("1",5);
    m11.insert("3",3);
    Map m12;
    m12.insert("test",15);
    assert(merge(m10,m11,m12)==false);
    assert(m12.contains("test")==false&&m12.size()==3);
    Map m13;
    Map m14;
    m13.insert("Fred",123);
    m13.insert("Ethel",456);
    m13.insert("Lucy",456);
    reassign(m13,m14);
    k="Fred";
    assert(m14.get(k,v)==true);
    assert(v==456);   
    k="Ethel";
    assert(m14.get(k,v)==true);
    assert(v==123||v==456); 
    ValueType v2;
    k="Lucy";
    assert(m14.get(k,v2)==true);
    assert(v2==123||v2==456&&v!=v2); 
    Map m15;
    m15.insert("Kyle",123);
    m15.insert("Ale",456);
    m15.insert("Avi",456);
    reassign(m15,m15);
    k="Kyle";
    assert(m15.get(k,v)==true);
    assert(v==456);   
    k="Ale";
    assert(m15.get(k,v)==true);
    assert(v==123||v==456); 
    k="Avi";
    assert(m15.get(k,v2)==true);
    assert(v2==123||v2==456&&v!=v2); 
    cerr<<"Passed all test"<<endl;
    }