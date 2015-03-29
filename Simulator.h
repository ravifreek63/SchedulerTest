/*
 * Simulator.h
 *
 *  Created on: Mar 28, 2015
 *      Author: ravitandon
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include "ResourceUnit.h"
#include "JobRequest.h"
#include "Scheduler.h"
#include "Cluster.h"
#include <fstream>
#include <string>
#include <sstream>

class Simulator {
	static int totalTime;
	static int maxResources;
	static int numNodes;
	Cluster *cluster;

public:
	Simulator();
	void runSimulation();
	void initGlobals();
	virtual ~Simulator();
	int getTicks();
	void readFile();
	static int getTotalTime() { return totalTime; }
	static int getMaxResources() { return maxResources; }
	static int getNumberNodes() { return numNodes; }
};

#endif /* SIMULATOR_H_ */
