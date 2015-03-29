/*
 * Scheduler.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: ravitandon
 */

#include "Scheduler.h"
#include <unistd.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Simulator.h"

int pickFromRange(int min, int max){
	int val = (rand() % (max-min+1)) + min;
	return val;
}

void Scheduler::runJobCreator(){
	std::vector<JobRequest> jobRequest;
	int jobId=0;
	srand (time(NULL));
	while(true){
		if(getLogicalTime()>Simulator::getTotalTime()) break;

		for(int id=0; id<jobsPerSecond; id++){
			jobId++;
			jobRequest.push_back(JobRequest(getLogicalTime(), pickFromRange(minSteps, maxSteps),
				jobId, pickFromRange(minUnits, maxUnits)));
		}
		cluster->pushJobs(jobRequest);
		jobRequest.clear();
		sleep(1);
	}
}

void Scheduler::runTimeClock(){
	ticks=0;
	while(true){
		if(getLogicalTime()>Simulator::getTotalTime()) break;
		sleep(1);
		ticks++;
	}
}

void Scheduler::runDispatcher(){
	std::vector<ResourceUnit> tempResourceDispatchRequests;
	ResourceUnit curr;
	while(true){
		if(getLogicalTime()>Simulator::getTotalTime()) break;
		for(int id=0; id<resourceDispatchRequests.size(); id++){
			curr = resourceDispatchRequests.at(id);
			if(curr.getReleaseTime()>=getLogicalTime()){
				cluster->addResource(curr.getNodeId(), curr.getUnits());
			} else {
				tempResourceDispatchRequests.push_back(curr);
			}
		}
		resourceDispatchRequests.clear();
		for(int id=0; id<tempResourceDispatchRequests.size(); id++){
			resourceDispatchRequests.push_back(tempResourceDispatchRequests.at(id));
		}
		tempResourceDispatchRequests.clear();
	}
}

void Scheduler::runScheduler(){
	JobRequest curr;
	int nodeId;
	std::vector<JobRequest> lPendingJobRequests;
	while(true){
		if(getLogicalTime()>Simulator::getTotalTime()) break;
		std::vector<JobRequest> jobReq = cluster->getNextKJobs(k);
		for(int id=0; id<k; id++){
			pendingJobRequests.push_back(jobReq.at(id));
		}
		for(int id=0; id<pendingJobRequests.size(); id++){
			curr=pendingJobRequests.at(id);
			nodeId = cluster->getResource(curr.getUnits());
			if(nodeId==-1){ // request is not satisfied, job pushed to temporary vector
				lPendingJobRequests.push_back(curr);
			} else {
				// add resource to release thread
				resourceDispatchRequests.push_back(ResourceUnit(nodeId, curr.getUnits(), curr.getFinishTime()));
			}
		}
		pendingJobRequests.clear();
		for(int id=0; id<lPendingJobRequests.size(); id++){
			pendingJobRequests.push_back(lPendingJobRequests.at(id));
		}
		lPendingJobRequests.clear();
	}
}

Scheduler::Scheduler(Cluster *c) {
	cluster = c;
	k=1; // number of jobs picked by the scheduler at a time
	minUnits = 1;
	maxUnits = 10;
	minSteps = 1;
	maxSteps = 5;
	jobsPerSecond = 2;

	std::thread timeClock(&Scheduler::runTimeClock, this);
	std::thread schedulerThread(&Scheduler::runScheduler, this);
	std::thread dispatcherThread(&Scheduler::runDispatcher, this);
	std::thread jobCreator(&Scheduler::runJobCreator, this);

	timeClock.join();
	schedulerThread.join();
	dispatcherThread.join();
	jobCreator.join();
}

Scheduler::~Scheduler() {

}

