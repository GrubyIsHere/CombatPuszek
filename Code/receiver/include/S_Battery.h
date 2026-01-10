#ifndef SBATTERY
#define SBATTERY

#include <Arduino.h>
#include <stdint.h>

class S_Battery
{
public:
  //----------------//
  // DEKLARACJE METOD//
  //----------------//
  // Konstruktor
  S_Battery();

  uint8_t ReportError();
  float ReportVoltage();
  int CheckVoltage();

private:
  //----------------//
  // DEKLARACJE METOD//
  //----------------//

  void Init();

  void AddVoltageReading(float voltage);

  static void BatterymeterHeartbeat(void *parameter);

  //-------//
  // OBIEKTY//
  //-------//

    TaskHandle_t *batterymeter_task_handler;

  //-------//
  // NASTAWY//
  //-------//

  const uint8_t battery_voltage_pin = 34;

  const uint16_t low_voltage_warning_threshold = 11000;  //mV
  const uint16_t low_voltage_error_threshold = 10000;    //mV

  const uint16_t high_voltage_warning_threshold = 12750; //mV
  const uint16_t high_voltage_error_threshold = 13000;   //mV

  const uint16_t adc_max_value = 4095; // ESP32 12-bit ADC

  const float reference_voltage = 3.3; 
  const float voltage_divider_ratio = 4.315; // inny niż 15k / 4,7k, bo empiryczna korekta niedokładności

  //------//
  // PAMIĘĆ//
  //------//

  float voltage_readings[100]; // Bufor odczytów
  uint8_t voltage_readings_index = 0; // Indeks bieżącego odczytu
  bool buffer_filled = false; // Czy bufor jest w pełni wypełniony

  uint8_t current_error = 0; 
};

#endif