/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef DRIVER_INIT_INCLUDED
#define DRIVER_INIT_INCLUDED

#include "atmel_start_pins.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <hal_atomic.h>
#include <hal_delay.h>
#include <hal_gpio.h>
#include <hal_init.h>
#include <hal_io.h>
#include <hal_sleep.h>

#include <tc_lite.h>
#include <tc_lite.h>
#include <tc_lite.h>

#include <tcc_lite.h>
#include <tcc_lite.h>

void redPWM_CLOCK_init(void);

int8_t redPWM_init(void);

void greenPWM_CLOCK_init(void);

int8_t greenPWM_init(void);

void bluePWM_CLOCK_init(void);

int8_t bluePWM_init(void);

void beatTimer_CLOCK_init(void);

int8_t beatTimer_init(void);

void neoPixel_CLOCK_init(void);

int8_t neoPixel_init(void);

/**
 * \brief Perform system initialization, initialize pins and clocks for
 * peripherals
 */
void system_init(void);

#ifdef __cplusplus
}
#endif
#endif // DRIVER_INIT_INCLUDED
