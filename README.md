# Temporizador One Shot com Raspberry Pi Pico W

## 📌 Descrição
Este projeto usa a função `add_alarm_in_ms()` do **Pico SDK** para controlar LEDs acionados por um botão. O ciclo funciona assim:
1. Botão pressionado: **Todos os LEDs acendem**.
2. Após **3s**, um LED desliga.
3. Após **3s**, mais um LED desliga.
4. Após **3s**, o último LED desliga.
5. O botão só pode ser pressionado novamente quando todos os LEDs estiverem apagados.

## 🛠 Componentes
- **Raspberry Pi Pico W**
- **LEDs (Azul, Vermelho, Verde) + Resistores 330Ω**
- **Botão (Pushbutton)**

## 🖥 Simulação
Vídeo demonstrativo: [📹 Clique aqui] (https://youtu.be/gU-vVe90m7o)

## 📜 Como Funciona
- **Interrupção no botão** para acionar os LEDs imediatamente.
- **Temporizador** controla o desligamento progressivo.
- **Debounce por software** evita leituras erradas do botão.

## 🚀 Execução
### Requisitos
- **Pico SDK, CMake, Ninja, Compilador ARM**

## Como Executar
1. Clone este repositório:
   ```bash
   git clone https://github.com/Gilmaiane23/Clock_e_Temporizadores.git
   ```
2. Compile e carregue o código no microcontrolador.

3. Verifique a Atividade a ser executada (se é a atividade 1 ou atividade 2)



