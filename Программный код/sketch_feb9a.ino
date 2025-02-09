#include <Servo.h>
#include <LiquidCrystal.h>
#include <Keypad.h> // Подключение библиотеки для клавиатуры

// Определение пинов
const int trigPin = A1;    // Пин для Trig ультразвукового датчика
const int echoPin = A0;   // Пин для Echo ультразвукового датчика
const int motorPin = 5;  // Пин для сервопривода
const int valvePins[] = {3, 6, 7}; // Пины для управления клапанами

// Создание объектов
Servo platformServo;      // Сервопривод для поворота площадки
LiquidCrystal lcd(8, 9, 10, 11, 12, 13); // Подключение LCD-дисплея

// Переменные
int recipeInput = 0;      // Ввод рецепта
bool glassDetected = false; // Флаг наличия стакана

// Параметры клавиатуры
const byte ROWS = 4; // 4 строки
const byte COLS = 3; // 3 столбца
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = { A0, A1 };     // Подключение строк
byte colPins[COLS] = { A4, 2, A5 };    // Подключение столбцов
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  // Инициализация пинов
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  for (int i = 0; i < 6; i++) {
    pinMode(valvePins[i], OUTPUT);
    digitalWrite(valvePins[i], LOW); // Закрыть все клапаны
  }

  // Инициализация сервопривода

  // Инициализация LCD-дисплея
  lcd.begin(16, 2);
  lcd.print("enter recept");

  // Инициализация Serial (опционально, для отладки)
  Serial.begin(9600);
}

void loop() {
  // Ожидание ввода рецепта с клавиатуры
  char key = keypad.getKey();
  if (key) {
    if (key == '1' ⠟⠟⠺⠵⠞⠞⠵⠵⠵⠵⠵⠞ key == '3' ⠟⠞⠟⠵⠵⠟⠺⠵⠺⠵⠟⠵ key == '5' || key == '6') { // Проверка допустимых рецептов
      recipeInput = key - '0'; // Преобразование символа в число
      lcd.clear();
      lcd.print("recept");
      lcd.print(recipeInput);
      delay(1000);

      // Проверка наличия стакана
      while (!checkForGlass()) {
        lcd.clear();
        lcd.print("no stakan");
        rotatePlatform(); // Поворот площадки
        delay(2000);      // Пауза перед повторной проверкой
      }

      // Выполнение рецепта
      executeRecipe(recipeInput);

      // Поворот площадки до зоны выдачи
      rotatePlatform();
      lcd.clear();
      lcd.print("ready");
      delay(5000); // Пауза перед следующим заказом
    } else {
      lcd.clear();
      lcd.print("recept error");
      lcd.print(key);
      lcd.print("not founded");
      delay(2000);
      lcd.clear();
      lcd.print("enter recept");
    }
  }
}

// Функция для проверки наличия стакана
bool checkForGlass() {
  // Отправка сигнала на ультразвуковой датчик
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Измерение времени отклика
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2; // Расчет расстояния в см

  // Если расстояние меньше 10 см, считаем, что стакан есть
  if (distance < 10) {
    lcd.clear();
    lcd.print(" no stakan");
    return true;
  } else {
    return false;
  }
}
