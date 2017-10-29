#include <ncurses.h>
#include <vector>
#include <string>

using namespace std;

class Gui{
public:
  Gui();
  ~Gui();
  WINDOW * newWindow(int height,int width, int starty, int startx);
  vector<WINDOW *> windows;
  void deleteWindow(WINDOW *local_win);
  void columns(int numColumns);
  void updateHeader(WINDOW * win, string header);
  void updateContents(WINDOW * win, string data);
  void updateContents(WINDOW * win, double data);
};

Gui::Gui(){
  initscr();
  curs_set(0);
  noecho();
  cout.setstate(std::ios_base::failbit);
}

void Gui::updateContents(WINDOW * win, string data){
  int y,x,dataHeight;
  getmaxyx(win,y,x);
  dataHeight = 3*(LINES/4);
  string clear;
  for(int i=2;i<x;i++){
    clear.push_back(' ');
  }
  mvwprintw(win,LINES/2,1,clear.c_str());
  mvwprintw(win,LINES/2,(x-data.size())/2,data.c_str() );
  wrefresh(win);

}

void Gui::updateContents(WINDOW * win, double data){
  int y,x,dataHeight;
  string input;
  input = to_string(data);
  getmaxyx(win,y,x);
  dataHeight = 3*(LINES/4);
  string clear;
  for(int i=2;i<x;i++){
    clear.push_back(' ');
  }
  mvwprintw(win,LINES/2,1,clear.c_str());
  mvwprintw(win,LINES/2,(x-input.size())/2,input.c_str() );
  wrefresh(win);
}

void Gui::updateHeader(WINDOW * win, string header){
  int y,x,headerHeight;
  getmaxyx(win,y,x);
  headerHeight = LINES/4;
  string line;
  for(int i=2;i<x;i++){
    line.push_back('-');
  }
  mvwprintw(win,headerHeight,1,line.c_str());
  mvwprintw(win,headerHeight - LINES/8,(x-header.size())/2,header.c_str());
  wrefresh(win);

}

void Gui::columns(int numColumns){
  int height = LINES;
  int width = COLS/numColumns;
  int startx = 0;
  windows.reserve(numColumns);
  for(int i=0;i<numColumns;i++){
    windows[i] = newWindow(height,width,0,startx);
    startx = startx + width;
  }
}

WINDOW * Gui::newWindow(int height, int width, int starty, int startx){
  WINDOW *local_win;
	local_win = newwin(height, width, starty, startx); //creates new window struct
	box(local_win, 0 , 0); //draws box around window 0,0 mean use default horizontal and vertical line characters
	wrefresh(local_win); //refresh the new window you just made
	return local_win; //return pointer to new window struct you created
}

void Gui::deleteWindow(WINDOW *local_win){
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' '); // erase the border from the screen
	wrefresh(local_win); //refresh the screen
	delwin(local_win); //deallocate the memory use to hold the window struct
}

Gui::~Gui(){
  for(auto window : windows){
    deleteWindow(window);
  }
  cout.clear();
  endwin();
}
