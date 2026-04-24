#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#define TFT_DC 4
#define TFT_CS 5
#define BTN_PIN 12

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

struct Particle {
  float x, y;
  float vx, vy;
  int life;
  int maxLife;
  int lastSize; // Guarda o tamanho anterior para apagar corretamente
};

const int MAX_PARTICLES = 100; 
Particle particles[MAX_PARTICLES];

void setup() {
  pinMode(BTN_PIN, INPUT_PULLUP);
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);

  for (int i = 0; i < MAX_PARTICLES; i++) {
    particles[i].life = 0;
    particles[i].lastSize = 0;
  }
}

uint16_t getFireColor(int life, int maxLife) {
  float ratio = (float)life / maxLife;
  if (ratio > 0.7) return ILI9341_WHITE;
  if (ratio > 0.4) return 0xFD20; // Laranja
  if (ratio > 0.1) return ILI9341_RED;
  return 0x2000; // Cinza/Vermelho muito escuro
}

void loop() {
  bool isPressed = (digitalRead(BTN_PIN) == LOW);

  // 1. SPAWN
  int spawnCount = isPressed ? 5 : 2;
  for (int s = 0; s < spawnCount; s++) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
      if (particles[i].life <= 0) {
        particles[i].x = tft.width() / 2 + random(-10, 10);
        particles[i].y = tft.height() - 10;
        
        float horizontalSpread = isPressed ? 5.0f : 1.5f;
        particles[i].vx = (random(-100, 100) / 100.0f) * horizontalSpread;
        
        float verticalPush = isPressed ? -8.0f : -4.0f;
        particles[i].vy = verticalPush + (random(-20, 0) / 10.0f);
        
        particles[i].maxLife = isPressed ? random(30, 70) : random(20, 40);
        particles[i].life = particles[i].maxLife;
        break;
      }
    }
  }

  // 2. UPDATE E RENDER
  for (int i = 0; i < MAX_PARTICLES; i++) {
    if (particles[i].life > 0) {
      // APAGA a posição anterior usando o tamanho que ela TINHA
      tft.fillRect((int)particles[i].x, (int)particles[i].y, particles[i].lastSize, particles[i].lastSize, ILI9341_BLACK);

      // ATUALIZA FÍSICA
      particles[i].x += particles[i].vx;
      particles[i].y += particles[i].vy;
      particles[i].life--;

      // DEFINE NOVO TAMANHO
      int currentSize = (particles[i].life > 20) ? (isPressed ? 5 : 3) : 1;
      particles[i].lastSize = currentSize; // Salva para a próxima limpeza

      // DESENHA SE AINDA VIVA
      if (particles[i].life > 0) {
        // Garante que não saia da tela ao desenhar quadrados grandes
        if (particles[i].x > 0 && particles[i].x < tft.width() - currentSize &&
            particles[i].y > 0 && particles[i].y < tft.height() - currentSize) {
          
          uint16_t color = getFireColor(particles[i].life, particles[i].maxLife);
          tft.fillRect((int)particles[i].x, (int)particles[i].y, currentSize, currentSize, color);
        } else {
          particles[i].life = 0; // Mata a partícula se sair da borda
        }
      }
    }
  }

  // Opcional: Redesenha a borda apenas quando pressionado para evitar rastro na borda
  if (isPressed) {
    tft.drawRect(0, 0, tft.width(), tft.height(), 0xFD20);
  } else {
    // Limpa a borda se ela existir
    tft.drawRect(0, 0, tft.width(), tft.height(), ILI9341_BLACK);
  }

  delay(5); // Delay menor para compensar o processamento do ESP32
}
