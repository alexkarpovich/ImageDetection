/*
 * HopfieldNetwork.h
 *
 *  Created on: Dec 24, 2015
 *      Author: aliaksandr
 */

#ifndef HOPFIELDNETWORK_H_
#define HOPFIELDNETWORK_H_


class HopfieldNetwork {
private:
	int imageSize;
	int imageCount;
	double ** learningSet;

public:
	HopfieldNetwork(double ** learningSet, int imageCount, int imageSize);
};


#endif /* HOPFIELDNETWORK_H_ */
