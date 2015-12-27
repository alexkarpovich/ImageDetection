#include "../headers/HopfieldNetwork.h"
#include "../headers/Matrix.h"
#include <cassert>
#include <cmath>

HopfieldNetwork::HopfieldNetwork(double ** learningSet, int trainingCount, int imageSize) {
	this->imageSize = imageSize;
	this->trainingCount = trainingCount;
	this->learningSet = learningSet;

	initVariables();
}

void HopfieldNetwork::initVariables() {
	inputs = new double[imageSize];
	outputs = new double[imageSize];

	weights = new double*[imageSize];
	for (int i = 0; i < imageSize; i++) {
		weights[i] = new double[imageSize];
	}
}

void HopfieldNetwork::computeWeights() {
	Matrix X(learningSet, imageSize, trainingCount);

	Matrix W = X * (X.transpose() * X).invert() * X.transpose();

	weights = W.getMatrix();
}

double HopfieldNetwork::activate(double S) {
	return tanh(S);
}

double HopfieldNetwork::computeEnergy(double * S) {
	double energy = 0;

	for (int i = 0; i < imageSize; i++) {
		energy += S[i] * outputs[i];
	}

	return -1 * energy;
}

double * HopfieldNetwork::computeOutputs() {
	double * S = new double[imageSize];

	for (int i = 0; i < imageSize; i++) {
		S[i] = 0;
		for (int j = 0; j < imageSize; j++) {
			S[i] += weights[j][i] * inputs[j];
		}

		outputs[i] = activate(S[i]);
	}

	return S;
}

double * HopfieldNetwork::prepareResult() {
	double * result = new double[imageSize];

	for (int i = 0; i < imageSize; i++) {
		result[i] = outputs[i] > 0 ? 1 : -1;
	}

	return result;
}

void HopfieldNetwork::training() {
	computeWeights();
	cout << "[ Training ]:\n- Matrix of weights is computed" << endl;
}

double * HopfieldNetwork::process(double * testImage) {
	cout << "[ Detection ]:" << endl;

	double dE = 1;
	int iteration = 0;
	double * S;
	double energy = 0;

	inputs = testImage;

	do {
		++iteration;

		S = computeOutputs();
		energy = computeEnergy(S);

		if (iteration > 1) {
			dE = energy - prevEnergy;
		}

		cout << iteration << ". dE=" << dE << ", E(t+1)=" << energy << ", E(t)=" << prevEnergy << endl;

		prevEnergy = energy;
		inputs = outputs;

		delete[] S;
	} while (dE > 1E-1);

	return prepareResult();
}
