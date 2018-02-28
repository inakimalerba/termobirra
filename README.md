# TermoBirra

_Ya sabes como soy, Marge, me gusta mi cerveza fría, la TV fuerte y los homosexuales locas, locas_

### Hardware
- Arduino Nano AtMega328
- Display 8x8x4 w/ MAX7219
- Temp. Sensor DS18B20

### Dependencies
- [`MD_MAX72XX`](https://github.com/MajicDesigns/MD_MAX72XX)
- [`MD_PAROLA`](https://github.com/MajicDesigns/MD_Parola)
- [`OneWire`](https://github.com/PaulStoffregen/OneWire)
- [`DallasTemperature`](https://github.com/milesburton/Arduino-Temperature-Control-Library)

### Wiring
- Display is connected via SPI (D10, D11 and D13)
- Temperature Sensor is connected to D3 port. 

### Debugging.
Serial port can be used to debug the application.
It is set at 9600 bauds.
