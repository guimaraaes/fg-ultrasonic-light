
# ultrasonic-light

## Elicitar requisitos

<img  src="https://github.com/guimaraaes/fg-ultrasonic-light/blob/main/assets/requisitos.png" width="100%" height="100%">

## Plano de Teste 

Na etapa de plano de teste, temos: 

- Definir o caso de teste usando BDD para especificar o **Contexto** do caso de teste e as condições de **Dado**, **Quando** e **Então**.
- O critério de parada fica por decisão do desenvolvedor.


## Esquemático do circuito eletrônico

<img  src="https://github.com/guimaraaes/fg-ultrasonic-light/blob/main/assets/esquematico-circuito.png" width="30%" height="30%">

## Arquitetura do projeto
Ao criar o projeto com o PlatformIO, a estrutura do projeto deve ser atualizada para a seguinte:

```
.
├── EmbeddedSystem          # System code with: configuration, setup, loop and component tests 
├── lib                     # ArduinoUnit lib and others needed
├── src                     # Source files 
├── test                    # System tests 
└── README.md               # Documentation
```

## Códificação do SE

Em `EmbeddedSystem/EmbeddedSystem.cpp` temos a classe `UltrasonicLight` com o funcionamento do sistema através da definição de:

- Instâncias dos componentes (sem configuração dos pinos);
- Método construtor `UltrasonicLight` para receber a descrição e o nome do autor do sistema (ao final da classe é criada a instância `embeddedSystem` com essas informações);
- Método de `configuration` (não aplicado nesse exemplo);
- Método `setupES` para criar os componentes com a configuração dos pinos com instâncias das classes de criação;
- Método `loopES` para implementar a lógica de controle;
- Método `runComponentTests` para testar os componentes.

```
class UltrasonicLight : public EmbeddedSystem
{

  public:
    ActuatorDigital *light;
    SensorUltrasonicCM *ultrasonic;

    UltrasonicLight(String description, String author) : EmbeddedSystem(description, author){};
    void configuration(){};

    void setupES()
    {
        ...
    };
    
    void loopES()
    {
        ...
    };

    void runComponentTests()
    {
        ...
    }
};

UltrasonicLight embeddedSystem = UltrasonicLight("sistema embarcado alerta com luz de acordo com a distância", "Sara Guimarães");
```

### setupES

- Método `setupES` para criar os componentes com a configuração dos pinos com instâncias das classes de criação;

```
    void setupES()
    {
        CreatorActuatorDigital *creatorActuatorDigital = new CreatorActuatorDigital();
        this->light = creatorActuatorDigital->createComponent(13);
    
        CreatorUltrasonic *creatorUltrasonic = new CreatorUltrasonic();
        this->ultrasonic = creatorUltrasonic->createComponent(4, 5);
    };
```

### loopES

- Método `loopES` para implementar a lógica de controle;

```
    void loopES()
    {
      float distance = ultrasonic->read();
  
      if (distance < 30)
      {
        light->write(LOW);
        delay(1000);
      }
      if (distance >= 30)
      {
        light->write(HIGH);
        delay(1000);
      }
    };
```

### runComponentTests

- Método `runComponentTests` para testar os componentes.

```
    void runComponentTests()
    {
        ultrasonic->componentTest();
        light->componentTest();
    }
```
Todos os componentes são testados através de interação com o desenvolvedor. A seguir são descritas as mensagens padrão enviadas pelo terminal para que o desenvolvedor valide se o componente está funcionando corretamente ou não.

#### Componente tipo sensor

```
Iniciando teste de componente no pino $PIN
--- Coloque em 10 segundos o componente com o valor $VALUE
--- Valor lido $NAME_SENSOR: $VALUE_READED
--- Resultado do teste de componente: você deve afirmar. Aguarde para responder.
---- Valor esperado $VALUE_EXPECTED
---- Valor lido $VALUE_READED
```

#### Componente tipo atuador

```
Iniciando teste de componente no pino $PIN
--- Verifique se em 2 segundos o componente está durante 10 segundos com o valor $VALUE
--- Resultado do teste de componente: você deve afirmar. Aguarde para responder.
```

## Códificação do SystemTests 
Em `test/SystemTests.cpp` temos a classe `UltrasonicLightSystemTests` com o funcionamento do sistema através da definição de:

- Componentes;
- Método construtor `UltrasonicLightSystemTests` (ao final da classe é criada a instância `systemTests`);
- Método de `enter` executar o funcionamento do sistema e salvar as interações em um histórico;
- Método `exit` limpar o histórico;
- Método `run` executar todos os casos de teste.

Os métodos `enter` e `exit` são executados no início e no final de cada caso de teste, respectivamente.

```
class UltrasonicLightSystemTests : public SystemTests
{
    public:
        UltrasonicLightSystemTests(){};
        void enter(String name)
        {
            Serial.println(name);
            delay(5000);
            setup();
            embeddedSystem.loopES();
            history->getHistory();
        };

        void exit()
        {
            history->list->clear();
        };

        void run()
        {
            Test::run();
        }
};

UltrasonicLightSystemTests systemTests = UltrasonicLightSystemTests();
```
### Casos de teste

Cada caso de teste é resultado da tradução do caso gerado com BDD para uma implementação em C++ com o Framework Guimarães.

#### Caso 1: teste para luz em estado desligado

- No BDD analisando o RF 1.2 no Diagrama de Requisitos podemos obter:
  - **Contexto**: O sistema está operacional e o ultrassônico medindo menos de 30 cm
  - **Dado** que o sistema está funcionando corretamente
  - **Quando** o ultrassônico mediu 15 cm
  - **Então** o LED deve estar apagado


- Com o Framework Guimarães

```
test(test_0to30)
{
    systemTests.enter("test_0to30");
    assertTrue(embeddedSystem.ultrasonic->behavior->raiseSensorViVf(0, 30));
    assertTrue(embeddedSystem.light->behavior->isActuatorLow());
    systemTests.exit();
}
```

#### Caso 2: teste para luz em estado ligado

- No BDD analisando o RF 1.1 no Diagrama de Requisitos podemos obter:
  - **Contexto**: O sistema está operacional e o ultrassônico medindo mais de 30 cm
  - **Dado** que o sistema está funcionando corretamente
  - **Quando** o ultrassônico mediu 35 cm
  - **Então** o LED deve estar ligado


- Com o Framework Guimarães

```
test(test_30toLarger)
{
    systemTests.enter("test_30toLarger");
    assertTrue(embeddedSystem.ultrasonic->behavior->raiseSensorViVf(30, 400));
    assertTrue(embeddedSystem.light->behavior->isActuatorHigh());
    systemTests.exit();
}
```


## Arquivo main
O projeto pode atuar em três ambientes distintos:
- Criação (`CREATE_ENVIROMENT`): Apenas o arquivo `EmbeddedSystem/EmbeddedSystem.cpp` com a lógica de funcionamento do arduino é executado;
- Testes de componente (`COMPONENT_TESTS_ENVIROMENT`): Apenas os testes de componentes do método `runComponentTests` do arquivo `EmbeddedSystem/EmbeddedSystem.cpp` são executados;
- Testes do sistema (`SYSTEM_TESTS_ENVIROMENT`): Apenas os testes de sistema são executados do arquivo `test/SystemTests.cpp`.

No aquivo `src/main.cpp` é definido o ambiente de execução. Apenas um `define` deve estar ativo por vez:

```
#define CREATE_ENVIROMENT
// #define COMPONENT_TESTS_ENVIROMENT
// #define SYSTEM_TESTS_ENVIROMENT
```

A seguir são incluídas as bibliotecas necessárias para execução do projeto:

```
#include <Arduino.h>

#include "../lib/FrameworkGuimaraes/FrameworkGuimaraes.h"

#include "../EmbeddedSystem/EmbeddedSystem.cpp"
#include "../lib/Ultrasonic/src/Ultrasonic.h"

#ifdef SYSTEM_TESTS_ENVIROMENT
#include "../test/SystemTests.cpp"
#endif
```

Seguindo com o método `setup` (todos os ambientes precisam do setup do embeddedSystem para execução):

```
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  embeddedSystem.setupES();
}
```

Por fim, a execução em `loop` do ambiente definido:

```
void loop()
{
// put your main code here, to run repeatedly:
#ifdef CREATE_ENVIROMENT
  embeddedSystem.loopES();
#endif

#ifdef COMPONENT_TESTS_ENVIROMENT
  embeddedSystem.runComponentTests();

#endif

#ifdef SYSTEM_TESTS_ENVIROMENT
  systemTests.run();
#endif
}
```
