#include "../../ezViz.hpp"
#include <unistd.h>

#define NUM_COLUMNS 4

int main(){
  Gui gui; //initialize user interface

  gui.columns(NUM_COLUMNS); //specify to create columns interface and number of columns

  gui.updateHeader(1, "First column header");
  gui.updateHeader(2, "This is an example");
  gui.updateHeader(3, "Watch live values change on screen!");
  gui.updateHeader(4, "Make as many columns as you need!");

  //gui.updateContents(1, "Write a string here");
  gui.updateContents(4, "Normal terminal will be restored on exit");
  gui.updateContents(3, 46.005);
  gui.updateContents(2, "Information can be overwritten here");
  gui.updateContents(1, "Ctrl-C to exit");

  int i = -10;
  int j = 0;
  while(true){
    if(i > 10){
      i = -10;
      j++;
    }
    else{
      gui.updateContents(3, (i*i*i)/6.5 + (i*i)*3 + 0.004*i); //function (1/6.5)i^3 + 3i^2 + 0.004i from -100 to 100
    }
    switch (j) {
      case 0:
        gui.updateHeader(4, "Make as many columns as you need!");
        break;
      case 1:
        gui.updateHeader(4, "Column Headers can be updated too!");
        break;
      case 2:
        gui.updateHeader(4, "Made with love and ncurses");
        break;
      case 3:
        j = 0;
        break;
    }
    usleep(90000);
    i++;
  }

}
