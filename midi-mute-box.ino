#include <Arduino.h>

#include <Embedded_Template_Library.h> // Requires Embedded Template Library (20.40.0 used)
#include <etl/debounce.h>
#include <etl/vector.h>
#include <etl/algorithm.h>
#include <etl/binary.h>

// --- Configuration ---

// Define MIDI channel for X32 communication
#define X32_MIDI_SERIAL Serial1 // Use Serials for MIDI communication
#define X32_MIDI_TX_PIN 13
#define X32_MIDI_RX_PIN 15 // Unused, but must be specified

#include "X32_MIDI.h"

// Define the number of channels to control
#define NUM_CHANNELS 8

// Define pin assignments.
const etl::array<int, NUM_CHANNELS> buttonPins = {34, 35, 32, 33, 25, 26, 27, 14};
const etl::array<int, NUM_CHANNELS> ledPins =    {23, 22, 21, 19, 18, 17, 16,  4};
const etl::array<X32MuteControlChannel, NUM_CHANNELS> channelNumbers = {
  X32MuteControlChannel::CH1_MUTE,
  X32MuteControlChannel::CH2_MUTE,
  X32MuteControlChannel::CH3_MUTE,
  X32MuteControlChannel::CH4_MUTE,
  X32MuteControlChannel::CH5_MUTE,
  X32MuteControlChannel::CH6_MUTE,
  X32MuteControlChannel::CH7_MUTE,
  X32MuteControlChannel::CH8_MUTE
  };

// Debounce time in milliseconds
const unsigned long DEBOUNCE_SAMPLE_VALID_COUNT = 50;

// Represents a single channel (button, LED, mute state, debouncer).
class Channel
{
public:
    Channel(int buttonPin, int ledPin, X32MuteControlChannel channelNumber) : _buttonPin(buttonPin),
                                                                              _ledPin(ledPin),
                                                                              _channelNumber(channelNumber),
                                                                              _isMuted(false),
                                                                              _debouncer() // Initialize debouncer
    {
        pinMode(_buttonPin, INPUT_PULLUP);
        pinMode(_ledPin, OUTPUT);
        updateLed();
    }

    // Sample the button state.  This should be called regularly in the main loop.
    void sampleButton()
    {
        _debouncer.add(digitalRead(_buttonPin) == LOW); // LOW is pressed
    }

    // Check if the button was pressed (rising edge after debouncing).
    bool wasButtonPressed() const
    {
        return _debouncer.is_set() && _debouncer.has_changed();
    }

    void setMuteState(bool muted)
    {
        if (_isMuted != muted)
        {
            _isMuted = muted;
            updateLed();
            sendMidiMuteCommand();
        }
    }

    bool getMuteState() const
    {
        return _isMuted;
    }

    void updateLed() const
    {
        digitalWrite(_ledPin, _isMuted ? HIGH : LOW);
    }

    void toggleMute()
    {
        setMuteState(!_isMuted);
    }

    void sendMidiMuteCommand() const
    {
        Serial.print("Channel ");
        Serial.print(static_cast<byte>(_channelNumber));
        if (_isMuted)
        {
            Serial.println(" Mute");
            //   Serial.println(MUTE_CC_START + (_channelNumber - 1));
            sendMuteCommand(_channelNumber, MuteControl::MUTE_ON);
        }
        else
        {
            Serial.println(" UnMute");
            //   Serial.println(MUTE_CC_START + (_channelNumber - 1));
            sendMuteCommand(_channelNumber, MuteControl::MUTE_OFF);
        }
    }

private:
    const int _buttonPin;
    const int _ledPin;
    const X32MuteControlChannel _channelNumber;
    bool _isMuted;
    etl::debounce<DEBOUNCE_SAMPLE_VALID_COUNT, 0, 0> _debouncer; // Embedded debouncer
};

// Manages all channels and MIDI communication.
class MuteBox
{
public:
    MuteBox() : _channels()
    {
        for (int i = 0; i < NUM_CHANNELS; ++i)
        {
            _channels.emplace_back(buttonPins[i], ledPins[i], channelNumbers[i]);
        }
    }
    ~MuteBox() = default;

    void update()
    {
      if(hasBeenTenSeconds())
      {
        syncWithMixer();
      }
      else
      {
        handleButtonPresses();
      }
    }

    // Placeholder for MIDI message handling (add your MIDI logic here)
    void handleMidiMessage(byte type, byte channel, byte data1, byte data2) {}
    void syncWithMixer()
    {
        for (auto &channel : _channels)
        {
            channel.sendMidiMuteCommand();
        }
    }

private:
    bool hasBeenTenSeconds() const
    {
      return (millis() % 10000) == 0;
    }

    void handleButtonPresses()
    {
        for (auto &channel : _channels)
        {                           // Use a range-based for loop for cleaner iteration
            channel.sampleButton(); // Sample the button state
            if (channel.wasButtonPressed())
            {
                channel.toggleMute();
            }
        }
    }

    etl::vector<Channel, NUM_CHANNELS> _channels;
};

// --- Global Objects ---
MuteBox muteBox;

// --- Arduino Setup and Loop ---

void setup()
{
    Serial.begin(115200);

    startMidi();
    Serial.println("MIDI connection established.");
    muteBox.syncWithMixer();
}

void loop()
{
    muteBox.update();
}