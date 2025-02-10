#include <LiquidCrystal.h>
#include <Keypad.h>

// Определение пинов
const int trigPin = A2;    
const int echoPin = A3;  
int duration, dist;
//int trigPin = A2; 
//int echoPin = A3; 
const int motorPin1 = 5;  
const int motorPin2 = 4;  
const int valvePins[] = {3, 6, 7}; // Пины для управления клапанами

// Создание объектов
LiquidCrystal lcd(8, 9, 10, 11, 12, 13); 

// Переменные
int recipeInput = 0;      
bool glassDetected = false; 

// Параметры клавиатуры
const byte ROWS = 4; 
const byte COLS = 3; 
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = { A0, A1, A2};     
byte colPins[COLS] = { A4, 2, A5 };   

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  // Инициализация пинов
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  for (int i = 0; i < 3; i++) { 
    pinMode(valvePins[i], OUTPUT);
    digitalWrite(valvePins[i], LOW); 
  }

  // Инициализация пинов мотора
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.print("enter recept");
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    if (key >= '1' && key <= '9') {
      recipeInput = key - '0'; 
      lcd.clear();
      lcd.print("recept");
      lcd.print(recipeInput);
      delay(1000);

      executeRecipe(recipeInput); // Выполнение выбранного рецепта
      lcd.clear();
      delay(1000);
      lcd.print("ready");
      delay(3000);

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


void executeRecipe(int recipe) {
  if (recipe == 1) { 
    digitalWrite(valvePins[0], HIGH);
    delay(1000);
    digitalWrite(valvePins[0], LOW);
    rotatePlatform(); // Поворот площадки до зоны выдачи
  }
  if (recipe == 2) { 
    digitalWrite(valvePins[2], HIGH);
    delay(59*50);
    digitalWrite(valvePins[2], LOW);
    delay(1000);
    digitalWrite(valvePins[0], HIGH);
    delay(59*50);
    digitalWrite(valvePins[0], LOW);
    delay(1000);
    digitalWrite(valvePins[1], HIGH);
    delay(59*30);
    digitalWrite(valvePins[1], LOW);
    delay(1000);
  }
  if (recipe == 3) { 
    digitalWrite(valvePins[2], HIGH);
    delay(1000);
    digitalWrite(valvePins[2], LOW);
    rotatePlatform(); // Поворот площадки до зоны выдачи
  }
  if (recipe == 4) { 
    digitalWrite(valvePins[0], HIGH);
    delay(1000);
    digitalWrite(valvePins[0], LOW);
    rotatePlatform(); // Поворот площадки до зоны выдачи
  }
  if (recipe == 5) { 
    digitalWrite(valvePins[1], HIGH);
    delay(1000);
    digitalWrite(valvePins[1], LOW);
    rotatePlatform(); // Поворот площадки до зоны выдачи
  }
  if (recipe == 6) { 
    digitalWrite(valvePins[2], HIGH);
    delay(1000);
    digitalWrite(valvePins[2], LOW);
    rotatePlatform(); // Поворот площадки до зоны выдачи
  }
  if (recipe == 9) { 
    digitalWrite(valvePins[2], HIGH);
    delay(59*30);
    digitalWrite(valvePins[2], LOW);
    delay(1000);
    digitalWrite(valvePins[0], HIGH);
    delay(59*50);
    digitalWrite(valvePins[0], LOW);
    delay(1000);
    analogWrite(motorPin1, 150);
    delay(270);
    analogWrite(motorPin1, 0);
    delay(1000);
    digitalWrite(valvePins[2], HIGH);
    delay(59*80);
    digitalWrite(valvePins[2], LOW);
    delay(1000);


  }
  if (recipe == 8) { 
    digitalWrite(valvePins[2], HIGH);
    delay(59*80);
    digitalWrite(valvePins[2], LOW);
    delay(1000);
    digitalWrite(valvePins[1], HIGH);
    delay(59*20);
    digitalWrite(valvePins[1], LOW);
    delay(1000);
  }
  if (recipe == 7) { 
    digitalWrite(valvePins[2], HIGH);
    delay(59*50);
    digitalWrite(valvePins[2], LOW);
    delay(1000);
    analogWrite(motorPin1, 150);
    delay(280);
    analogWrite(motorPin1, 0);
    delay(1000);
    digitalWrite(valvePins[0], HIGH);
    delay(59*40);
    digitalWrite(valvePins[0], LOW);
    delay(1000);
    analogWrite(motorPin1, 150);
    delay(280);
    analogWrite(motorPin1, 0);
    delay(1000);
    digitalWrite(valvePins[1], HIGH);
    delay(59*10);
    digitalWrite(valvePins[1], LOW);
    delay(1000);
    analogWrite(motorPin1, 150);
    delay(200);
    analogWrite(motorPin1, 0);
    delay(1000);
    digitalWrite(valvePins[2], HIGH);
    delay(59*50);
    digitalWrite(valvePins[2], LOW);
    delay(1000);
    analogWrite(motorPin1, 150);
    delay(280);
    analogWrite(motorPin1, 0);
    delay(5000);
    analogWrite(motorPin1, 150);
    delay(250);
    analogWrite(motorPin1, 0);
    delay(5000);
    analogWrite(motorPin1, 150);
    delay(250);
    analogWrite(motorPin1, 0);
    delay(5000);
    analogWrite(motorPin1, 150);
    delay(250);
    analogWrite(motorPin1, 0);
    delay(5000);

  }
Serial.println(recipe);
}

void rotatePlatform() {
  delay(1000);
  analogWrite(motorPin1, 150); // Вперёд
  delay(260); // Время работы мотора 
  analogWrite(motorPin1, 0); // Остановить мотор
  digitalWrite(motorPin2, HIGH); // Вперёд
  delay(10); // Время работы мотора 
  digitalWrite(motorPin2, LOW); // Остановить мотор
}
