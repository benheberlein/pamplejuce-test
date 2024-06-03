/**
 * @file SimplePanner.h
 * @author ben (ben.heberlein@gmail.com)
 * @date 2024-07-27
 *
 * @brief This file consists of the SimplePanner class, which is used for stereo audio processing.
 *
 * SimplePanner is a class that inherits from the JUCE's AudioProcessor. It offers functionality
 * for processing and manipulating audio signals. The main purpose of this class is to provide
 * panning facilities for audio signals which implies controlling the amplitude or intensity
 * of the signal separately in two channels.
 *
 * The class provides methods for manipulating panning, checking and handling audio buses layout
 * along with typical methods to handle and manage audio processor's state, amongst others.
 */

#include <juce_audio_processors/juce_audio_processors.h>

using namespace juce;

namespace nla {

/**
 * @brief Make parameters in a nice looking syntax
 */
auto makeParam = [] (const String& paramId, const String& paramName, float min, float max, float defaultValue)
{
    return std::make_unique<AudioParameterFloat>(
        paramId, paramName, NormalisableRange<float>(min, max), defaultValue);
};

class SimplePanner : public juce::AudioProcessor {
public:
    SimplePanner();

    void prepareToPlay(double, int) override {}
    void releaseResources() override {}

    bool isBusesLayoutSupported(const BusesLayout& layouts) const override {
        return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
    }

    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) override {
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

    juce::AudioProcessorEditor* createEditor() override { return nullptr; }
    bool hasEditor() const override { return false; }

    const juce::String getName() const override { return "SimplePanner"; }

    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int index) override {}
    const juce::String getProgramName(int index) override { return {}; }
    void changeProgramName(int index, const juce::String& newName) override {}

    void getStateInformation(juce::MemoryBlock& destData) override {}
    void setStateInformation(const void* data, int sizeInBytes) override {}

private:
    float panValue;

    juce::AudioProcessorValueTreeState parameters;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimplePanner)
};

} // namespace nla