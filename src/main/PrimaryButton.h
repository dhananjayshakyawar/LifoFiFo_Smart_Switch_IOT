/**************************************************************
 * This is a DEMO. You can use it only for development and testing.
 *
 * If you would like to add these features to your product,
 * please contact Blynk for Business:
 *
 *                  http://www.blynk.io/
 *
 **************************************************************/

volatile bool     p_buttonPressed = false;
volatile uint32_t p_buttonPressTime = -1;

void primary_button_action(void)
{
 //ation
  DEBUG_PRINT("Primary buttton action...");
}

void primary_pressed_action(void)
{
 //ation
 DEBUG_PRINT("Primary buttton press action...");
}


ICACHE_RAM_ATTR
void primary_button_change(void)
{
#if PRIMARY_BUTTON_ACTIVE_LOW
  bool buttonState = !digitalRead(PRIMARY_BUTTON_PIN);
#else
  bool buttonState = digitalRead(PRIMARY_BUTTON_PIN);
#endif

  if (buttonState && !p_buttonPressed) {
    p_buttonPressTime = millis();
    p_buttonPressed = true;
    DEBUG_PRINT("Hold the button to reset configuration...");
  } else if (!buttonState && p_buttonPressed) {
    p_buttonPressed = false;
    uint32_t buttonHoldTime = millis() - p_buttonPressTime;
    if (buttonHoldTime >= PRIMARY_BUTTON_HOLD_TIME_ACTION) {
      primary_button_action();
    } else {
      primary_pressed_action();
    }
    p_buttonPressTime = -1;
  }
}

void primary_button_init()
{
#if PRIMARY_BUTTON_ACTIVE_LOW
  pinMode(PRIMARY_BUTTON_PIN, INPUT_PULLUP);
#else
  pinMode(PRIMARY_BUTTON_PIN, INPUT);
#endif
  attachInterrupt(PRIMARY_BUTTON_PIN, primary_button_change, CHANGE);
}

