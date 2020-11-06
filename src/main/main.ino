
//#define USE_SPARKFUN_BLYNK_BOARD    // Uncomment the board you are using
#define USE_NODE_MCU_BOARD        // Comment out the boards you are not using
//#define USE_WITTY_CLOUD_BOARD
//#define USE_CUSTOM_BOARD          // For all other ESP8266-based boards -
                                    // see "Custom board configuration" in Settings.h

#define APP_DEBUG        // Comment this out to disable debug prints

//#define BLYNK_SSL_USE_LETSENCRYPT   // Comment this out, if using public Blynk Cloud

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#include "BlynkProvisioning.h"


WidgetTerminal terminal(V1);

void setup() {
  delay(100);
  Serial.begin(BAUD_RATE);

  BlynkProvisioning.begin();

    // Clear the terminal content
  terminal.clear();

  // This will print Blynk Software version to the Terminal Widget when
  // your hardware gets connected to Blynk Server
  terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.println(F("-------------"));
  terminal.println(F("Type 'Marco' and get a reply, or type"));
  terminal.println(F("anything else and get it printed back."));
  terminal.flush();

}

BLYNK_WRITE(V1)
{

  // if you type "Marco" into Terminal Widget - it will respond: "Polo:"
  if (String("Marco") == param.asStr()) {
    terminal.println("You said: 'Marco'") ;
    terminal.println("I said: 'Polo'") ;
  } else {

    // Send it back
    terminal.print("You said:");
    terminal.write(param.getBuffer(), param.getLength());
    terminal.println();
  }

  // Ensure everything is sent
  terminal.flush();
}

void loop() {
  // This handles the network and cloud connection
  BlynkProvisioning.run();
}

