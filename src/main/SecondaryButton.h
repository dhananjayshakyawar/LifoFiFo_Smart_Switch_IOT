/**************************************************************
 * This is a DEMO. You can use it only for development and testing.
 *
 * If you would like to add these features to your product,
 * please contact Blynk for Business:
 *
 *                  http://www.blynk.io/
 *
 **************************************************************/

volatile bool     s_buttonPressed = false;
volatile uint32_t s_buttonPressTime = -1;

void secondary_button_action(void)
{
 //ation
  DEBUG_PRINT("Secondary buttton action...");
}

void secondary_pressed_action(void)
{
 //ation
 DEBUG_PRINT("Secondary buttton press action...");
}


ICACHE_RAM_ATTR
void secondary_button_change(void)
{
#if SECONDARY_BUTTON_ACTIVE_LOW
  bool buttonState = !digitalRead(SECONDARY_BUTTON_PIN);
#else
  bool buttonState = digitalRead(SECONDARY_BUTTON_PIN);
#endif

  if (buttonState && !s_buttonPressed) {
    s_buttonPressTime = millis();
    s_buttonPressed = true;
    DEBUG_PRINT("Hold the button to reset configuration...");
  } else if (!buttonState && s_buttonPressed) {
    s_buttonPressed = false;
    uint32_t buttonHoldTime = millis() - s_buttonPressTime;
    if (buttonHoldTime >= SECONDARY_BUTTON_HOLD_TIME_ACTION) {
      secondary_button_action();
    } else {
      secondary_pressed_action();
    }
    s_buttonPressTime = -1;
  }
}

void secondary_button_init()
{
#if SECONDARY_BUTTON_ACTIVE_LOW
  pinMode(SECONDARY_BUTTON_PIN, INPUT_PULLUP);
#else
  pinMode(SECONDARY_BUTTON_PIN, INPUT);
#endif
  attachInterrupt(SECONDARY_BUTTON_PIN, secondary_button_change, CHANGE);
}

