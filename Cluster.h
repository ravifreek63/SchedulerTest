/*
 * Cluster.h
 *
 *  Created on: Mar 28, 2015
 *      Author: ravitandon
 */

#ifndef CLUSTER_H_
#define CLUSTER_H_

#include<map>
#include<mutex>
#include<vector>
#include "JobRequest.h"
#include "algorithm"
#include <iostream>

using namespace std;

class Cluster {
private:
	std::map<int, int> nodeResUnits; // maps each node to the available resource units
	std::mutex nodeResMutex;
	std::vector<JobRequest> requestVector;
	std::mutex requestVectorLock;
	int numberNodes; // total number of nodes in the cluster
	void sortJobQueue(); // this is the function that sorts the vector by the finish time

public:
	Cluster(int, int);
	virtual ~Cluster();
	void init(int, int);
	void addResource(int nodeId, int units);
	void removeResource(int nodeId, int units);
	std::vector<JobRequest> getNextKJobs(int k);
	void pushJobs(std::vector<JobRequest> vec);
	int getResource(int units);
};

#endif /* CLUSTER_H_ */
