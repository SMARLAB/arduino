#include "HX711.h"                                            // подключаем библиотеку для работы с тензодатчиком

#define DT  7                                                // Указываем номер вывода, к которому подключен вывод DT  датчика
#define SCK 8                                                // Указываем номер вывода, к которому подключен вывод SCK датчика
uint32_t tmr;

HX711 scale;                                                  // создаём объект scale

float calibration_factor = -3.7;                            // вводим калибровочный коэффициент
float units;                                                  // задаём переменную для измерений в граммах
float ounces;                                                 // задаём переменную для измерений в унциях

void setup() {
  Serial.begin(9600);                                         // инициируем работу последовательного порта на скорости 9600 бод
  scale.begin(DT, SCK);                                       // инициируем работу с датчиком
  scale.set_scale();                                          // выполняем измерение значения без калибровочного коэффициента
  scale.tare();                                               // сбрасываем значения веса на датчике в 0
  scale.set_scale(calibration_factor);                        // устанавливаем калибровочный коэффициент
}

void loop() {

  if (millis() - tmr >= 1000) {
 tmr = millis();   

  Serial.print("Reading: ");                                  // выводим текст в монитор последовательного порта
  for (int i = 0; i < 10; i ++) {                             // усредняем показания, считав значения датчика 10 раз
    units = + scale.get_units(), 10;                          // суммируем показания 10 замеров
  }
  units = units / 10;                                         // усредняем показания, разделив сумму значений на 10
  ounces = units * 0.035274;                                  // переводим вес из унций в граммы
  Serial.print(ounces);                                       // выводим в монитор последовательного порта вес в граммах
  Serial.println(" grams");                                   // выводим текст в монитор последовательного порта
  }
}
