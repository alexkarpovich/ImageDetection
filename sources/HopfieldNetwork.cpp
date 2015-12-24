#include "../headers/HopfieldNetwork.h"

HopfieldNetwork::HopfieldNetwork(double ** learningSet, int imageCount, int imageSize) {
	this->imageSize = imageSize;
	this->imageCount = imageCount;
	this->learningSet = learningSet;
}
