#include <iostream>
#include<stack>
using namespace std;
class Coord
{
  public:
    Coord(int r, int c) : m_r(r), m_c(c) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
  private:
    int m_r;
    int m_c;
};
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    stack<Coord> coordStack;
    Coord start(sr,sc);
    coordStack.push(start);
    //S meaning start
    maze[sr][sc]='S';
    /*for(int i=0;i<nRows;i++){
        for(int j=0;j<nCols;j++){
            cout << maze[i][j];
        }
        cout <<endl;
    } */
    // initialize focus with an invalid point
    Coord focus(-1,-1);
    while(!coordStack.empty()){
        focus = coordStack.top();
        cout << focus.r() << " " <<focus.c() << endl;
        coordStack.pop();
        if(focus.r()==er&&focus.c()==ec){
            return true;
        }
        else{
            //North
            if(focus.r()-1>=0){

                if(maze[focus.r()-1][focus.c()]=='.'){
                    Coord temp(focus.r()-1,focus.c());
                    coordStack.push(temp);
                    maze[focus.r()-1][focus.c()]='V';
                }
            }
            //West
            if(focus.c()-1>=0){
                if(maze[focus.r()][focus.c()-1]=='.'){
                    Coord temp(focus.r(),focus.c()-1);
                    coordStack.push(temp);
                    maze[focus.r()][focus.c()-1]='V';
                }
            //South
            }if(focus.r()+1<nRows){
                if(maze[focus.r()+1][focus.c()]=='.'){
                    Coord temp(focus.r()+1,focus.c());
                    coordStack.push(temp);
                    maze[focus.r()+1][focus.c()]='V';
                }
            //East
            }if(focus.c()+1<nCols){
                if(maze[focus.r()][focus.c()+1]=='.'){
                    Coord temp(focus.r(),focus.c()+1);
                    coordStack.push(temp);
                    maze[focus.r()][focus.c()+1]='V';
                }
            }
        }
    }
    return false;
}
int main()
        {
            string maze[10] = {
                "XXXXXXXXXX",
                "X........X",
                "XXXXX.X.XX",
                "X...X.X..X",
                "X.X...X..X",
                "X.XXX.XXXX",
                "XXX....X.X",
                "X.XX.XXX.X",
                "X....X...X",
                "XXXXXXXXXX"
            };
        
            if (pathExists(maze, 10,10, 6,5, 1,8))
                cout << "Solvable!" << endl;
            else
                cout << "Out of luck!" << endl;
        }