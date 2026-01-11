STM32F4 – Interner Temperatursensor

- Kanal: ADC1_IN18
  - Quelle: Reference Manual, S. 412–413, Punkt 13.10 „Temperature Sensor“

- ADC-Auflösung: 12 Bit → 0–4095
  - Quelle: Datasheet S. 42, Abschnitt 3.38

- ADC Takt (ADCCLK) aus APB2 (PCLK2) über Prescaler
  - Quelle: Reference Manual, S. 390, Punkt 13.3.2

- Umrechnung ADC → Temperatur:
  - Formel: Temperatur (°C) = (V_SENSE - V25) / Avg_Slope + 25
  - V25 = 0.76 V, Avg_Slope = 2.5 mV/°C
    - Quelle: Datasheet S. 164
  - V_SENSE = ADC_Wert * (V_REF / 4095)

- Sampling-Time:
  - Empfohlen ≥ 480 ADC-Zyklen
  - Formel: t_Abtast = ADC_Zyklen / f_ADCCLK
  - Beispiel: ADCCLK = 36 MHz → 480 Zyklen ~13 µs
  - Quelle: Reference Manual, S. 412–413, Datasheet Tabelle ADC characteristics

- Hinweise:
  - ADC starten: HAL_ADC_Start()
  - Werte abrufen: HAL_ADC_PollForConversion() + HAL_ADC_GetValue()
  - Werte in °C umrechnen mit eigener Funktion
