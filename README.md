# Projet : Affichage OLED avec ESP32 et Bouton

## Description
Ce projet utilise un écran OLED I2C 128x64 connecté à un ESP32 pour afficher un message en fonction de l'état d'un bouton poussoir. Lorsque le bouton est pressé, le message change dynamiquement sur l'écran.

## Matériel requis
- ESP32 DevKit V1
- Écran OLED 128x64 avec interface I2C (SSD1306)
- Bouton poussoir
- Résistances de pull-up (optionnel si `INPUT_PULLUP` est utilisé)
- Câbles de connexion

## Schéma de connexion
| Composant  | ESP32 Pin |
|------------|----------|
| OLED SDA   | GPIO 21  |
| OLED SCL   | GPIO 22  |
| Bouton     | GPIO 27  |

## Bibliothèques nécessaires
Avant de compiler le code, assure-toi d'installer les bibliothèques suivantes dans l'IDE Arduino :
- `Adafruit_GFX`
- `Adafruit_SSD1306`
- `Wire`
- `SPI`

Tu peux les installer via le gestionnaire de bibliothèques de l'IDE Arduino.

## Code source
```cpp
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

#define i2_adrr 0x3C
#define columns 128
#define rows 64
const int btn_1 = 27;
bool etat = false;

Adafruit_SSD1306 display(columns, rows, &Wire, -1);

void setup() {
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, i2_adrr)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  pinMode(btn_1, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(btn_1) == LOW) {
    etat = !etat;
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(etat ? "le btn est appuyé" : "le btn pas appuyé");
  display.display();
}
```

## Explication du Code
1. **Initialisation de l'écran OLED**
   - Configuration via I2C (adresse `0x3C`)
   - Effacement de l'écran après l'initialisation
2. **Lecture du bouton poussoir**
   - Utilisation du mode `INPUT_PULLUP` pour éviter une résistance externe
   - Inversion de l'état de la variable `etat` lorsque le bouton est pressé
3. **Mise à jour de l'affichage**
   - Affiche "le btn est appuyé" si le bouton est pressé
   - Affiche "le btn pas appuyé" sinon

## Fonctionnement
- Lorsque tu appuies sur le bouton connecté à GPIO 27, l'écran OLED affiche "le btn est appuyé".
- Lorsque tu relâches le bouton, l'affichage revient à "le btn pas appuyé".

## Améliorations possibles
- Ajouter un **délai anti-rebond** pour éviter les erreurs de détection rapide du bouton.
- Utiliser une **interruption matérielle** pour améliorer la réactivité.
- Afficher un **compteur de pressions** sur l'écran OLED.

## Auteur
Paul Jacotin

