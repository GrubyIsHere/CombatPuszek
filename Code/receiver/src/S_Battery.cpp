#include <S_Battery.h>

//-------------//
// INICJALIZACJE//
//-------------//

// Konstruktor
S_Battery::S_Battery()
{
    Init();
}

//---------------//
// DEFINICJE METOD//
//---------------//

void S_Battery::Init()
{
    pinMode(battery_voltage_pin, INPUT);

    memset(voltage_readings, 0, sizeof(voltage_readings)); //zerowanie bufora pomiarów

    xTaskCreate(
        S_Battery::BatterymeterHeartbeat, // Funkcja zadania
        "Batterymeter",              // Nazwa zadania
        2048,                      // Rozmiar stosu (2 KB)
        this,                      // Parametry zadania
        1,                         // Priorytet (1 – niski, 2 – wyższy)
        batterymeter_task_handler  // Uchwyt zadania
    );
}

void S_Battery::BatterymeterHeartbeat(void *parameter)
{
    S_Battery* instance = static_cast<S_Battery*>(parameter); //jakiś kurwa drut castowy, żeby task w tle sie tworzył poprawnie
    while (true) {
        instance->CheckVoltage();
        vTaskDelay(pdMS_TO_TICKS(10000)); // Sprawdzaj co 10 sekund
    }
}

void S_Battery::AddVoltageReading(float voltage)
{
  voltage_readings[voltage_readings_index] = voltage;
  voltage_readings_index = (voltage_readings_index + 1) % 100; //100, bo bufor na 100 pomiarów
  
  if(!buffer_filled && voltage_readings_index == 0) {
    buffer_filled = true;
  }
}

int S_Battery::CheckVoltage()
{
    int adc_value = analogRead(battery_voltage_pin);
    float voltage = (adc_value * reference_voltage / adc_max_value) * voltage_divider_ratio;
    uint16_t voltage_mV = static_cast<uint16_t>(voltage * 1000); // Konwersja do mV

    // Dodaj odczyt do bufora
    AddVoltageReading(voltage);

    current_error = 
    (voltage_mV < low_voltage_error_threshold) ? 1 :    // Błąd niskiego napięcia
    (voltage_mV < low_voltage_warning_threshold) ? 2 :  // Ostrzeżenie o niskim napięciu
    (voltage_mV > high_voltage_error_threshold) ? 3 :   // Błąd wysokiego napięcia
    (voltage_mV > high_voltage_warning_threshold) ? 4 : // Ostrzeżenie o wysokim napięciu
    0;                                                  // Wszystko git

  return current_error;
}

uint8_t S_Battery::ReportError()
{
    return current_error;
}

float S_Battery::ReportVoltage()
{
    return voltage_readings[0];
}