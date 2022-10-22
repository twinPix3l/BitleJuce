#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Parameters.h"

using namespace juce;

//==============================================================================
MyBitCrushAudioProcessorEditor::MyBitCrushAudioProcessorEditor (MyBitCrushAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), parameters (vts)
{

  	dwSlider.reset (new juce::Slider ("Dry/Wet"));
  	addAndMakeVisible (dwSlider.get());
  	dwSlider->setRange (0, 0.5, 0);
  	dwSlider->setValue(DEFAULT_DW);
	dwSlider->setSliderStyle (Slider::LinearHorizontal);
  	dwSlider->Slider::setColour(Slider::trackColourId, Colour(0xffA814AD));
  	dwSlider->Slider::setColour(Slider::backgroundColourId, Colours::silver);
  	dwSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);

  	dwSlider->setBounds (150, 64, 500, 16);

  	bdSlider.reset (new juce::Slider ("BitDepth"));
  	addAndMakeVisible (bdSlider.get());
  	bdSlider->setRange (1, 32, 1);
  	bdSlider->setValue(DEFAULT_BD);
  	bdSlider->setSliderStyle (Slider::LinearHorizontal);
	bdSlider->Slider::setColour(Slider::backgroundColourId, Colours::yellow);
    	bdSlider->Slider::setColour(Slider::trackColourId, Colour(0xff263238));
  	bdSlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);

  	bdSlider->setBounds (150, 96, 500, 16);

  	rtSlider.reset (new juce::Slider ("Rate"));
  	addAndMakeVisible (rtSlider.get());
  	rtSlider->setRange (1, 70, 1);
  	rtSlider->setValue(DEFAULT_RT);
  	rtSlider->setSliderStyle (Slider::LinearHorizontal);
  	rtSlider->Slider::setColour(Slider::trackColourId, Colours::yellow);
  	rtSlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);

  	rtSlider->setBounds (150, 128, 500, 16);

  	mdButton.reset (new juce::ToggleButton ("Invert"));
  	mdButton->setColour(0x1000281, Colours::black);
	addAndMakeVisible (mdButton.get());

  	mdButton->setBounds (543, 156, 72, 24);

  	fqSlider.reset (new juce::Slider ("LFO freq (Hz)"));
  	addAndMakeVisible (fqSlider.get());
  	fqSlider->setRange (0.1, 20.0, 0);
  	fqSlider->setValue(DEFAULT_FQ);
  	fqSlider->setSliderStyle (Slider::LinearHorizontal);
  	fqSlider->Slider::setColour(Slider::trackColourId, Colours::yellow);
  	fqSlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);

  	fqSlider->setBounds (150, 192, 500, 16);

  	amSlider.reset (new juce::Slider ("Mod Amount"));
  	addAndMakeVisible (amSlider.get());
  	amSlider->setRange (0.0, MAX_RT / 2, 0);
  	amSlider->setValue(DEFAULT_AM);
  	amSlider->setSliderStyle (Slider::LinearHorizontal);
  	amSlider->Slider::setColour(Slider::trackColourId, Colours::yellow);
  	amSlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);

  	amSlider->setBounds (150, 224, 500, 16);

  	wfSlider.reset (new juce::Slider ("Waveform"));
  	addAndMakeVisible (wfSlider.get());
  	wfSlider->setRange (0, 4, 1);
  	wfSlider->setValue(DEFAULT_WF);
  	wfSlider->setSliderStyle (Slider::LinearHorizontal);
	wfSlider->Slider::setColour(Slider::trackColourId, Colour(0xff263238));
  	wfSlider->Slider::setColour(Slider::backgroundColourId, Colour(0xff263238));
	wfSlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);

  	wfSlider->setBounds (150, 256, 500, 16);

  	gpSlider.reset (new juce::Slider ("Volume"));
  	addAndMakeVisible (gpSlider.get());
  	gpSlider->setRange (0.0f, 1.0f, 0);
  	gpSlider->setValue(DEFAULT_GP);
  	gpSlider->setSliderStyle (Slider::LinearVertical);
  	gpSlider->Slider::setColour(Slider::trackColourId, Colour(0xffA814AD));
  	gpSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);

  	gpSlider->setBounds (695, 84, 48, 270);

  	dwAttachment.reset(new SliderAttachment(parameters, NAME_DW, *dwSlider));
  	bdAttachment.reset(new SliderAttachment(parameters, NAME_BD, *bdSlider));
  	rtAttachment.reset(new SliderAttachment(parameters, NAME_RT, *rtSlider));
  	mdAttachment.reset(new ButtonAttachment(parameters, NAME_MD, *mdButton));
  	fqAttachment.reset(new SliderAttachment(parameters, NAME_FQ, *fqSlider));
  	amAttachment.reset(new SliderAttachment(parameters, NAME_AM, *amSlider));
  	wfAttachment.reset(new SliderAttachment(parameters, NAME_WF, *wfSlider));
  	gpAttachment.reset(new SliderAttachment(parameters, NAME_GP, *gpSlider));

  	dwLabel.reset (new juce::Label ("Dry/Wet"));
  	addAndMakeVisible (dwLabel.get());
  	dwLabel->setText("Dry/Wet", juce::dontSendNotification);
  	dwLabel->attachToComponent(dwSlider.get(), true);
	dwLabel->setColour(0x1000281, Colours::black);

  	bdLabel.reset (new juce::Label ("Bit Depth"));
  	addAndMakeVisible (bdLabel.get());
  	bdLabel->setText("Bit Depth", juce::dontSendNotification);
  	bdLabel->attachToComponent(bdSlider.get(), true);
	bdLabel->setColour(0x1000281, Colours::black);

  	rtLabel.reset (new juce::Label ("Rate"));
  	addAndMakeVisible (rtLabel.get());
  	rtLabel->setText("Rate", juce::dontSendNotification);
  	rtLabel->attachToComponent(rtSlider.get(), true);
	rtLabel->setColour(0x1000281, Colours::black);

  	fqLabel.reset (new juce::Label ("LFO freq (Hz)"));
  	addAndMakeVisible (fqLabel.get());
  	fqLabel->setText("Freq LFO (Hz)", juce::dontSendNotification);
  	fqLabel->attachToComponent(fqSlider.get(), true);
	fqLabel->setColour(0x1000281, Colours::black);

  	amLabel.reset (new juce::Label ("Mod Amount"));
  	addAndMakeVisible (amLabel.get());
  	amLabel->setText("Mod Amount", juce::dontSendNotification);
  	amLabel->attachToComponent(amSlider.get(), true);
	amLabel->setColour(0x1000281, Colours::black);

  	wfLabel.reset (new juce::Label ("Waveform"));
  	addAndMakeVisible (wfLabel.get());
  	wfLabel->setText("LFO Shape", juce::dontSendNotification);
  	wfLabel->attachToComponent(wfSlider.get(), true);
	wfLabel->setColour(0x1000281, Colours::black);

  	gpLabel.reset (new juce::Label ("Volume"));
  	addAndMakeVisible (gpLabel.get());
  	gpLabel->setText("Volume", juce::dontSendNotification);
  	gpLabel->attachToComponent(gpSlider.get(), false);

  	setSize (768, 380);
}

MyBitCrushAudioProcessorEditor::~MyBitCrushAudioProcessorEditor()
{
  	dwAttachment = nullptr;
  	bdAttachment = nullptr;
  	rtAttachment = nullptr;
  	mdAttachment = nullptr;
  	fqAttachment = nullptr;
  	amAttachment = nullptr;
  	wfAttachment = nullptr;
  	gpAttachment = nullptr;

  	//[/Destructor_pre]

  	dwSlider = nullptr;
  	bdSlider = nullptr;
  	rtSlider = nullptr;
  	mdButton = nullptr;
  	fqSlider = nullptr;
  	amSlider = nullptr;
  	wfSlider = nullptr;
  	gpSlider = nullptr;

  	dwLabel = nullptr;
  	bdLabel = nullptr;
  	rtLabel = nullptr;
  	fqLabel = nullptr;
  	amLabel = nullptr;
  	wfLabel = nullptr;
  	gpLabel = nullptr;

}

//==============================================================================
void MyBitCrushAudioProcessorEditor::paint (juce::Graphics& g)
{
    	{
        	int x = 0, y = 0, width = 768, height = 380;
        	juce::Colour fillColour1 = Colours::black, fillColour2 = Colours::silver;
		    g.setGradientFill (juce::ColourGradient (fillColour1, 340.0f - 0.0f + x, 240.0f - 0.0f + y,
                                                 	 fillColour2, 40.0f - 0.0f + x, 0.0f - 0.0f + y,
                                                 	 false));
        	g.fillRect (x, y, width, height);
    	}
	
	{
		g.setColour (Colour(0xffA814AD));
            	g.setOpacity(1.0f);
            	g.setFont(fontBitle);
            	g.setFont(60.f);
            	g.drawText("Bitle", 0, 0, 384, 50, juce::Justification::topRight, true);

	    	g.setColour (juce::Colours::silver);
	    	g.drawText ("Juce", 384, 0, 384, 50, juce::Justification::topLeft, true);
        
            	g.resetToDefaultState();
            	g.setFont(20.0f);
		g.setColour (Colours::silver);
		g.setOpacity(1.0f);
		g.drawText ("v: 1.0.0", 675, 0, 93, 55, juce::Justification::centredBottom, true);

		g.setFont(15.0f);
		g.setColour (Colours::silver);
		g.setOpacity(1.0f);
		g.drawText ("Coded at Laboratorio di Informatica Musicale by A. C.", 2, 281, 675, 99, juce::Justification::bottomLeft, true);
	}

	{
		g.setOpacity(0.25);
		g.drawImageAt(btj, 0, 0, false);

		g.setOpacity(0.75f);
            	g.setImageResamplingQuality(juce::Graphics::ResamplingQuality::highResamplingQuality);
		g.drawImageAt(limR, 579, 284, false);
	}

        {
            	g.setColour(Colours::silver);
            	Line<float> line1(Point<float>(0, 55), Point<float>(768, 55));
            	g.drawLine(line1, 2.0f);

            	g.setColour(Colours::silver);
            	Line<float> line2(Point<float>(675, 55), Point<float>(675, 384));
            	g.drawLine(line2, 2.0f);

            	g.setColour(Colours::silver);
            	Line<float> line3(Point<float>(0, 281), Point<float>(675, 281));
            	g.drawLine(line3, 2.0f);

        }
}

void MyBitCrushAudioProcessorEditor::resized()
{
}