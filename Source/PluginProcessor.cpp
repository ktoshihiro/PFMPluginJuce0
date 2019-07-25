/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PfmpluginJuce0AudioProcessor::PfmpluginJuce0AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
    ),
#endif
    apvts(/* AudioProcessor& */ *this, /* UndoManager* */ nullptr)
{
    //shouldPlaySound = new AudioParameterBool("shouldPlaySoundParam", "shouldPlaySound", false);
    //addParameter(shouldPlaySound);
    auto shouldPlaySoundParam = std::make_unique<AudioParameterBool>("shouldPlaySoundParam", "shouldPlaySound", false);
    auto* param = apvts.createAndAddParameter(std::move(shouldPlaySoundParam));
    shouldPlaySound = dynamic_cast<AudioParameterBool*>(param);

    auto pgColorParam = std::make_unique<AudioParameterFloat>("bgColorParam", "bgColor", 0.0f, 1.0f, 0.5f);
    param = apvts.createAndAddParameter(std::move(pgColorParam));
    bgColor = dynamic_cast<AudioParameterFloat*>(param);

    apvts.state = ValueTree("PFMSynthValueTree");
}

PfmpluginJuce0AudioProcessor::~PfmpluginJuce0AudioProcessor()
{
}

//==============================================================================
const String PfmpluginJuce0AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PfmpluginJuce0AudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool PfmpluginJuce0AudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool PfmpluginJuce0AudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double PfmpluginJuce0AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PfmpluginJuce0AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PfmpluginJuce0AudioProcessor::getCurrentProgram()
{
    return 0;
}

void PfmpluginJuce0AudioProcessor::setCurrentProgram(int index)
{
}

const String PfmpluginJuce0AudioProcessor::getProgramName(int index)
{
    return {};
}

void PfmpluginJuce0AudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void PfmpluginJuce0AudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void PfmpluginJuce0AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PfmpluginJuce0AudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void PfmpluginJuce0AudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int i = 0; i < buffer.getNumSamples(); ++i) {
        for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
            if (shouldPlaySound->get()) {
                buffer.setSample(channel, i, r.nextFloat());
            }
            else {
                buffer.setSample(channel, i, 0);
            }
        }
    }
}

//==============================================================================
bool PfmpluginJuce0AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PfmpluginJuce0AudioProcessor::createEditor()
{
    // `this` is pointing to the active instance of the plugin processor.
    // `this` is dereferenced, giving us the actual active instance, 
    // which is passed to the plugin editor constructor as a reference.
    return new PfmpluginJuce0AudioProcessorEditor(*this);
}

//==============================================================================
void PfmpluginJuce0AudioProcessor::getStateInformation(MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    DBG(apvts.state.toXmlString());
    MemoryOutputStream mos(destData, false);
    apvts.state.writeToStream(mos);
}

void PfmpluginJuce0AudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    MemoryBlock mb(data, static_cast<size_t>(sizeInBytes));
    MemoryInputStream mis(mb, false);
    apvts.state.readFromStream(mis);
}

void PfmpluginJuce0AudioProcessor::UpdateAutomatableParameter(RangedAudioParameter* param, float value)
{
    param->beginChangeGesture();
    param->setValueNotifyingHost(value);
    param->endChangeGesture();
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PfmpluginJuce0AudioProcessor();
}
