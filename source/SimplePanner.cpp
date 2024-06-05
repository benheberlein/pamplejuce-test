/**
 * @file SimplePanner.cpp
 * @brief 
 * @author ben
 * @date 6/2/2024
 */

#include "SimplePanner.h"

using namespace juce;
using namespace nla;

SimplePanner::SimplePanner()
  : AudioProcessor(
        BusesProperties()
            .withInput("Input", juce::AudioChannelSet::stereo())
            .withOutput("Output", juce::AudioChannelSet::stereo())),
    panValue(0.5),
    parameters(*this, nullptr, "Parameters", { makeParam("panParam", "Pan", 0.0f, 1.0f, 0.5f) }) {}

bool SimplePanner::isBusesLayoutSupported(const AudioProcessor::BusesLayout& layouts) const {
    return layouts.getMainInputChannelSet() == juce::AudioChannelSet::stereo() && layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void SimplePanner::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) {
    auto* leftChannel = buffer.getWritePointer(0);
    auto* rightChannel = buffer.getWritePointer(1);

    panValue = *parameters.getRawParameterValue("panParam");

    for(int i = 0; i < buffer.getNumSamples(); ++i) {
        auto leftGain = fminf(panValue, 0.5f) * 2.0f;
        auto rightGain = (1.0f - fmaxf(panValue, 0.5f)) * 2.0f;

        leftChannel[i] *= leftGain;
        rightChannel[i] *= rightGain;
    }
}

void SimplePanner::prepareToPlay(double sampleRate, int blockSize) {
    (void) sampleRate;
    (void) blockSize;
}

void SimplePanner::releaseResources() {}

AudioProcessorEditor* SimplePanner::createEditor() {
    return new GenericAudioProcessorEditor(*this);
}

bool SimplePanner::hasEditor() const {
    return true;
}

const String SimplePanner::getName() const {
    return "SimplePanner";
}

bool SimplePanner::acceptsMidi() const {
    return false;
}

bool SimplePanner::producesMidi() const {
    return false;
}

double SimplePanner::getTailLengthSeconds() const {
    return 0.0;
}

int SimplePanner::getNumPrograms() {
    return 1;
}

int SimplePanner::getCurrentProgram() {
    return 0;
}

void SimplePanner::setCurrentProgram(int index) {
    (void) index;
}

const String SimplePanner::getProgramName(int index) {
    (void) index;
    return "None";
}

void SimplePanner::changeProgramName(int index, const String& newName) {
    (void) index;
    (void) newName;
}

void SimplePanner::getStateInformation(MemoryBlock& destData) {
    (void) destData;
}

void SimplePanner::setStateInformation(const void* data, int sizeInBytes) {
    (void) data;
    (void) sizeInBytes;
}

int SimplePanner::a() {
    return 88;
}

#include "GainPluginDemo.h"

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new GainProcessor();
}