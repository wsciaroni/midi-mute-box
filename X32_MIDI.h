#pragma once

#include <Arduino.h>

enum class MuteControl : byte {
    MUTE_ON = 127,
    MUTE_OFF = 0
};

enum class X32MuteControlChannel : byte {
    CH1_MUTE = 0,
    CH2_MUTE = 1,
    CH3_MUTE = 2,
    CH4_MUTE = 3,
    CH5_MUTE = 4,
    CH6_MUTE = 5,
    CH7_MUTE = 6,
    CH8_MUTE = 7,
    CH9_MUTE = 8,
    CH10_MUTE = 9,
    CH11_MUTE = 10,
    CH12_MUTE = 11,
    CH13_MUTE = 12,
    CH14_MUTE = 13,
    CH15_MUTE = 14,
    CH16_MUTE = 15,
    CH17_MUTE = 16,
    CH18_MUTE = 17,
    CH19_MUTE = 18,
    CH20_MUTE = 19,
    CH21_MUTE = 20,
    CH22_MUTE = 21,
    CH23_MUTE = 22,
    CH24_MUTE = 23,
    CH25_MUTE = 24,
    CH26_MUTE = 25,
    CH27_MUTE = 26,
    CH28_MUTE = 27,
    CH29_MUTE = 28,
    CH30_MUTE = 29,
    CH31_MUTE = 30,
    CH32_MUTE = 31,
    AUX1_MUTE = 32,
    AUX2_MUTE = 33,
    AUX3_MUTE = 34,
    AUX4_MUTE = 35,
    AUX5_MUTE = 36,
    AUX6_MUTE = 37,
    USBL_MUTE = 38,
    USBR_MUTE = 39,
    FXRETURN1L_MUTE = 40,
    FXRETURN1R_MUTE = 41,
    FXRETURN2L_MUTE = 42,
    FXRETURN2R_MUTE = 43,
    FXRETURN3L_MUTE = 44,
    FXRETURN3R_MUTE = 45,
    FXRETURN4L_MUTE = 46,
    FXRETURN4R_MUTE = 47,
    BUS1_MUTE = 48,
    BUS2_MUTE = 49,
    BUS3_MUTE = 50,
    BUS4_MUTE = 51,
    BUS5_MUTE = 52,
    BUS6_MUTE = 53,
    BUS7_MUTE = 54,
    BUS8_MUTE = 55,
    BUS9_MUTE = 56,
    BUS10_MUTE = 57,
    BUS11_MUTE = 58,
    BUS12_MUTE = 59,
    BUS13_MUTE = 60,
    BUS14_MUTE = 61,
    BUS15_MUTE = 62,
    BUS16_MUTE = 63,
    MATRIX1_MUTE = 64,
    MATRIX2_MUTE = 65,
    MATRIX3_MUTE = 66,
    MATRIX4_MUTE = 67,
    MATRIX5_MUTE = 68,
    MATRIX6_MUTE = 69,
    MAINLR_MUTE = 70,
    MAINC_MUTE = 71,
    DCA1_MUTE = 72,
    DCA2_MUTE = 73,
    DCA3_MUTE = 74,
    DCA4_MUTE = 75,
    DCA5_MUTE = 76,
    DCA6_MUTE = 77,
    DCA7_MUTE = 78,
    DCA8_MUTE = 79,
    MUTEGRP1_MUTE = 80,
    MUTEGRP2_MUTE = 81,
    MUTEGRP3_MUTE = 82,
    MUTEGRP4_MUTE = 83,
    MUTEGRP5_MUTE = 84,
    MUTEGRP6_MUTE = 85
};

enum class X32FaderChannel : byte {
    CH1_FADER = 0,
    CH2_FADER = 1,
    CH3_FADER = 2,
    CH4_FADER = 3,
    CH5_FADER = 4,
    CH6_FADER = 5,
    CH7_FADER = 6,
    CH8_FADER = 7,
    CH9_FADER = 8,
    CH10_FADER = 9,
    CH11_FADER = 10,
    CH12_FADER = 11,
    CH13_FADER = 12,
    CH14_FADER = 13,
    CH15_FADER = 14,
    CH16_FADER = 15,
    CH17_FADER = 16,
    CH18_FADER = 17,
    CH19_FADER = 18,
    CH20_FADER = 19,
    CH21_FADER = 20,
    CH22_FADER = 21,
    CH23_FADER = 22,
    CH24_FADER = 23,
    CH25_FADER = 24,
    CH26_FADER = 25,
    CH27_FADER = 26,
    CH28_FADER = 27,
    CH29_FADER = 28,
    CH30_FADER = 29,
    CH31_FADER = 30,
    CH32_FADER = 31,
    AUX1_FADER = 32,
    AUX2_FADER = 33,
    AUX3_FADER = 34,
    AUX4_FADER = 35,
    AUX5_FADER = 36,
    AUX6_FADER = 37,
    USBL_FADER = 38,
    USBR_FADER = 39,
    FXRETURN1L_FADER = 40,
    FXRETURN1R_FADER = 41,
    FXRETURN2L_FADER = 42,
    FXRETURN2R_FADER = 43,
    FXRETURN3L_FADER = 44,
    FXRETURN3R_FADER = 45,
    FXRETURN4L_FADER = 46,
    FXRETURN4R_FADER = 47,
    BUS1_FADER = 48,
    BUS2_FADER = 49,
    BUS3_FADER = 50,
    BUS4_FADER = 51,
    BUS5_FADER = 52,
    BUS6_FADER = 53,
    BUS7_FADER = 54,
    BUS8_FADER = 55,
    BUS9_FADER = 56,
    BUS10_FADER = 57,
    BUS11_FADER = 58,
    BUS12_FADER = 59,
    BUS13_FADER = 60,
    BUS14_FADER = 61,
    BUS15_FADER = 62,
    BUS16_FADER = 63,
    MATRIX1_FADER = 64,
    MATRIX2_FADER = 65,
    MATRIX3_FADER = 66,
    MATRIX4_FADER = 67,
    MATRIX5_FADER = 68,
    MATRIX6_FADER = 69,
    MAINLR_FADER = 70,
    MAINC_FADER = 71,
    DCA1_FADER = 72,
    DCA2_FADER = 73,
    DCA3_FADER = 74,
    DCA4_FADER = 75,
    DCA5_FADER = 76,
    DCA6_FADER = 77,
    DCA7_FADER = 78,
    DCA8_FADER = 79
};

enum class X32PanChannel : byte {
    CH1_PAN = 0,
    CH2_PAN = 1,
    CH3_PAN = 2,
    CH4_PAN = 3,
    CH5_PAN = 4,
    CH6_PAN = 5,
    CH7_PAN = 6,
    CH8_PAN = 7,
    CH9_PAN = 8,
    CH10_PAN = 9,
    CH11_PAN = 10,
    CH12_PAN = 11,
    CH13_PAN = 12,
    CH14_PAN = 13,
    CH15_PAN = 14,
    CH16_PAN = 15,
    CH17_PAN = 16,
    CH18_PAN = 17,
    CH19_PAN = 18,
    CH20_PAN = 19,
    CH21_PAN = 20,
    CH22_PAN = 21,
    CH23_PAN = 22,
    CH24_PAN = 23,
    CH25_PAN = 24,
    CH26_PAN = 25,
    CH27_PAN = 26,
    CH28_PAN = 27,
    CH29_PAN = 28,
    CH30_PAN = 29,
    CH31_PAN = 30,
    CH32_PAN = 31,
    AUX1_PAN = 32,
    AUX2_PAN = 33,
    AUX3_PAN = 34,
    AUX4_PAN = 35,
    AUX5_PAN = 36,
    AUX6_PAN = 37,
    USBL_PAN = 38,
    USBR_PAN = 39,
    FXRETURN1L_PAN = 40,
    FXRETURN1R_PAN = 41,
    FXRETURN2L_PAN = 42,
    FXRETURN2R_PAN = 43,
    FXRETURN3L_PAN = 44,
    FXRETURN3R_PAN = 45,
    FXRETURN4L_PAN = 46,
    FXRETURN4R_PAN = 47,
    BUS1_PAN = 48,
    BUS2_PAN = 49,
    BUS3_PAN = 50,
    BUS4_PAN = 51,
    BUS5_PAN = 52,
    BUS6_PAN = 53,
    BUS7_PAN = 54,
    BUS8_PAN = 55,
    BUS9_PAN = 56,
    BUS10_PAN = 57,
    BUS11_PAN = 58,
    BUS12_PAN = 59,
    BUS13_PAN = 60,
    BUS14_PAN = 61,
    BUS15_PAN = 62,
    BUS16_PAN = 63,
    MATRIX1_PAN = 64,
    MATRIX2_PAN = 65,
    MATRIX3_PAN = 66,
    MATRIX4_PAN = 67,
    MATRIX5_PAN = 68,
    MATRIX6_PAN = 69,
    MAINLR_PAN = 70,
    MAINC_PAN = 71,
    DCA1_PAN = 72,
    DCA2_PAN = 73,
    DCA3_PAN = 74,
    DCA4_PAN = 75,
    DCA5_PAN = 76,
    DCA6_PAN = 77,
    DCA7_PAN = 78,
    DCA8_PAN = 79
};


namespace x32_midi_private
{
    enum class MidiChannel : int8_t {
        MIDI_CHANNEL_1 = 0,
        MIDI_CHANNEL_2 = 1,
        MIDI_CHANNEL_3 = 2,
        MIDI_CHANNEL_4 = 3,
        MIDI_CHANNEL_5 = 4,
        MIDI_CHANNEL_6 = 5
    };

    #define MIDI_CONTROL_CHANGE 0xB0 // Control Change message type

    void sendMidiCommand(MidiChannel midiChannel, byte channel, byte value)
    {
        X32_MIDI_SERIAL.write(MIDI_CONTROL_CHANGE | (static_cast<byte>(midiChannel) & etl::lsb_mask<byte, 4>::value));
        X32_MIDI_SERIAL.write(channel);
        X32_MIDI_SERIAL.write(value); // Ensure value is 7-bit
    }
} // namespace x32_midi_private

inline void startMidi(uint32_t baudRate = 31250)
{
    X32_MIDI_SERIAL.begin(baudRate);
    X32_MIDI_SERIAL.setTimeout(1000); // Set a timeout for MIDI communication
    delay(1000); // Allow time for the MIDI connection to establish
}

// Midi Control Change for Fader
/// @brief Sends a MIDI Control Change message to set the fader value.
/// @param channel The fader channel to control.
/// @param value The fader value (0-127).
/// @details The value is masked to ensure it is 7-bit.
inline void sendFaderCommand(X32FaderChannel channel, int8_t value)
{
    x32_midi_private::sendMidiCommand(
        x32_midi_private::MidiChannel::MIDI_CHANNEL_1,
        static_cast<byte>(channel),
        value & etl::lsb_mask<int8_t, 7>::value // Ensure value is 7-bit
    );
}

// MIDI Control Change for Mute
/// @brief Sends a MIDI Control Change message to mute or unmute a channel.
/// @param channel The channel to mute or unmute.
/// @param value The mute state (MUTE_ON or MUTE_OFF).
inline void sendMuteCommand(X32MuteControlChannel channel, MuteControl value)
{
    x32_midi_private::sendMidiCommand(
        x32_midi_private::MidiChannel::MIDI_CHANNEL_2,
        static_cast<byte>(channel),
        static_cast<byte>(value)
    );
}

// MIDI Control Change for Pan
/// @brief Sends a MIDI Control Change message to set the pan value.
/// @param channel The pan channel to control.
/// @param value The pan value (0-127).
/// @details The value is masked to ensure it is 7-bit.
inline void sendPanCommand(X32PanChannel channel, int8_t value)
{
    x32_midi_private::sendMidiCommand(
        x32_midi_private::MidiChannel::MIDI_CHANNEL_3,
        static_cast<byte>(channel),
        value & etl::lsb_mask<int8_t, 7>::value // Ensure value is 7-bit
    );
}
