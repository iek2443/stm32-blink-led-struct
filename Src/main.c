/**
 * STM32F4 Bare-Metal LED Blink Example using Register Structures
 *
 * - Blinks all 4 user LEDs (LD3–LD6) on the STM32F4 Discovery board.
 * - Uses RCC and GPIOD peripheral structures (typedef struct) for register access.
 * - No HAL, no CMSIS — pure register-level programming.
 */

#include <stdint.h>

// ==============================
// Base Address Definitions
// ==============================

#define PERIPH_BASE             (0x40000000UL)                // Base address of all peripheral registers
#define AHB1PERIPH_OFFSET       (0x00020000UL)                // Offset for AHB1 peripherals
#define AHB1PERIPH_BASE         (PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOD_OFFSET            (0x0C00UL)                    // GPIOD offset in AHB1
#define GPIOD_BASE              (AHB1PERIPH_BASE + GPIOD_OFFSET)

#define RCC_OFFSET              (0x3800UL)                    // RCC offset in AHB1
#define RCC_BASE                (AHB1PERIPH_BASE + RCC_OFFSET)

#define GPIODEN                 (1U << 3)                     // Bit 3 enables GPIOD clock

// ==============================
// Typedef Struct Definitions
// ==============================

#define __IO volatile

typedef struct {
	__IO uint32_t MODER;     // Mode register
	__IO uint32_t OTYPER;    // Output type register
	__IO uint32_t OSPEEDR;   // Output speed register
	__IO uint32_t PUPDR;     // Pull-up/pull-down register
	__IO uint32_t IDR;       // Input data register
	__IO uint32_t ODR;       // Output data register
	__IO uint32_t BSRR;      // Bit set/reset register
	__IO uint32_t LCKR;      // Configuration lock register
	__IO uint32_t AFRL;      // Alternate function low register
	__IO uint32_t AFRH;      // Alternate function high register
} GPIO_TypeDef;

typedef struct {
	__IO uint32_t CR;
	__IO uint32_t PLLCFGR;
	__IO uint32_t CFGR;
	__IO uint32_t CIR;
	__IO uint32_t AHB1RSTR;
	__IO uint32_t AHB2RSTR;
	__IO uint32_t AHB3RSTR;
	uint32_t RESERVED0;
	__IO uint32_t APB1RSTR;
	__IO uint32_t APB2RSTR;
	uint32_t RESERVED1[2];
	__IO uint32_t AHB1ENR;    // AHB1 peripheral clock enable register
	__IO uint32_t AHB2ENR;
	__IO uint32_t AHB3ENR;
	uint32_t RESERVED2;
	__IO uint32_t APB1ENR;
	__IO uint32_t APB2ENR;
	uint32_t RESERVED3[2];
	__IO uint32_t AHB1LPENR;
	__IO uint32_t AHB2LPENR;
	__IO uint32_t AHB3LPENR;
	uint32_t RESERVED4;
	__IO uint32_t APB1LPENR;
	__IO uint32_t APB2LPENR;
	uint32_t RESERVED5[2];
	__IO uint32_t BDCR;
	__IO uint32_t CSR;
	uint32_t RESERVED6[2];
	__IO uint32_t SSCGR;
	__IO uint32_t PLLI2SCFGR;
	__IO uint32_t PLLSAICFGR;
	__IO uint32_t DCKCFGR;
} RCC_TypeDef;

// ==============================
// Peripheral Access Macros
// ==============================

#define RCC     ((RCC_TypeDef *) RCC_BASE)
#define GPIOD   ((GPIO_TypeDef *) GPIOD_BASE)

// ==============================
// LED Pin Definitions
// ==============================

#define PIN12           (1U << 12)      // Green LED
#define PIN13           (1U << 13)      // Orange LED
#define PIN14           (1U << 14)      // Red LED
#define PIN15           (1U << 15)      // Blue LED

// ==============================
// Main Function
// ==============================

int main(void) {
	// 1. Enable clock access to GPIOD
	RCC->AHB1ENR |= GPIODEN;

	// 2. Set GPIOD pins 12, 13, 14, 15 as general purpose output
	GPIOD->MODER &= ~(0xFFU << 24);     // Clear bits first
	GPIOD->MODER |= (1U << 24);         // Pin 12 - output
	GPIOD->MODER |= (1U << 26);         // Pin 13 - output
	GPIOD->MODER |= (1U << 28);         // Pin 14 - output
	GPIOD->MODER |= (1U << 30);         // Pin 15 - output

	// 3. Blink loop
	while (1) {
		GPIOD->ODR ^= PIN13;            // Toggle Orange LED (LD3)
		for (volatile int i = 0; i < 200000; i++)
			; // Delay

		GPIOD->ODR ^= PIN12;            // Toggle Green LED (LD4)
		for (volatile int i = 0; i < 200000; i++)
			;

		GPIOD->ODR ^= PIN14;            // Toggle Red LED (LD5)
		for (volatile int i = 0; i < 200000; i++)
			;

		GPIOD->ODR ^= PIN15;            // Toggle Blue LED (LD6)
		for (volatile int i = 0; i < 200000; i++)
			;
	}
}
