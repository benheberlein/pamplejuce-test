/**
 * @file SimplePanner.h
 * @author ben (ben.heberlein@gmail.com)
 * @date 2024-07-27
 *
 * @brief This file consists of the SimplePanner class, which is used for stereo audio processing.
 *
 * SimplePanner is a class that inherits from the JUCE's AudioProcessor.
 * It provides panning capability for audio signals, thus allowing control of the amplitude or
 * intensity of the signal in two separate channels. The class provides methods for manipulating
 * panning, checking and handling audio buses layout, and typical methods to handle and manage
 * the audio processor's state.
 */

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

using namespace juce;

namespace nla {

class SimplePanner : public juce::AudioProcessor {
public:
    SimplePanner();

    /**
     * @brief Prepare to play method
     */
    void prepareToPlay(double a, int b) override;

    /**
     * @brief Releases resources used by the object
     */
    void releaseResources() override;

    /**
     * @brief Validates if the provided audio bus layout is supported
     * @param layouts Layouts to check
     * @return True if layout is supported, else false
     */
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

    /**
     * @brief Process an audio block
     * @param buffer Buffer to process
     * @param midiBuffer MidiBuffer
     */
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiBuffer) override;

    /**
     * @brief Creates and returns an AudioProcessorEditor object
     * @return Pointer to the created AudioProcessorEditor
     */
    juce::AudioProcessorEditor* createEditor() override;

    /**
     * @brief Checks if the object has an editor
     * @return True if it has editor, else false
     */
    bool hasEditor() const override;

    /**
     * @brief Returns the name of the object
     * @return Name as juce::String
     */
    const juce::String getName() const override;

    /**
     * @brief Checks if the object accepts MIDI input
     * @return True if Midi is accepted, else false
     */
    bool acceptsMidi() const override;

    /**
     * @brief Checks if the object produces MIDI output
     * @return True if Midi is produced, else false
     */
    bool producesMidi() const override;

    /**
     * @brief Returns the tail length in seconds
     * @return Tail length in seconds
     */
    double getTailLengthSeconds() const override;

    /**
     * @brief Returns the number of programs
     * @return Number of programs
     */
    int getNumPrograms() override;

    /**
     * @brief Returns the index of the current program
     * @return Current program index
     */
    int getCurrentProgram() override;

    /**
     * @brief Sets the current program to the given index
     * @param index Index to set
     */
    void setCurrentProgram(int index) override;

    /**
     * @brief Returns the name of the program at index
     * @param index Index to get name from
     * @return Name of program as juce::String
     */
    const juce::String getProgramName(int index) override;

    /**
     * @brief Changes the name of the program at index
     * @param index Index to change name
     * @param newName New name to set
     */
    void changeProgramName(int index, const juce::String& newName) override;

    /**
     * @brief Copies state information to a juce::MemoryBlock
     * @param destData Destination juce::MemoryBlock
     */
    void getStateInformation(juce::MemoryBlock& destData) override;

    /**
     * @brief Sets state information from a data buffer
     * @param data Pointer to the data
     * @param sizeInBytes Size of the data in bytes
     */
    void setStateInformation(const void* data, int sizeInBytes) override;

    /**
     * @brief Returns value 88
     * @return 88
     */
    static int a();


private:
    float panValue;

    juce::AudioProcessorValueTreeState parameters;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimplePanner)
};

} // namespace nla