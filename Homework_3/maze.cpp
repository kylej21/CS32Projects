//#include<iostream>
//using namespace std;
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
    if(sr==er && sc==ec){
        return true;
    }
    maze[sr][sc]='V';
    if(maze[sr+1][sc]=='.'){
        bool x = pathExists(maze,nRows,nCols,sr+1,sc,er,ec);
        if(x==true){
            return true;
        }
    }
    if(maze[sr-1][sc]=='.'){
        bool x = pathExists(maze,nRows,nCols,sr-1,sc,er,ec);
        if(x==true){
            return true;
        }
    }
    if(maze[sr][sc+1]=='.'){
        bool x = pathExists(maze,nRows,nCols,sr,sc+1,er,ec);
        if (x==true){
            return true;
        }
    }
    if(maze[sr][sc-1]=='.'){
        bool x = pathExists(maze,nRows,nCols,sr,sc-1,er,ec);
        if(x==true){
            return true;
        }
    }
    return false;
}
/*
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
}*/