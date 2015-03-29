/*
 * Scheduler.h
 *
 *  Created on: Mar 28, 2015
 *      Author: ravitandon
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "JobRequest.h"
#include "ResourceUnit.h"
#include <thread>
#include <vector>
#include "Cluster.h"
#include <iostream>
#include <mutex>
using namespace std;

class Scheduler {
	Cluster *cluster;
	int k;
	std::vector<JobRequest> dispatchedRequests;
	std::vector<JobRequest> pendingJobRequests;
	std::vector<ResourceUnit> resourceDispatchRequests;
	std::mutex resourceDispatchRequestsLock;
	int ticks;
	int minUnits;
	int maxUnits;
	int minSteps;
	int maxSteps;
	int jobsPerSecond;
	int waitTime;

public:
	Scheduler(Cluster *c);
	void runScheduler();
	void runDispatcher();
	void runTimeClock();
	void runJobCreator();
	virtual ~Scheduler();
	int getLogicalTime() { return ticks; }
	void createExampleJobs();

};

#endif /* SCHEDULER_H_ */
