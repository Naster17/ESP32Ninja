#include "ir_driver.h"

#ifdef ENABLE_IR
const uint16_t kRecvPin = IR_RECEIVER_PIN;
const uint16_t kCaptureBufferSize = 1024;
const uint8_t kTimeout = 50;
const uint16_t kMinUnknownSize = 12;
const uint8_t kTolerancePercentage = kTolerance; // kTolerance is normally 25%

IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);
decode_results results; // Somewhere to store the results

const uint16_t kIrLed = IR_TRANSMITTER_PIN; // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRsend irsend(kIrLed);

namespace Drivers
{

    bool IR::init()
    {
        irrecv.setUnknownThreshold(kMinUnknownSize);
        irrecv.setTolerance(kTolerancePercentage); // Override the default tolerance.
        irrecv.enableIRIn();                       // Start the receiver
        irsend.begin();
        return true;
    }
    void IR::receiver()
    {
        while (1)
        {
            // Check if the IR code has been received.
            if (irrecv.decode(&results))
            {
                if (results.overflow)
                    Serial.println(String(D_WARN_BUFFERFULL) + ": " + String(kCaptureBufferSize));

                if (kTolerancePercentage != kTolerance)
                    Serial.println(String(D_STR_TOLERANCE) + " : " + String(kTolerancePercentage));

                Serial.println(resultToHumanReadableBasic(&results));
                Serial.println(resultToSourceCode(&results));
                Serial.println(); // Blank line between entries
                // decode_type aka protocol
            }
        }
    }

    void IR::transmitter()
    {
        uint16_t rawData[71] = {9070, 4534, 570, 566, 544, 592, 570, 566, 568, 570, 568, 568, 566, 570, 570, 568, 570, 568, 568, 1678, 542, 1706, 576, 1674, 566, 1680, 542, 596, 570, 1678, 568, 1680, 564, 1684, 568, 568, 568, 1680, 570, 564, 572, 566, 568, 568, 568, 568, 570, 568, 568, 568, 564, 1684, 566, 570, 572, 1676, 568, 1678, 542, 1710, 570, 1674, 540, 1708, 564, 1684, 568, 41218, 9066, 2262, 568}; // NEC F740BF
        irsend.sendRaw(rawData, 71, 38);
        // Send a raw data capture at 38kHz.
        Serial.println("NEC");
        irsend.sendNEC(0xF740BF);
        // uint32_t address = 0xEF00;
        // uint32_t command = 0x3;
        // uint32_t data = irsend.encodeNEC(address, command);
        // irsend.sendNEC(data, sizeof(data));
        // irsend.send(NEC,);
    }

    /*
    Timestamp : 000270.692
    Protocol  : SAMSUNG
    Code      : 0xA0A012ED (32 Bits)

    uint16_t rawData[67] = {4566, 4516,  528, 1704,  504, 612,  528, 1704,  526, 588,  528, 588,  526, 588,  528, 590,  526, 588,  530, 1704,  526, 590,  528, 1704,  528, 588,  526, 590,  528, 588,  528, 588,  526, 590,  526, 590,  524, 590,  528, 588,  526, 1706,  526, 590,  526, 590,  528, 1704,  526, 590,  526, 1706,  524, 1708,  526, 1706,  526, 590,  524, 1708,  524, 1706,  526, 592,  524, 1706,  526};  // SAMSUNG A0A012ED
    uint32_t address = 0x5;
    uint32_t command = 0x48;
    uint64_t data = 0xA0A012ED;
    */
    /*
    Timestamp : 001137.742
    Protocol  : NEC
    Code      : 0xF7C03F (32 Bits)

    uint16_t rawData[71] = {9070, 4532,  612, 522,  618, 522,  570, 568,  544, 594,  570, 568,  618, 518,  572, 566,  570, 568,  570, 1680,  570, 1678,  576, 1672,  544, 1704,  618, 520,  616, 1632,  618, 1632,  616, 1630,  614, 1634,  606, 1644,  612, 526,  572, 564,  606, 532,  612, 524,  570, 568,  602, 534,  606, 532,  608, 528,  608, 1640,  604, 1646,  602, 1644,  572, 1678,  572, 1676,  600, 1650,  570, 41228,  9066, 2260,  568};  // NEC F7C03F
    uint32_t address = 0xEF00;
    uint32_t command = 0x3;
    uint64_t data = 0xF7C03F;

    */

}

#endif