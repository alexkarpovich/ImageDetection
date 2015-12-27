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
	int trainingCount;
	double prevEnergy;
	double ** learningSet;
	double * inputs;
	double * outputs;
	double ** weights;

	void initVariables();
	void computeWeights();
	double * computeOutputs();
	double * prepareResult();
	double activate(double S);
	double computeEnergy(double * S);


public:
	HopfieldNetwork(double ** learningSet, int trainingCount, int imageSize);

	void training();
	double * process(double * testImage);
};


#endif /* HOPFIELDNETWORK_H_ */
