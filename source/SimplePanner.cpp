/**
 * @file SimplePanner.cpp
 * @brief 
 * @author ben
 * @date 6/2/2024
 */

#include "SimplePanner.h"

using namespace nla;

SimplePanner::SimplePanner()
    : AudioProcessor(
        BusesProperties()
            .withInput("Input", juce::AudioChannelSet::stereo())
            .withOutput("Output", juce::AudioChannelSet::stereo())),
        panValue(0.5),
        parameters(*this, nullptr, "Parameters", {
            makeParam("panParam", "Pan", 0.0f, 1.0f, 0.5f)
        }) {}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimplePanner();
}