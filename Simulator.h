/*
 * Simulator.h
 *
 *  Created on: Mar 28, 2015
 *      Author: ravitandon
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

class Simulator {
	static int totalTime;
	int numNodes;
	Cluster cluster;

public:
	Simulator();
	void runSimulation();
	void initGlobals();
	virtual ~Simulator();
	int getTicks();
	void readFile();
	static int getTotalTime() { return totalTime; }
};

#endif /* SIMULATOR_H_ */
