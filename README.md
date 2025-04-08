# STM32 Bare-Metal: LED Blinking with Register Structures

This project demonstrates how to blink the onboard LEDs of the STM32F4 Discovery board using register-level programming with `typedef struct`-based access. This method improves code readability and maintainability compared to direct pointer dereferencing.

---

## 🔁 Related Project

👉 If you're looking for the beginner-level version (without `typedef struct`), check out:  
https://github.com/iek2443/stm32-baremetal-leds.git

---

## 🧠 What You Will Learn

- How to use register-mapped peripheral structures (`typedef struct`) for RCC and GPIO
- How to enable peripheral clocks through `RCC->AHB1ENR`
- How to configure GPIO pins as outputs using `GPIOD->MODER`
- How to toggle output pins using `GPIOD->ODR`

---

## 🔧 Requirements

- STM32F4 Discovery Board
- ARM GCC Toolchain
- ST-Link Programmer
- STM32CubeProgrammer or OpenOCD
- USB Mini-B cable

---

📁 Project Structure
--------------------

stm32-blink-led/\
├── src/\
│   └── main.c         --> Bare-metal LED toggle code\
├── inc/               --> (Optional: header files)\
└── README.md

## 💡 LED Info (STM32F4 Discovery)

| LED | Port | Pin |
|-----|------|-----|
| LD3 (Orange) | D | 13 |
| LD4 (Green)  | D | 12 |
| LD5 (Red)    | D | 14 |
| LD6 (Blue)   | D | 15 |

---

## ⚙️ Registers Used

- `RCC->AHB1ENR` → Enables clock for GPIO port
- `GPIOD->MODER` → Configures the pin mode (output/input/etc.)
- `GPIOD->ODR` → Controls the output level on the pins

Each GPIO pin uses 2 bits in the MODER register:
- `00`: Input  
- `01`: Output  
- `10`: Alternate Function  
- `11`: Analog  

---

## ⏱ About the Delay Loop

A simple software delay is implemented using:

```c
for (volatile int i = 0; i < 200000; i++);
```
## 🧭 Summary

This approach helps you write **more readable and maintainable code** while still programming at the register level — a clean alternative to raw pointer arithmetic.

