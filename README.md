# Aether-Particles 🌌

**Aether-Particles** é um motor de simulação de partículas de alto desempenho desenvolvido para microcontroladores (ESP32) utilizando o display **ILI9341**. O projeto combina física procedural, integração de hardware via protocolo SPI e interação em tempo real.

O nome remete ao "Quinto Elemento" (Éter), servindo como uma base modular para a criação de diversos efeitos elementais, como fogo, água, fumaça e plasma.

---

## 🚀 Funcionalidades Atuais

- **Simulação de Fogo Procedimental:** Partículas com ciclo de vida, variação de tamanho e degradê de cor térmico.
- **Interação via Hardware:** Suporte a entrada digital (Pushbutton) para efeitos de "Boost" e dispersão lateral.
- **Renderização Otimizada:** Algoritmo de limpeza seletiva de buffers para evitar *flicker* (piscagem) e rastro na tela.
- **Física Dinâmica:** Cálculo de trajetória, velocidade e resistência do ar em tempo real.

---

## 🛠️ Hardware Utilizado

- **Microcontrolador:** ESP32 (NodeMCU-32S ou similar).
- **Display:** TFT LCD ILI9341 (320x240 pixels) com interface SPI.
- **Interação:** 1x Pushbutton.

### Pinagem (Wokwi/Hardware)
| Componente | Pino ESP32 | Função |
| :--- | :--- | :--- |
| **ILI9341 CS** | GPIO 5 | Chip Select |
| **ILI9341 DC** | GPIO 4 | Data/Command |
| **ILI9341 SDI** | GPIO 23 | MOSI (Data) |
| **ILI9341 SCK** | GPIO 18 | Clock |
| **Pushbutton** | GPIO 12 | Input (Pullup) |

---

## 📂 Estrutura do Projeto

No ambiente **Wokwi**, o projeto é composto pelos seguintes arquivos essenciais:

1. `sketch.ino`: O código principal em C++ contendo a lógica do sistema e o loop de renderização.
2. `diagram.json`: Configurações de conexão e layout dos componentes no simulador.
3. `libraries.txt`: Lista de dependências (Adafruit GFX e Adafruit ILI9341).

---

## 🔮 Roadmap (Futuras Implementações)

- [ ] **Módulo Hydrus:** Simulação de fluidos e chuva.
- [ ] **Módulo Aura:** Partículas controladas por sensores de movimento (IMU/Acelerômetro).
- [ ] **Multi-Core Processing:** Utilizar o segundo núcleo do ESP32 para cálculos físicos enquanto o primeiro renderiza.
- [ ] **Configuração Web:** Interface IoT para ajustar cores e gravidade via Wi-Fi.

---

## ✒️ Autor

**Matheus Ferreira** *Software Developer | IoT & Automação Industrial* Focando na convergência entre o hardware industrial e experiências digitais fluidas.

---

## ⚖️ Licença

Este projeto está sob a licença MIT. Consulte o arquivo [LICENSE](LICENSE) para mais detalhes.
