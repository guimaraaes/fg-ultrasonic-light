class UltrasonicLight : public EmbeddedSystem
{

public:
  ActuatorDigital *light;
  SensorUltrasonicCM *ultrasonic;

  UltrasonicLight(String description, String author)
      : EmbeddedSystem(description, author){};

  void configuration(){};

  void setupES()
  {
    CreatorActuatorDigital *creatorActuatorDigital =
        new CreatorActuatorDigital();
    this->light = creatorActuatorDigital->createComponent(13);

    CreatorUltrasonic *creatorUltrasonic = new CreatorUltrasonic();
    this->ultrasonic = creatorUltrasonic->createComponent(4, 5);
  }

  void loopES()
  {
    float distance = ultrasonic->read();

    if (distance >= 10 && distance <= 30)
    {
      light->write(HIGH);
      delay(1000);
    }
    else
    {
      light->write(LOW);
      delay(1000);
    }
  }

  void runComponentTests()
  {
    light->componentTest();
    ultrasonic->componentTest();
  }
};
UltrasonicLight embeddedSystem = UltrasonicLight("sistema embarcado alerta com luz de acordo com a distância", "Sara Guimarães");
