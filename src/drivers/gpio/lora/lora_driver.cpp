#include "lora_driver.h"

static bool loraStatus;

namespace Drivers
{
    bool Lora::init()
    {
        LoRa.setPins(PIN_LORA_CS, PIN_LORA_RST, PIN_LORA_DIO0);
        // LoRa.setSPIFrequency(20000000);
        LoRa.setTxPower(10);

        if (LoRa.begin(LORA_FREQUENCY))
        {
            loraStatus = true;
            return true;
        }
        else
        {
            loraStatus = false;
            return false;
        }
    }

    void Lora::deinit()
    {
        loraStatus = false;
        LoRa.end();
    }

    void Lora::set_tx_power(int power)
    {
        LoRa.setTxPower(power);
    }

    void Lora::send_lora_packet()
    {
        //     // // send packet
        LoRa.beginPacket();
        LoRa.print("Hello LoRa ");
        LoRa.endPacket();
        }

    String Lora::recive_lora_packet()
    {
        int packetSize = LoRa.parsePacket();
        if (packetSize)
        {
            // received a packet
            Serial.print("Received packet '");

            // read packet
            while (LoRa.available())
            {
                Serial.print((String)(char)LoRa.read());
                return (String)(char)LoRa.read();
            }

            // print RSSI of packet
            Serial.print("' with RSSI ");
            Serial.println((String)LoRa.packetRssi());
        }
        return "";
    }
}