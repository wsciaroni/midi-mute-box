#include <Embedded_Template_Library.h> // Requires Embedded Template Library (20.40.0 used)
#include <etl/debounce.h>
#include <etl/vector.h>
#include <etl/algorithm.h>

// --- Configuration ---

// Define MIDI channel for X32 communication
#define X32_MIDI_CHANNEL 1

// Define the number of channels to control
#define NUM_CHANNELS 2

// Define pin assignments.
const etl::array<int, NUM_CHANNELS> buttonPins = {5};
const etl::array<int, NUM_CHANNELS> ledPins = {4};

// --- MIDI Constants (X32 Specific) ---
const int MUTE_CC_START = 0x60;
const byte MUTE_ON_VALUE = 127;
const byte MUTE_OFF_VALUE = 0;

// Debounce time in milliseconds
const unsigned long DEBOUNCE_SAMPLE_VALID_COUNT = 50;

// Represents a single channel (button, LED, mute state, debouncer).
class Channel {
public:
    Channel(int buttonPin, int ledPin, int channelNumber) :
        _buttonPin(buttonPin),
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
    void sampleButton() {
        _debouncer.add(digitalRead(_buttonPin) == LOW); // LOW is pressed
    }

    // Check if the button was pressed (rising edge after debouncing).
    bool wasButtonPressed() const {
      return _debouncer.is_set() && _debouncer.has_changed();
    }

    void setMuteState(bool muted) {
        if (_isMuted != muted) {
            _isMuted = muted;
            updateLed();
            sendMidiMuteCommand();
        }
    }

    bool getMuteState() const {
        return _isMuted;
    }

    void updateLed() const {
        digitalWrite(_ledPin, _isMuted ? HIGH : LOW);
    }

    void toggleMute() {
        setMuteState(!_isMuted);
    }

private:
    void sendMidiMuteCommand() const {
        Serial.print("Channel ");
        Serial.print(_channelNumber);
        if(_isMuted)
        {
          Serial.print(" Mute CC:");
          Serial.println(MUTE_CC_START + (_channelNumber - 1));
          // MUTE_ON_VALUE
        }
        else
        {
          Serial.print(" UnMute CC:");
          Serial.println(MUTE_CC_START + (_channelNumber - 1));
          // MUTE_OFF_VALUE
        }
    }

    int _buttonPin;
    int _ledPin;
    int _channelNumber;
    bool _isMuted;
    etl::debounce<DEBOUNCE_SAMPLE_VALID_COUNT, 0, 0> _debouncer; // Embedded debouncer
};

// Manages all channels and MIDI communication.
class MuteBox {
public:
    MuteBox() : _channels()
    {
        for (int i = 0; i < NUM_CHANNELS; ++i) {
            _channels.emplace_back(buttonPins.at(i), ledPins.at(i), i + 1);
        }
    }
    ~MuteBox() = default;

    void update() {
        handleButtonPresses();
    }

    // Placeholder for MIDI message handling (add your MIDI logic here)
    void handleMidiMessage(byte type, byte channel, byte data1, byte data2) {}
    void syncWithMixer() {}

private:
    void handleButtonPresses() {
        for (auto& channel : _channels) { // Use a range-based for loop for cleaner iteration
            channel.sampleButton();       // Sample the button state
            if (channel.wasButtonPressed()) {
                channel.toggleMute();
            }
        }
    }

    etl::vector<Channel, NUM_CHANNELS> _channels;
};

// --- Global Objects ---
MuteBox muteBox;

// --- Arduino Setup and Loop ---
// (Placeholder for MIDI callback - add if needed)
void handleMidiControlChange(byte channel, byte control, byte value) {}

void setup() {
    Serial.begin(115200);
    Serial.println("MIDI connection established.");
    delay(1000);
    muteBox.syncWithMixer();
}

void loop() {
    muteBox.update();
}