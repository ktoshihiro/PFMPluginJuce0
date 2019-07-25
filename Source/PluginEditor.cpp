/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PfmpluginJuce0AudioProcessorEditor::PfmpluginJuce0AudioProcessorEditor(PfmpluginJuce0AudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    cachedBgColor = processor.bgColor->get();
    setSize(400, 300);
}

PfmpluginJuce0AudioProcessorEditor::~PfmpluginJuce0AudioProcessorEditor()
{
    // The GUI should stop making sound when it's not visible
    //processor.shouldPlaySound->beginChangeGesture();
    //processor.shouldPlaySound->setValueNotifyingHost(false);
    //processor.shouldPlaySound->endChangeGesture();
    PfmpluginJuce0AudioProcessor::UpdateAutomatableParameter(processor.shouldPlaySound, false);
}

//==============================================================================
void PfmpluginJuce0AudioProcessorEditor::paint(Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId).interpolatedWith(Colours::red, cachedBgColor));

    g.setColour(Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void PfmpluginJuce0AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void PfmpluginJuce0AudioProcessorEditor::mouseDown(const MouseEvent& e)
{
    lastClickPos = e.getPosition();
}

void PfmpluginJuce0AudioProcessorEditor::mouseUp(const MouseEvent& e)
{
    //processor.shouldPlaySound->beginChangeGesture();
    //processor.shouldPlaySound->setValueNotifyingHost(!processor.shouldPlaySound->get());
    //processor.shouldPlaySound->endChangeGesture();
    PfmpluginJuce0AudioProcessor::UpdateAutomatableParameter(processor.shouldPlaySound, !processor.shouldPlaySound->get());
}

void PfmpluginJuce0AudioProcessorEditor::mouseDrag(const MouseEvent& e)
{
    auto clickPos = e.getPosition();
    //DBG(clickPos.toString());
    auto diffY = jlimit(-1.0, 1.0, -(clickPos.y - lastClickPos.y) / 200.0);
    diffY = jmap(diffY, -1.0, 1.0, 0.0, 1.0);
    /*
        in hindsight, it would have been much easierand simpler to do this instead of the jlimit / jmap:
            audo difY = jmap((double)clickPos.y, 0.0, (double)getHeight(), 1.0, 0.0);
        to map the cursor's y value in the window to the param
    */
    DBG("diffY: " << diffY);
    PfmpluginJuce0AudioProcessor::UpdateAutomatableParameter(processor.bgColor, diffY);
    cachedBgColor = processor.bgColor->get();
    repaint();
}
