#include "../../ezViz.hpp"

#define NUM_COLUMNS 4

int main(){
  Gui gui; //initialize user interface

  gui.columns(NUM_COLUMNS); //specify to create columns interface and number of columns

  gui.updateHeader(1, "First column header");
  gui.updateHeader(3, "This is an example");

  //gui.updateContents(1, "Write a string here");
  gui.updateContents(2, 46.005);
  gui.updateContents(3, "Information can be overwritten here");
  gui.updateContents(1, "Ctrl-C to exit");

  while(true){};

}
