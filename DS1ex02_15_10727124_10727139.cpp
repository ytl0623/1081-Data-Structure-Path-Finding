// 10727124 劉宇廷 10727139 蘇崇傑
#include <iostream>
#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std ;

typedef char str20[20] ;

struct maz{
   char state ;
   bool r ;     // route
   bool v ;     // visited
   bool g ;     // goal
   bool finalg ;     // final goal
   bool realr ;     // real route
   bool realv ;     // real visited

};

class Maze{
  public:
    int maxX ;
    int maxY ;

    struct maz maze[100][100] ;

    bool Readmaze( string command ){
      string filename ;
      FILE  *infile = NULL ;
      filename = "input" + command + ".txt" ;
      infile = fopen( filename.c_str(), "r" ) ;

      if ( infile == NULL ){
        cout << endl << filename << " does not exist!" << endl ;
      }
      else{
        fscanf( infile, "%d %d", &maxX , &maxY ) ;
        char temp ;
        fscanf( infile, "%c", &temp ) ;

        int i, j ;
        for ( i = 0 ; i < maxY ; i++ ){
          for( j = 0 ; j < maxX ; j++ ){
            fscanf( infile, "%c", &maze[i][j].state ) ;

            if ( maze[i][j].state == 'G' ) {
              maze[i][j].g = true ;
            }
          }
          fscanf( infile, "%c" , &temp ) ;     // skip change line
          j = 0 ;     // next line

        }
        return true ;

      }

      fclose( infile ) ;
      system( "PAUSE" ) ;

    }

    void Initialization(){
      for (int i = 0 ; i < 100 ; i++ ){
        for( int j = 0 ; j < 100 ; j++ ){
          maze[i][j].v = false ;
          maze[i][j].r = false ;
        }
      }
    }

    bool Go( int x, int y ){
      if( ( maze[y][x].state == 'E' || maze[y][x].state == 'G' ) && y <= maxY && x <= maxX && maze[y][x].v == false ){
        maze[y][x].v = true ;
        maze[y][x].r = true ;

        if( maze[y][x].g  && maze[y][x].v ){
          maze[y][x].g = false ;
          maze[y][x].finalg = true ;
          return true ;

        }

        if( !( Go( x+1, y ) || Go( x, y+1 ) || Go( x-1, y ) || Go( x, y-1 ) ) ){
          maze[y][x].r = false ;
          return false ;

        }
        else{
          return true ;
        }
      }

      return false ;
    }

    void Current(){
      for (int i = 0 ; i < maxY ; i++ ){
        for( int j = 0 ; j < maxX ; j++ ){
          if ( maze[i][j].r ){
            maze[i][j].realr = true ;
          }

          if ( maze[i][j].v ){
            maze[i][j].realv = true ;
          }
        }
      }
    }

    void Showr(){
      for (int i = 0 ; i < maxY ; i++ ){
        for( int j = 0 ; j < maxX ; j++ ){
          if ( maze[i][j].realr == true && maze[i][j].finalg == false ){
            maze[i][j].state = 'R' ;
          }

          if ( maze[i][j].realv == true && maze[i][j].finalg != true && maze[i][j].realr == false ){
            maze[i][j].state = 'E' ;
          }

          cout <<  maze[i][j].state ;
        }
        cout << endl ;
      }
    }

    void Showv(){
      for (int i = 0 ; i < maxY ; i++ ){
        for( int j = 0 ; j < maxX ; j++ ){
          if ( maze[i][j].realv == true && maze[i][j].finalg == false ){
            maze[i][j].state = 'V' ;
          }
          cout <<  maze[i][j].state ;
        }
        cout << endl ;
      }
    }


    int Getx(){
      return x ;
    }

    int Gety(){
      return y ;
    }

  private:
    int x = 0 ;
    int y = 0 ;

};


int main(){
  cout << endl << "***Path Finding     ***" ;
  cout << endl << "***0. Quit          ***" ;
  cout << endl << "***1. One goal      ***" ;
  cout << endl << "***2. More goals    ***" ;
  cout << endl << "***********************" ;
  cout << endl << "Input a command(0,1,2):" ;

  str20 command ;
  cin >> command ;

  while ( strcmp( command, "0" ) != 0 ){
    if ( strcmp( command, "1" ) == 0 ){
      cout << endl << "Input a file number(e.g.,201,202,...):" ;
      cin >> command ;

      Maze amaze ;
      amaze.Initialization() ;
      amaze.Readmaze( command );

      int a = amaze.Getx() ;
      int b = amaze.Gety() ;

      if ( amaze.Go( b, a ) ){
        amaze.Current() ;
        amaze.Showv() ;
        cout << endl ;
        amaze.Showr() ;
        cout << endl ;

      }
      else {
        amaze.Current() ;
        amaze.Showv() ;
      }

    }
    else if ( strcmp( command, "2" ) == 0 ){
      cout << endl << "Input a file number(e.g.,201,202,...):" ;
      cin >> command ;

      int  num ;
      cout << endl << "Number of G (goals):" ;
      cin >> num ;

      Maze amaze ;
      amaze.Initialization() ;
      amaze.Readmaze( command ) ;

      int a = amaze.Getx() ;
      int b = amaze.Gety() ;

      while ( num > 0 && amaze.Go( b, a ) ){
        amaze.Current() ;
        a = amaze.Getx() ;
        cout << a << endl ;
        b = amaze.Gety() ;
        cout << b << endl ;
        amaze.Initialization() ;
        num-- ;
      }

      if ( num <= 0 ){
        amaze.Showv() ;
        cout << endl ;
        amaze.Showr() ;
        cout << endl ;

      }
      else{
        amaze.Showv() ;
      }
    }
    else{
      cout << endl << "The command does not exist!" ;
    }

    cout << endl << "***Path Finding     ***" ;
    cout << endl << "***0. Quit          ***" ;
    cout << endl << "***1. One goal      ***" ;
    cout << endl << "***2. More goals    ***" ;
    cout << endl << "***********************" ;
    cout << endl << "Input a command(0,1,2):" ;

    cin >> command ;

  }

}
