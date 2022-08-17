#include "MainComponent.h"


//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (200, 200);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate) 
{
    juce::String message;
    message << "Preparando para tocar audio...\n";
    message << " samples por bloco esperados =  " << samplesPerBlockExpected << "\n";
    message << " sample rate =  " << sampleRate << "\n";
    juce::Logger::getCurrentLogger()->writeToLog(message);

}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Seu processamente de audio vai aqui!


    bufferToFill.clearActiveBufferRegion();

    for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); channel++)
    {
        // pega um pointer para o sample inicial no buffer para essa saida de audio
        auto* buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

        // preenche o numero requerido de samples com ruido entre -0.125 e + 0.125

        for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)

            buffer[sample] = random.nextFloat() * 0.25f - 0.125f;
    }
}



void MainComponent::releaseResources()
{
    juce::Logger::getCurrentLogger()->writeToLog("encerrando recursos de audio");

}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
