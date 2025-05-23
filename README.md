# Монитор Температуры Дизеля Тепловоза (Кейс №40)

Проект для хакатона, реализующий систему мониторинга температуры охлаждающей жидкости (воды) и масла дизельного двигателя тепловоза на базе микроконтроллера ESP8266.

## Контекст (Кейс №40 - ООО «Компания «Востсибуголь»)

**Проблема:** На старых моделях тепловозов (ТЭМ-7(А), ТЭМ-2(18), ТЭ10, ТЭ116) отсутствует автоматическая регистрация температуры охлаждающей жидкости и масла. Контроль возложен на машиниста. Превышение температурных режимов приводит к дорогостоящим поломкам дизеля. Необходимо регистрировать параметры для анализа причин перегрева и обучения локомотивных бригад.

**Цель:** Оснастить тепловоз датчиками температуры воды и масла с возможностью передачи и хранения данных для анализа случаев перегрева.

**Критерии успеха:** Уменьшение количества отказов тепловозов из-за перегрева.

## Описание Проекта

Данный проект представляет собой прототип системы мониторинга:
1.  **Считывает** показания с двух датчиков температуры DHT11 (имитирующих датчики воды и масла).
2.  **Оценивает** текущее состояние: норма, повышенная температура, критический перегрев.
3.  **Индицирует** состояние с помощью RG светодиода (Зеленый - норма, Красный - выше нормы, Мигающий красный - критично, Желтый (R+G) - ошибка чтения датчика).
4.  **Симулирует** расчет управляющих параметров для системы охлаждения (обороты вентилятора, поток насоса) на основе температуры.
5.  **Отправляет** данные о температуре и расчетных параметрах на платформу IoT ThingSpeak для удаленного мониторинга и хранения.
6.  **Рассчитывает** скорость изменения температуры для возможного анализа динамики нагрева/остывания.

## Аппаратное Обеспечение

*   Микроконтроллер ESP8266 (например, NodeMCU V2/V3)
*   2 x Датчика температуры и влажности DHT11 (или DHT22). *Примечание: Для реального применения потребуются промышленные датчики температуры (термопары K-типа, PT100 и т.д.).*
*   Двухцветный (красно-зеленый) или RGB светодиод (используются только красный и зеленый компоненты).
*   Резисторы для светодиода (например, 2 x 220-330 Ом).
*   Соединительные провода.
*   Источник питания для ESP8266 (5V).

## Программное Обеспечение

*   Среда разработки Arduino IDE или PlatformIO.
*   Установленный пакет поддержки плат ESP8266.
*   Библиотеки:
    *   `DHT sensor library` (от Adafruit или аналог)
    *   `ESP8266WiFi` (входит в ядро ESP8266)
    *   `ESP8266HTTPClient` (входит в ядро ESP8266)

## Конфигурация

Основные параметры настраиваются в файле `config.h`:
*   `wifi_ssid`, `wifi_pass`: Имя и пароль вашей Wi-Fi сети.
*   `ts_key`: API ключ для записи (Write API Key) вашего канала ThingSpeak (4 поля: Water Temp, Oil Temp, Fan RPM, Pump LPM).
*   `pin_dht_water`, `pin_dht_oil`, `pin_rgb_r`, `pin_rgb_g`: Пины подключения датчиков и светодиода.
*   `temp_norm`, `temp_crit`: Температурные пороги для индикации.
*   Параметры симуляции управления.
*   Интервалы чтения и отправки данных.

## Структура Кода

*   `Hakaton_C6.ino`: Главный файл (`setup()`, `loop()`).
*   `config.h`: Конфигурация.
*   `sensors.h/.cpp`: Инициализация датчиков.
*   `control.h/.cpp`: Расчет управляющих параметров (симуляция).
*   `network.h/.cpp`: Wi-Fi и ThingSpeak.
*   `utils.h/.cpp`: Управление светодиодом, утилиты.

## Сборка и Загрузка

1.  Клонируйте репозиторий.
2.  Откройте проект в Arduino IDE/PlatformIO.
3.  Установите библиотеки.
4.  Отредактируйте `config.h` (Wi-Fi, ThingSpeak Key).
5.  Подключите компоненты к ESP8266 согласно `config.h`.
6.  Выберите плату и порт.
7.  Скомпилируйте и загрузите.
8.  Откройте Монитор серийного порта (9600).
9.  Проверьте данные на ThingSpeak.
10. Создать файл log.csv.
11. Запустить serial_log.py для логирования

## Ссылка на Thingspeak

https://thingspeak.mathworks.com/channels/2935390