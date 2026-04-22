# STM32 Embedded Peripheral Demo

This project is an embedded system implementation on an STM32 Discovery board.  
It demonstrates the use of common microcontroller peripherals such as timers, ADC, interrupts, GPIO, LCD, and watchdog functionality.

---

## Features

- Internal temperature sensor via ADC
- Timer-based ADC triggering (TIM3 → TRGO)
- Interrupt-driven data processing (ADC callback)
- Independent Watchdog (IWDG) 
- GPIO control (LED for critical temperature)
- LCD output (live temperature display)
- Reset reason detection (watchdog / power / software reset)

---

## System Overview

- A hardware timer (TIM3) periodically triggers ADC conversions
- The internal temperature sensor is sampled via ADC
- Temperature values are converted and displayed on an LCD
- If a threshold is exceeded, an LED is activated
- A watchdog monitors system activity:
  - If no valid ADC updates occur, the watchdog is not refreshed -> system reset
- After reset, the cause is printed for debugging purposes

---

## Project Goals

The goal of this project is to apply core embedded systems concepts:

- Interrupt handling
- Peripheral integration
- Real-time behavior
- System reliability (watchdog)

---

## Hardware

- STM32F429 Discovery Board

