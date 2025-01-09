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

// test(testeUltrasonico40cm_LuzDesligada)
// {
//     systemTests.enter("Teste ultrassonico 40 cm e Led LOW"); // Log sistema
//     assertTrue(embeddedSystem.ultrasonic->behavior->isComponentInValue(40, 5, SearchType::NEXT));
//     assertTrue(embeddedSystem.light->behavior->isComponentInValue(LOW, SearchType::NEXT));
//     systemTests.exit(); // Limpeza histórico
// }

test(testeUltrasonico20cm_LuzLigada)
{
    systemTests.enter("Teste ultrassonico 20 cm e Led HIGH"); // Log sistema
    assertTrue(embeddedSystem.ultrasonic->behavior->isComponentInValue(20, 5, SearchType::NEXT));
    assertTrue(embeddedSystem.light->behavior->isComponentInValue(HIGH, SearchType::NEXT));
    systemTests.exit(); // Limpeza histórico
}
