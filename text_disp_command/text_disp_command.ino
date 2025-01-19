#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Указываем адрес I2C и размеры дисплея (например, 16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();         // Инициализация LCD
  lcd.backlight();    // Включить подсветку
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

        // Проверяем условие "no" для r1
        if (line1 != "no") {
          lcd.setCursor(0, 0);
          lcd.print(line1); // Выводим текст на первую строку
        }

        // Проверяем условие "no" для r2
        if (line2 != "no") {
          lcd.setCursor(0, 1);
          lcd.print(line2); // Выводим текст на вторую строку
        }
      }
    }
    // Проверяем команду на "code.lcd.clear"
    else if (command.startsWith("code.lcd.clear")) {
      lcd.clear(); // Очищаем экран
    }
  }
}
