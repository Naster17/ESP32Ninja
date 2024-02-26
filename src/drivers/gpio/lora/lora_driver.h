#ifndef ILORA_H
#define ILORA_H

#include "config.h"

#include <SPI.h>
#include <LoRa.h>

#define PIN_LORA_COPI 23
#define PIN_LORA_CIPO 19
#define PIN_LORA_SCK 18
#define PIN_LORA_CS 14
#define PIN_LORA_RST 13
#define PIN_LORA_DIO0 12

// /*433E6: 433 МГц (часто используется в Европе)
// 868E6: 868 МГц (часто используется в Европе)
// 915E6: 915 МГц (часто используется в Северной Америке)*/
#define LORA_FREQUENCY 868E6

namespace Drivers
{

    class Lora
    {
    public:
        static bool init();
        static void deinit();
        static void set_tx_power(int power);
        static void send_lora_packet();
        static String recive_lora_packet();
    };
}

#endif

// //======================================================================//

// #define PIN_LORA_COPI 23
// #define PIN_LORA_CIPO 19
// #define PIN_LORA_SCK 18
// #define PIN_LORA_CS 5
// #define PIN_LORA_RST 2
// #define PIN_LORA_DIO0 4

// /*433E6: 433 МГц (часто используется в Европе)
// 868E6: 868 МГц (часто используется в Европе)
// 915E6: 915 МГц (часто используется в Северной Америке)*/
// #define LORA_FREQUENCY 868E6

// //======================================================================//

// int counter = 0;

// //======================================================================//

// void setup()
// {
//     Serial.begin(9600);
//     delay(1500);
//     Serial.println("LoRa Sender");

//     LoRa.setPins(PIN_LORA_CS, PIN_LORA_RST, PIN_LORA_DIO0);
//     // LoRa.setSPIFrequency(20000000);
//     LoRa.setTxPower(20);

//     if (!LoRa.begin(LORA_FREQUENCY))
//     {
//         Serial.println("Starting LoRa failed!");
//         while (1)
//             ;
//     }
//     else
//     {
//         Serial.print("LoRa initialized with frequency ");
//         Serial.println(LORA_FREQUENCY);
//     }
// }

// //======================================================================//

// void loop()
// {
//     Serial.print("Sending packet: ");
//     Serial.println(counter);

//     // send packet
//     LoRa.beginPacket();
//     LoRa.print("Hello LoRa ");
//     LoRa.print(counter);
//     LoRa.endPacket();

//     counter++;

//     delay(1000);
// }