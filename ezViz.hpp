#include <ncurses.h>
#include <csignal>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Gui{
public:
  Gui();
  ~Gui();
  void deleteWindow(WINDOW *local_win);
  void columns(int numColumns);
  void updateHeader(int winNum, string header);
  void updateContents(int winNum, string data);
  void updateContents(int winNum, double data);
private:
  WINDOW * newWindow(int height, int width, int starty, int startx);
  vector<WINDOW *> windows;
};

Gui::Gui(){
  initscr(); // Start curses mode
  curs_set(0); // set Invisible cursor
  noecho(); //Don't echo back typed characters
  // register signal SIGINT and signal handler
  cout.setstate(std::ios_base::failbit); //block couts
}

void Gui::updateContents(int winNum, string data){
  if(winNum >= 0 && winNum <= windows.size()){
  WINDOW * win = windows[winNum - 1];
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
}

void Gui::updateContents(int winNum, double data){
  if(winNum <= windows.size()){
  WINDOW * win = windows[winNum - 1];
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
}}

void Gui::updateHeader(int winNum, string header){
  if(winNum <= windows.size()){
  WINDOW * win = windows[winNum + 1];
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
}}

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

WINDOW * Gui::newWindow(int height, int width, int starty, int startx){ //section off a portion of the screen to write specific data. Window will be bordered
  WINDOW *local_win;
	local_win = newwin(height, width, starty, startx); //creates new window struct
	box(local_win, 0 , 0); //draws box around window 0,0 mean use default horizontal and vertical line characters
	wrefresh(local_win); //refresh the new window you just made
	return local_win; //return pointer to new window struct you created
}

void Gui::deleteWindow(WINDOW *local_win){ //remove one of the windows
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
