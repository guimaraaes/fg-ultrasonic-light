
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
## Adicionando o Framework Guimarães, Ultrasonic e Arduino Unit ao Seu Projeto
Após configurar a estrutura básica do seu projeto Arduino com PlatformIO, você pode querer adicionar bibliotecas ou frameworks externos, como o framework Guimarães. Aqui estão os passos para adicionar o código do framework Guimarães ao diretório `lib/` do seu projeto:
 - **Clone via Git**: Se você estiver familiarizado com o Git, pode clonar o repositório diretamente para o diretório `/` do seu projeto PlatformIO usando o comando:
   ```
   git clone https://github.com/guimaraaes/FrameworkGuimaraes.git FrameworkGuimaraes
   ```
   e para o diretório `lib/` do seu projeto PlatformIO usando o comando:
   ```
   https://github.com/ErickSimoes/Ultrasonic.git lib/Ultrasonic
   ```
   e
   ```
   git clone https://github.com/mmurdoch/arduinounit.git lib/ArduinoUnit
   ```
   
 - **ou Download Manual**: Alternativamente, você pode baixar o repositório como um arquivo ZIP e extrair o conteúdo manualmente nas respectivas pastas da clonagem.
