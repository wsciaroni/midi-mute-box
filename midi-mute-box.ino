// TODO: Add Midi Support
// MIDIUSB Headers
// #include <MIDIUSB.h>
// #include <MIDIUSB_Defs.h>
// #include <frequencyToNote.h>
// #include <pitchToFrequency.h>
// #include <pitchToNote.h>

// #include <MIDI.h> // Requires MIDIUSB library (1.0.5 used)

#include <Embedded_Template_Library.h> // Requires Embedded Template Library (20.40.0 used)

// #include <Arduino.h>

#include <etl/vector.h>    // For etl::vector
#include <etl/algorithm.h> // For etl::for_each

// --- Configuration ---

// Define MIDI channel for X32 communication (usually 1, but check your X32 setup)
#define X32_MIDI_CHANNEL 1

// Define the number of channels to control
// #define NUM_CHANNELS 8
#define NUM_CHANNELS 2

// Define pin assignments.  Adjust these to your actual wiring.
// Example: const int buttonPins[NUM_CHANNELS] = {2, 4, 5, 12, 13, 14, 15, 32};
// const etl::array<int, NUM_CHANNELS> buttonPins = {2, 4, 5, 12, 13, 14, 15, 32};
// const etl::array<int, NUM_CHANNELS> ledPins = {16, 17, 18, 19, 21, 22, 23, 25};  // Example LED pins.
const etl::array<int, NUM_CHANNELS> buttonPins = {2, 4};
const etl::array<int, NUM_CHANNELS> ledPins = {16, 17}; // Example LED pins.

// --- MIDI Constants (X32 Specific) ---

// Control Change messages for mute.  CC numbers 96 (0x60) to 103 (0x67) are mute toggles.
const int MUTE_CC_START = 0x60;

// Value for mute ON (any value > 0, typically 127 for consistency).
const byte MUTE_ON_VALUE = 127;
// Value for mute OFF (0).
const byte MUTE_OFF_VALUE = 0;

// --- Class Definitions ---

// Represents a single channel (button, LED, mute state).
class Channel
{
public:
    Channel(int buttonPin, int ledPin, int channelNumber) : _buttonPin(buttonPin),
                                                            _ledPin(ledPin),
                                                            _channelNumber(channelNumber),
                                                            _isMuted(false) // Initialize as unmuted
    {
        pinMode(_buttonPin, INPUT_PULLUP); // Use internal pull-up resistor
        pinMode(_ledPin, OUTPUT);
        updateLed(); // Set initial LED state
    }

    // Check if the button is pressed.  Debouncing is handled externally.
    bool isButtonPressed() const
    {
        return digitalRead(_buttonPin) == LOW; // LOW indicates pressed with INPUT_PULLUP
    }

    // Set the mute state and update the LED.
    void setMuteState(bool muted)
    {
        if (_isMuted != muted)
        { // Only update if the state changes
            _isMuted = muted;
            updateLed();
            sendMidiMuteCommand();
        }
    }
    bool getMuteState() const
    {
        return _isMuted;
    }

    // Update the LED based on the mute state.
    void updateLed() const
    {
        digitalWrite(_ledPin, _isMuted ? HIGH : LOW); // HIGH = red (muted), LOW = green (unmuted)
    }

    void toggleMute()
    {
        setMuteState(!_isMuted);
    }

private:
    void sendMidiMuteCommand() const
    {
        // Send Control Change message.
        // usbMIDI.sendControlChange(MUTE_CC_START + (_channelNumber -1), _isMuted ? MUTE_ON_VALUE : MUTE_OFF_VALUE, X32_MIDI_CHANNEL);
        Serial.print("Channel ");
        Serial.print(_channelNumber);
        Serial.print("Mute CC:");
        Serial.println(MUTE_CC_START + (_channelNumber - 1));
    }

    int _buttonPin;
    int _ledPin;
    int _channelNumber; // 1-based channel number
    bool _isMuted;
};

// Manages all channels and MIDI communication.
class MuteBox
{
public:
    MuteBox() : _channels() // pre-allocate storage.  Important for `etl::vector`
    {
        // Create Channel objects using placement new for efficiency and ETL compatibility.
        for (int i = 0; i < NUM_CHANNELS; ++i)
        {
            _channels.emplace_back(buttonPins.at(i), ledPins.at(i), i + 1);
            // new (&_channels[i]) Channel(buttonPins[i], ledPins[i], i + 1);
        }
    }
    ~MuteBox() = default; // No dynamic allocation within, so default destructor is sufficient.

    void update()
    {
        // Check button presses and toggle mute state.
        handleButtonPresses();
    }

    void handleMidiMessage(byte type, byte channel, byte data1, byte data2)
    {

        // Handle Control Change messages for mute status.
        // if (type == midi::ControlChange && channel == X32_MIDI_CHANNEL) {
        //      // Check if it's a mute CC message for one of our channels
        //      if (data1 >= MUTE_CC_START && data1 < MUTE_CC_START + NUM_CHANNELS)
        //      {
        //         int channelIndex = data1 - MUTE_CC_START;
        //          _channels[channelIndex].setMuteState(data2 != MUTE_OFF_VALUE);
        //      }
        // }
    }
    void syncWithMixer()
    {
        for (int i = 0; i < NUM_CHANNELS; ++i)
        {
            // TODO: Refactor this behavior from us setting the state of the mixer to us getting the state of the mixer.
            //      usbMIDI.sendControlChange(MUTE_CC_START + i, _channels[i].getMuteState() ? MUTE_ON_VALUE : MUTE_OFF_VALUE, X32_MIDI_CHANNEL);
        }
    }

private:
    void handleButtonPresses()
    {
        for (int i = 0; i < NUM_CHANNELS; ++i)
        {
            // TODO: Use etl::debounce
            // Simple debouncing: Check for a stable LOW state for a few milliseconds.
            if (_channels[i].isButtonPressed())
            {
                int debounceDelay = 50; // milliseconds
                delay(debounceDelay);
                if (_channels[i].isButtonPressed())
                {
                    _channels[i].toggleMute();
                    // Wait for button release to prevent multiple toggles
                    while (_channels[i].isButtonPressed())
                        ;
                }
            }
        }
    }

    etl::vector<Channel, NUM_CHANNELS> _channels;
};

// --- Global Objects ---

MuteBox muteBox; // Create the main MuteBox instance.

// --- Arduino Setup and Loop ---
// MIDI call back
void handleMidiControlChange(byte channel, byte control, byte value)
{
    // muteBox.handleMidiMessage(midi::ControlChange, channel, control, value);
}

void setup()
{
    Serial.begin(115200);
    // usbMIDI.setHandleControlChange(handleMidiControlChange);

    // Wait for MIDI connection (optional, but good for debugging)
    // while (!usbMIDI.read()){
    //   delay(100);
    Serial.println("Waiting for MIDI connection...");
    // }

    Serial.println("MIDI connection established.");
    // Sync With Mixer
    delay(1000);
    muteBox.syncWithMixer();
}

void loop()
{

    // usbMIDI.read();
    muteBox.update(); // Update the MuteBox (check buttons, update LEDs, send MIDI).
}