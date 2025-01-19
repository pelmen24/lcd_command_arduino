#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

// Указываем адрес I2C и размеры дисплея (например, 16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Функция для анимации набора текста
void typeText(int row, const String& text, int delayMs) {
  lcd.setCursor(0, row);
  for (int i = 0; i < text.length(); i++) {
    lcd.print(text[i]);
    delay(delayMs);
  }
}

void setup() {
  lcd.init();         // Инициализация LCD
  lcd.backlight();    // Включить подсветку
  lcd.blink();        // Включить мигающий курсор
  Serial.begin(9600); // Инициализация последовательного порта
}

void loop() {
  // Проверяем, есть ли данные в последовательном порту
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); // Считываем строку до символа '\n'

    // Проверяем команду на начало с "code.lcd.disp"
    if (command.startsWith("code.lcd.disp")) {
      // Ищем текст для r1 и r2
      int r1Start = command.indexOf("r1:\"") + 4;
      int r1End = command.indexOf("\"", r1Start);
      int r2Start = command.indexOf("r2:\"") + 4;
      int r2End = command.indexOf("\"", r2Start);

      // Если оба текста найдены, обрабатываем их
      if (r1Start > 3 && r1End > r1Start && r2Start > 3 && r2End > r2Start) {
        String line1 = command.substring(r1Start, r1End);
        String line2 = command.substring(r2Start, r2End);

        lcd.clear(); // Очищаем экран

        // Проверяем условие для r1
        if (line1.length() > 0 && line1 != "no") {
          typeText(0, line1, 100); // Анимация набора текста на первой строке
        }

        // Проверяем условие для r2
        if (line2.length() > 0 && line2 != "no") {
          typeText(1, line2, 100); // Анимация набора текста на второй строке
        }
      }
    }
    // Проверяем команду на "code.lcd.clear"
    else if (command.startsWith("code.lcd.clear")) {
      lcd.clear(); // Очищаем экран
    }
  }
}
