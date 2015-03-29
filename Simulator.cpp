/*
 * Simulator.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: ravitandon
 */

#include "Simulator.h"

int Simulator::totalTime=0;
int Simulator::maxResources=0;
int Simulator::numNodes=0;

int toInt(string numStr){
	stringstream ss;
	ss << numStr;
	int num;
	ss >> num;
	return num;
}

Simulator::Simulator() {
	readFile();
	cluster = new Cluster();
}

Simulator::~Simulator() {

}

void Simulator::readFile(){
	string line;
	ifstream myfile ("config.txt");
	int count=0;
	  if (myfile.is_open()){
		  while ( getline (myfile,line) ){
			  count++;
			  switch(count){
			  case 1:
				  Simulator::totalTime=toInt(line);
				  break;
			  case 2:
				  numNodes=toInt(line);
				  break;
			  case 3:
				  maxResources=toInt(line);
				  break;
			  }
		  }
		  myfile.close();
	  }
}

void Simulator::runSimulation(){
	Scheduler *scheduler = new Scheduler(cluster);
}

int main(){
   Simulator *simulator = new Simulator();
   simulator->runSimulation();
   return 0;
}
