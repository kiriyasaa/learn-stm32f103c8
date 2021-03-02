#include <Arduino.h>
#include <string.h>

class Button
{
private:
  char m_current_button{};

public:
  Button(char);
  ~Button();
  int getValue();
};

Button::Button(char button)
{
  m_current_button = button;
}

Button::~Button()
{
  SerialUSB.println("Destructor Button");
}

int Button::getValue()
{
  return this->m_current_button;
}

void setup()
{
  SerialUSB.println("Enter void setup()");
  pinMode(PC13, OUTPUT);
  SerialUSB.begin(115200);
  Button a(0x11);
  Button d(0x64);
  Button s(0x73);
  Button w(0x77);
  uint8_t count{0};
  while (true)
  {
    int serial_result{SerialUSB.read()};
    if (serial_result == a.getValue())
    {
      digitalToggle(PC13);
      SerialUSB.println("\rHello World!" + static_cast<String>(count));
      count += 1;
    }
    if (serial_result == s.getValue())
    {
      break;
    }
    count == 254 ? count = 0 : count = count;
  }
  SerialUSB.println("End of void setup()");
  digitalWrite(PC13, HIGH);
  SerialUSB.println("Reseting Arduino simulation.");
}

void loop()
{
  setup();
}
