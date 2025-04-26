#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

constexpr char wifi_ssid[] = "HONOR X6";      // Имя вашей Wi-Fi сети
constexpr char wifi_pass[] = "11111111";      // Пароль вашей Wi-Fi сети

constexpr char ts_host[]   = "api.thingspeak.com"; // Сервер ThingSpeak
constexpr char ts_key[]    = "UWRUCKEFA0VXVNOM";   // Ваш API ключ для записи в канал ThingSpeak

constexpr uint8_t pin_dht_water = 5;  // Пин датчика температуры воды (D1)
constexpr uint8_t pin_dht_oil   = 10;  // Пин датчика температуры масла (D2)
constexpr uint8_t pin_rgb_r     = 14; // Пин красного компонента LED (D5)
constexpr uint8_t pin_rgb_g     = 12; // Пин зеленого компонента LED (D6)

constexpr float temp_norm  =  90.0f; // Нормальная температура
constexpr float temp_crit  = 120.0f; // Критическая температура

constexpr float rpm_min  =  500.0f; // Минимальные обороты вентилятора
constexpr float rpm_max  = 1800.0f; // Максимальные обороты вентилятора
constexpr float lpm_min  =    8.0f; // Минимальный поток насоса (л/мин)
constexpr float lpm_max  =   20.0f; // Максимальный поток насоса (л/мин)

constexpr float fan_rps_per_5deg   = 3.0f;  // Увеличение скорости вентилятора (об/сек) на каждые 5°C
constexpr float pump_lps_per_5deg  = 0.20f; // Увеличение потока насоса (л/сек) на каждые 5°C

constexpr uint32_t read_every_ms = 2000;  // Интервал чтения датчиков
constexpr uint32_t push_every_ms = 15000; // Интервал отправки данных на ThingSpeak

#endif
