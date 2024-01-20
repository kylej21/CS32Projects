#include "GamerMap.h"
#include <iostream>
#include <cassert>
using namespace std;
int main(){
    GamerMap gm;
    gm.addGamer("Ale");
    assert(gm.numGamers()==1);
    gm.addGamer("Ale");
    gm.addGamer("Kyle");
    assert(gm.numGamers()==2);
    assert(gm.hoursSpent("Ale")==0);
    assert(gm.hoursSpent("Diego")==-1);
    assert(gm.play("Ale",10));
    assert(gm.hoursSpent("Ale")==10);
    assert(gm.play("Diego",5)==false);
    assert(gm.play("Kyle",-2)==false);
    gm.print();

};