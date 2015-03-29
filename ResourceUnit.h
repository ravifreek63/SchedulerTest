/*
 * ResourceUnit.h
 *
 *  Created on: Mar 28, 2015
 *      Author: ravitandon
 */

#ifndef RESOURCEUNIT_H_
#define RESOURCEUNIT_H_

class ResourceUnit {
private:
	int nodeId;
	int units;
	int releaseTime;

public:
	ResourceUnit(int n, int u, int t);
	ResourceUnit();
	virtual ~ResourceUnit();
	int getReleaseTime() { return releaseTime; }
	int getNodeId() { return nodeId; }
	int getUnits() { return units; }
};

#endif /* RESOURCEUNIT_H_ */
