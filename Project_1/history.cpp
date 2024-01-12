#include <iostream>
#include "history.h"
#include "globals.h"
using namespace std;

History::History(int nRows, int nCols)
 : m_rows(nRows), m_cols(nCols)
{
    for(int i=0;i<MAXROWS;i++){
        for(int j=0;j<MAXCOLS;j++){
            landed[i][j]=-1;
        }
    }
    for(int i=0;i<nRows;i++){
        for(int j=0;j<nCols;j++){
            landed[i][j]=0;
        }
    }
   
}
bool History::record(int r, int c){
    if(r<1 || c<1){
        return false;
    }
    if(r>m_rows || c>m_cols){
        return false;
    }
    landed[r-1][c-1]+=1;
    return true;
}
void History::display() const{
    clearScreen();
    for(int i=0; i<m_rows;i++){
        for(int j=0;j<m_cols;j++){
            cout << landed[i][j];
        }
        cout << endl;
    }
}