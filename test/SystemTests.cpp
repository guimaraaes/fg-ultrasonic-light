#include "../lib/ArduinoUnit/src/ArduinoUnit.h"

class UltrasonicLightSystemTests : public SystemTests
{
public:
    UltrasonicLightSystemTests(){};

    void enter(String name)
    {
        Serial.println(name);
        delay(10000);
        setup();
        embeddedSystem.loopES();
        history->getHistory();
    };

    void exit()
    {
        history->list.clear();
    };

    void run()
    {
        Test::run();
    }
};

UltrasonicLightSystemTests systemTests = UltrasonicLightSystemTests();

test(test_0to30)
{
    systemTests.enter("test_0to30");
    assertTrue(embeddedSystem.ultrasonic->behavior->raiseSensorViVf(0, 30));
    assertTrue(embeddedSystem.light->behavior->isActuatorLow());
    systemTests.exit();
}
