/*
 * JobRequest.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: ravitandon
 */

#include "JobRequest.h"

JobRequest::JobRequest(int t, int s, int j, int u) {
	time = t;
	steps = s;
	jobId= j;
	units = u;
}

JobRequest::JobRequest(){

}

JobRequest::~JobRequest() {
	// TODO Auto-generated destructor stub
}

