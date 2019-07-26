/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class PfmpluginJuce0AudioProcessorEditor : public AudioProcessorEditor, public Timer
{
public:
    PfmpluginJuce0AudioProcessorEditor(PfmpluginJuce0AudioProcessor&);
    ~PfmpluginJuce0AudioProcessorEditor();

    //==============================================================================
    void paint(Graphics&) override;
    void resized() override;

    void mouseDown(const MouseEvent& e) override;
    void mouseUp(const MouseEvent& e) override;
    void mouseDrag(const MouseEvent& e) override;
    void timerCallback() override;

    void Update();

private:
    Point<int> lastClickPos;
    float cachedBgColor = 0.0f;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PfmpluginJuce0AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PfmpluginJuce0AudioProcessorEditor)
};
