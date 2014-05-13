// c++ -o splitLHE splitLHE.cpp
#include "LHEF.h"
#include <iomanip>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

int main(int argc, char ** argv) {
  if(argc < 4) {
   std::cout << "Usage: " << argv[0] << " fileToSplit.lhe initial_number   end_number" << std::endl ;
   return -1;
  }

  std::ifstream ifs (argv[1]) ;
  LHEF::Reader reader (ifs) ;

  std::string filenameOutput = argv[2] ;

  int initial_number = atoi (argv[3]) ;
  int end_number = atoi (argv[4]) ;

  LHEF::Writer * writer ;
  std::ofstream outputStream ;
  outputStream.open (filenameOutput.c_str ()) ;
  std::cout << "opening in output : " << filenameOutput << std::endl ;
  writer = new LHEF::Writer (outputStream) ;

  int ieve = 0 ;
  int index = 0 ;
  //---- loop over input events
  while (reader.readEvent ()) {
   if (ieve == 0) {
    writer->headerBlock() << reader.headerBlock ;
    writer->initComments() << reader.initComments ;
    writer->heprup = reader.heprup ;
    writer->init () ;
   }

   if ( reader.outsideBlock.length() ) {
    std::cout << reader.outsideBlock;
   }
   writer->eventComments() << reader.eventComments;
   writer->hepeup = reader.hepeup;

   ieve++ ;
   if (ieve >= initial_number   &&    ieve < end_number) {
    writer->writeEvent();
   }
  }
  outputStream.close () ;
  //---- loop over input events

  delete writer ;
  return 0 ;
}