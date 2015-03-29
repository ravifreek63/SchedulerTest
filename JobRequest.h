/*
 * JobRequest.h
 *
 *  Created on: Mar 28, 2015
 *      Author: ravitandon
 */

#ifndef JOBREQUEST_H_
#define JOBREQUEST_H_

class JobRequest {
private:
	int time;
	int steps;
	int jobId;
	int units;

public:
	JobRequest(int time, int steps, int jobId, int units);
	JobRequest();
	virtual ~JobRequest();
	int getFinishTime() { return (time+steps); }
	int getUnits()  { return units; }
};

#endif /* JOBREQUEST_H_ */
