// ------------------------------------------
// LRVent: Last Resort Ventilator Controller
//
// This code is a best attempt at creating a simple, reliable controller
// for the LRVent using a windshield wiper motor to actuate a BVM. This is
// EXPERIMENTAL, UNCERTIFIED, and NOT TESTED ON HUMANS. Use at your own risk.
// The developers take NO RESPONSIBILITY and are NOT LIABLE in any event.
//
// questions? hello@makefastoworkshop.com
// ------------------------------------------

#define SerialLRVent SerialUSB

#define PIN_HEARTBEAT_LED               13

#define PIN_WIPER_MOTOR_FET_PWM_OUTPUT   5
#define PIN_WIPER_MOTOR_REF_GND_OUTPUT   2 // makes wiring simpler

#define PIN_KNOB_RATE_ANA_INPUT         A8
#define PIN_KNOB_RATE_GND_OUTPUT        A9 // makes wiring simpler
#define PIN_KNOB_RATE_VCC_OUTPUT        A7 // makes wiring simpler

#define BREATHING_BPM_MAX               18
#define BREATHING_BPM_MIN                8

//#define BREATHING_PERIOD_MS_MAX      (60000 /  8)
//#define BREATHING_PERIOD_MS_MIN      (60000 / 18)

// ----------

uint32_t      breathingPeriodMillis = 60000 / 13;
unsigned long lastBreathStartMillis = 0;
unsigned long motoMinMillisToCycle  = 1200; // fastest motor can cycle around/2 (to ensure we stay on past wiper switch).
bool          motorIsDriving        = false;

// ----------

void setup() {
  pinMode(PIN_WIPER_MOTOR_FET_PWM_OUTPUT, OUTPUT);
  digitalWrite(PIN_WIPER_MOTOR_FET_PWM_OUTPUT, LOW);
  pinMode(PIN_WIPER_MOTOR_REF_GND_OUTPUT, OUTPUT);
  digitalWrite(PIN_WIPER_MOTOR_REF_GND_OUTPUT, LOW);
  // --
  pinMode(PIN_KNOB_RATE_ANA_INPUT, INPUT);
  pinMode(PIN_KNOB_RATE_GND_OUTPUT, OUTPUT);
  digitalWrite(PIN_KNOB_RATE_GND_OUTPUT, LOW);
  pinMode(PIN_KNOB_RATE_VCC_OUTPUT, OUTPUT);
  digitalWrite(PIN_KNOB_RATE_VCC_OUTPUT, HIGH);
  // --
  pinMode(PIN_HEARTBEAT_LED, OUTPUT);
  // --
  analogReadResolution(10); // 10 bits --> analog values will be [0,1023]
  // --
  SerialLRVent.begin(115200);
  // while (!SerialLRVent); 
  // --
  delay(2000);
  SerialLRVent.println("LRVent Running...");
  // --
  adjustParamsBasedOnKnobs();
}

uint16_t readRateValPercent() {
  int valSum = 0;
  for (int i = 0; i < 16; i++) {
    valSum += analogRead(PIN_KNOB_RATE_ANA_INPUT);
  }
  uint16_t pctVal  = (valSum * 100 / 1024) / 16;
  return pctVal;
}

void adjustParamsBasedOnKnobs() {
  uint16_t rateVal  = readRateValPercent();
  // --
  // this param should adjust slowly to limit unintended changes due to noise.
  uint32_t breathingPeriodMillisNew = 60000 / (BREATHING_BPM_MIN + (float)rateVal*(BREATHING_BPM_MAX-BREATHING_BPM_MIN)/100.0);
  int diff = breathingPeriodMillisNew - breathingPeriodMillis;
  if(diff >  10) diff =  10;
  if(diff < -10) diff = -10;
  breathingPeriodMillis += diff;
}

unsigned long loopFrame = 0;
void loop() {
  unsigned long nowMillis = millis();
  // --
  if (!motorIsDriving && (nowMillis - lastBreathStartMillis >= breathingPeriodMillis)) {
    digitalWrite(PIN_WIPER_MOTOR_FET_PWM_OUTPUT, HIGH);
    motorIsDriving        = true;
    lastBreathStartMillis = nowMillis;
  } else if (nowMillis - lastBreathStartMillis < motoMinMillisToCycle) {
    // motor stays on at least motoMinMillisToCycle... do nothing.
  } else {
    // motor has driven at least the min cycle time, but not ready to cycle again.
    if (motorIsDriving) {
      digitalWrite(PIN_WIPER_MOTOR_FET_PWM_OUTPUT, LOW);
      motorIsDriving = false;
    }
  }
  // --
  adjustParamsBasedOnKnobs();
  delay(5); // rate-limit the loop to reduce read errors if we get a noise spike
  // --
  if(loopFrame%300 == 0)        digitalWrite(PIN_HEARTBEAT_LED, HIGH);
  else if(loopFrame%300 == 150)  digitalWrite(PIN_HEARTBEAT_LED, LOW);
  // --
  if(loopFrame%50 == 1){
    SerialLRVent.println(60000.0 / breathingPeriodMillis, DEC);
  }
  // --
  loopFrame++;
}
