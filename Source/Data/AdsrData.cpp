/*
  ==============================================================================

    AdsrData.cpp
    Created: 29 Oct 2024 2:27:52pm
    Author:  Bogdan

  ==============================================================================
*/

#include "AdsrData.h"

void AdsrData::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
	adsrParams.attack = attack;
	adsrParams.decay = decay;
	adsrParams.sustain = sustain;
	adsrParams.release = release;

	setParameters(adsrParams);
}
