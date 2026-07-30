<p align="center">
  <a href="#english">🇺🇸 English</a> | 
  <a href="#portugues">🇧🇷 Português</a>
</p>

---
<a name="english" id="english"></a>

# Robotic Hand - C Prototype Project

**Federal University of Uberlândia - UFU**

**Course/Subject: Procedural Programming**

---
## About the Project

This project consists of the development and control of a **robotic hand** driven by servo motors, using the **C** programming language. The goal is to simulate human finger movements through commands programmed or sent via serial interface.

---

## 👥 Group Members

* **Ana Luísa Cardoso de Matos** - ID: `12521EBI036`
* **Ana Júlia Freitas Resende** - ID: `12521EBI006`
* **Camila Franco Borges** - ID: `12521EBI026`
* **Larissa Araújo Lima** - ID: `12511EBI008`
* **Vinícius Santos Nímia** - ID: `12521EBI022`
---

## 🛠️ Components Used

| Component | Quantity | Description |
| :--- | :---: | :--- |
| **Microcontroller** | 1 | ESP32-Wrover |
| **Servo Motors** | 1 | *TAL* servos for finger control |
| **Power Supply** | 1 | 5V external power supply |
| **3D Structure** | 1 | PLA/ABS printed hand |
| **Wires / Jumper Wires** | - | Signal and power connections |

---

## 📸 Gallery and Mechanism of Action

Below are images of the 3D printed robotic hand (based on the *InMoov* open-source project), highlighting the mechanical cable/tendon actuation system.

| Palmar View (Front) | Dorsal View (Back) |
| :---: | :---: |
| ![Robotic Hand - Front](mao_frente.jpeg) | ![Robotic Hand - Back](mao_costas.jpeg) |

### 🔍 Mechanical Explanation

1. **Tendon Actuation (Nylon Wires/Cords):**
   * The hand uses an **artificial tendon** system (black wires guided by internal channels printed inside the phalanges).
   * **Flexion (Closing fingers):** Each finger has a cable running along the palmar side. When pulled by a servo motor at the base/forearm, the wire tightens and bends the finger joints.
   * **Extension (Opening fingers / Return):** As seen in the dorsal view, elastic/lock cords are anchored to the back of the hand. They provide the necessary retraction tension for the finger to return to the extended position when the servo relaxes the main cable.

2. **3D Printed Structure:**
   * **Material:** PLA/ABS parts divided into distal, middle, and proximal phalanges, connected by pins or flexible joints.
   * **Cable Routing:** The holes on the palm and back of the hand act as guides (grommets/pass-throughs) to reduce friction and maintain the alignment of the steel/nylon cables during movement.

---

## ⚙️ System Architecture and Operation

The robotic hand control uses a **Master-Slave (Transmitter/Receiver)** architecture with wireless communication via the **MQTT protocol** over a Wi-Fi network. The system consists of two **ESP32** microcontrollers working synchronously:

1. **ESP32 #1 (Transmitter / Remote Control):** Reads physical user inputs through pushbuttons and sends commands via Wi-Fi to the MQTT broker.
2. **ESP32 #2 (Receiver / Hand Actuator):** Subscribes to the MQTT broker topic, receives commands in real time, and drives the stepper motor using the A4988 driver.

---

## 💻 C/C++ Code Explanation (`.ino`)

### 📤 1. Transmitter Code (`first.ino`) — ESP32 #1
This code handles the user input interface.

* **Wi-Fi and MQTT Connection:** Connects to the configured Wi-Fi network and establishes a link with the public broker `broker.hivemq.com`.
* **Button Reading:** Uses pins `GPIO 4` and `GPIO 5` with internal pull-up resistors (`INPUT_PULLUP`) to detect button presses.
* **Message Publishing:**
  * **Press Close:** Publishes the string `"FECHAR"` to the topic `projeto/mao/comando`.
  * **Press Open:** Publishes the string `"ABRIR"` to the topic `projeto/mao/comando`.
  * **No button pressed:** Publishes the string `"PARAR"` to stop any movement.

```cpp
// Main loop snippet for reading buttons and sending commands
bool estadoAbrir  = (digitalRead(btnAbrir) == LOW);
bool estadoFechar = (digitalRead(btnFechar) == LOW);

if (estadoFechar && !estadoAbrir) {
    client.publish("projeto/mao/comando", "FECHAR");
} else if (estadoAbrir && !estadoFechar) {
    client.publish("projeto/mao/comando", "ABRIR");
} else {
    client.publish("projeto/mao/comando", "PARAR");
}

---
<a name="portugues" id="portugues"></a>

# Mão Robótica  - Projeto de Protótipo em C

**Universidade Federal de Uberlândia - UFU**

**Disciplina: Programação Procedimental**

---
## Sobre o Projeto

Este projeto consiste no desenvolvimento e controle de uma **mão robótica** acionada por servomotores, utilizando a linguagem **C**. O objetivo é simular os movimentos dos dedos humanos através de comandos programados/enviados via interface serial.

---

## 👥 Integrantes do Grupo

* **Ana Luísa Cardoso de Matos** - Matrícula: `12521EBI036`
* **Ana Júlia Freitas Resende** - Matrícula: `12521EBI006`
* **Camila Franco Borges** - Matrícula: `12521EBI026`
* **Larissa Araújo Lima** - Matrícula: `12511EBI008`
* **Vinícius Santos Nímia** - Matrícula: `12521EBI022`
---

## 🛠️ Componentes Utilizados

| Componente | Quantidade | Descrição |
| :--- | :---: | :--- |
| **Microcontrolador** | 1 | ESP32-Wrover |
| **Servomotores** | 1 | Servos *TAL* para controle dos dedos |
| **Fonte de Alimentação** | 1 | Fonte externa de 5V |
| **Estrutura 3D** | 1 | Mão impressa em PLA/ABS |
| **Fios / Jumper Wire** | - | Conexões de sinal e alimentação |

---

## 📸 Galeria e Mecanismo de Ação

Abaixo estão as imagens da mão robótica impressa em 3D (baseada no projeto open-source *InMoov*), destacando o sistema de atuação mecânica por fios/tendões.

| Visão Palmar (Frente) | Visão Dorsal (Costas) |
| :---: | :---: |
| ![Mão Robótica - Frente](mao_frente.jpeg) | ![Mão Robótica - Costas](mao_costas.jpeg) |

### 🔍 Explicação Mecânica

1. **Atuação por Tendões (Fios de Nylon/Cordões):**
   * A mão utiliza um sistema de **tendões artificiais** (fios pretos guiados por canais internos impressos nas falanges).
   * **Flexão (Fechar os dedos):** Cada dedo possui um fio passando pela parte palmar. Quando puxado por um servomotor na base/antebraço, o fio tensiona e dobra as articulações do dedo.
   * **Extensão (Abrir os dedos / Retorno):** Como visto na visão dorsal, há cordões elásticos/trava ancorados na parte posterior da mão. Eles fornecem a tensão de retração necessária para que o dedo volte à posição estendida quando o servo relaxa o fio principal.

2. **Estrutura Impressa em 3D:**
   * **Material:** Peças em PLA/ABS divididas em falanges distal, média e proximal, conectadas por pinos ou encaixes flexíveis.
   * **Roteamento de Cabos:** Os furos na palma e no dorso da mão atuam como guias (passa-cabos) para reduzir o atrito e manter o alinhamento dos cabos de aço/nylon durante o movimento.
---

## ⚙️ Arquitetura e Funcionamento do Sistema

[cite_start]O controle da mão robótica utiliza uma arquitetura **Mestre-Escravo (Transmissor/Receptor)** com comunicação sem fio via **protocolo MQTT** através de uma rede Wi-Fi[cite: 1, 24]. [cite_start]O sistema é composto por dois microcontroladores **ESP32** atuando de forma síncrona[cite: 10, 26]:

1. [cite_start]**ESP32 #1 (Transmissor / Controle Remoto):** Lê os comandos físicos através de botões e envia mensagens via Wi-Fi para o broker MQTT[cite: 25, 29, 32].
2. [cite_start]**ESP32 #2 (Receptor / Atuador da Mão):** Se inscreve no tópico do broker MQTT, recebe os comandos em tempo real e acciona o motor de passo através do driver A4988[cite: 4, 7, 11].

---

## 💻 Explicação dos Códigos C/C++ (`.ino`)

### 📤 1. Código Transmissor (`first.ino`) — ESP32 #1
Este código é responsável pela interface de entrada do usuário.

* [cite_start]**Conexão Wi-Fi e MQTT:** Conecta-se à rede Wi-Fi configurada e se vincula ao broker público `broker.hivemq.com`[cite: 1, 24, 29].
* [cite_start]**Leitura dos Botões:** Utiliza os pinos `GPIO 4` e `GPIO 5` com resistor de pull-up interno (`INPUT_PULLUP`) para detectar o acionamento dos botões[cite: 25, 28].
* **Envio de Mensagens:**
  * [cite_start]**Pressionar Fechar:** Publica a string `"FECHAR"` no tópico `projeto/mao/comando`[cite: 32].
  * [cite_start]**Pressionar Abrir:** Publica a string `"ABRIR"` no tópico `projeto/mao/comando`[cite: 33, 34].
  * [cite_start]**Nenhum botão pressionado:** Publica a string `"PARAR"` para cessar qualquer movimento[cite: 34].

```cpp
// Trecho principal da leitura e envio no loop
bool estadoAbrir  = (digitalRead(btnAbrir) == LOW);
bool estadoFechar = (digitalRead(btnFechar) == LOW);

if (estadoFechar && !estadoAbrir) {
    client.publish("projeto/mao/comando", "FECHAR");
} else if (estadoAbrir && !estadoFechar) {
    client.publish("projeto/mao/comando", "ABRIR");
} else {
    client.publish("projeto/mao/comando", "PARAR");
}
```

---

### 📥 2. Código Receptor (`second.ino`) — ESP32 #2
Este código é responsável pela recepção dos comandos e acionamento do motor de passo.

* [cite_start]**Assinatura de Tópico (Subscribe):** Assim que se conecta ao broker MQTT, se inscreve no tópico `projeto/mao/comando` para receber as mensagens enviadas pelo ESP32 #1[cite: 11].
* [cite_start]**Função Callback:** Sempre que uma nova mensagem chega via MQTT, a função `callback()` extrai a string (`"ABRIR"`, `"FECHAR"` ou `"PARAR"`) e atualiza a variável `comandoAtual`[cite: 7, 9].
* [cite_start]**Mecanismo de Segurança (Timeout):** Se o ESP32 #2 não receber mensagens por mais de 300 milissegundos, o estado é forçado para `"PARAR"` para evitar acionamentos contínuos acidentais[cite: 17, 18].
* **Controle do Driver A4988 (Motor de Passo):**
  * [cite_start]**Pino `DIR` (`GPIO 19`):** Define o sentido da rotação do motor (`HIGH` para abrir, `LOW` para fechar)[cite: 4, 18, 20].
  * **Pino `STEP` (`GPIO 18`):** Envia pulsos de onda quadrada para dar os passos do motor. [cite_start]A frequência do pulso é determinada pela variável `velocidade` (2500 µs)[cite: 4, 5, 19, 21].

```cpp
// Trecho de acionamento do motor de passo via Driver A4988
if (comandoAtual == "FECHAR") {
    digitalWrite(pinDir, LOW);   // Define a direção (Fechar)
    digitalWrite(pinStep, HIGH); // Início do pulso
    delayMicroseconds(2500);
    digitalWrite(pinStep, LOW);  // Fim do pulso
    delayMicroseconds(2500);
}
```

---

## 🔄 Fluxo de Funcionamento Passo a Passo

1. [cite_start]**Inicialização:** Ambos os ESP32 inicializam a comunicação Serial, conectam-se ao Wi-Fi local e estabelecem vínculo com o broker MQTT[cite: 1, 9, 11, 15, 24, 28, 29].
2. [cite_start]**Entrada:** O usuário pressiona o botão de **Fechar** no ESP32 #1[cite: 25, 31, 32].
3. [cite_start]**Transmissão:** O ESP32 #1 envia o texto `"FECHAR"` para a nuvem via MQTT[cite: 32].
4. [cite_start]**Recepção:** O ESP32 #2 recebe o pacote em milissegundos via Wi-Fi[cite: 7, 8].
5. [cite_start]**Ação:** O ESP32 #2 altera o sinal do pino `DIR` e começa a enviar pulsos no pino `STEP`, tracionando os cabos/tendões da mão até que o botão seja solto[cite: 18, 19, 20].
