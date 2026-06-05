/*
    Main.cpp
    Application entry point for Redstar Designer.
    Creates the main window and hosts MainComponent.
*/

#include <JuceHeader.h>
#include "MainComponent.h"

class RedstarDesignerApplication : public juce::JUCEApplication
{
public:
    RedstarDesignerApplication() = default;

    const juce::String getApplicationName() override    { return "Redstar Designer"; }
    const juce::String getApplicationVersion() override { return "0.1.0"; }
    bool moreThanOneInstanceAllowed() override           { return true; }

    void initialise(const juce::String&) override
    {
        mainWindow.reset(new MainWindow(getApplicationName()));
    }

    void shutdown() override
    {
        mainWindow = nullptr;
    }

    // A desktop window that owns the MainComponent
    class MainWindow : public juce::DocumentWindow
    {
    public:
        explicit MainWindow(juce::String name)
            : DocumentWindow(name,
                juce::Desktop::getInstance().getDefaultLookAndFeel()
                    .findColour(juce::ResizableWindow::backgroundColourId),
                DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar(true);
            setContentOwned(new MainComponent(), true);
            setResizable(true, true);
            centreWithSize(getWidth(), getHeight());
            setVisible(true);
        }

        void closeButtonPressed() override
        {
            juce::JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION(RedstarDesignerApplication)