/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>
#include <hpl_gclk_base.h>
#include <hpl_pm_base.h>

void redAction_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, TC3);
	_gclk_enable_channel(TC3_GCLK_ID, CONF_GCLK_TC3_SRC);
}

void greenAction_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, TC4);
	_gclk_enable_channel(TC4_GCLK_ID, CONF_GCLK_TC4_SRC);
}

void blueAction_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, TC5);
	_gclk_enable_channel(TC5_GCLK_ID, CONF_GCLK_TC5_SRC);
}

void pwmTimer_PORT_init(void)
{

	gpio_set_pin_function(PA04, PINMUX_PA04E_TCC0_WO0);

	gpio_set_pin_function(PA05, PINMUX_PA05E_TCC0_WO1);

	gpio_set_pin_function(PA18, PINMUX_PA18F_TCC0_WO2);
}

void pwmTimer_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, TCC0);
	_gclk_enable_channel(TCC0_GCLK_ID, CONF_GCLK_TCC0_SRC);
}

void system_init(void)
{
	init_mcu();

	redAction_CLOCK_init();

	redAction_init();

	greenAction_CLOCK_init();

	greenAction_init();

	blueAction_CLOCK_init();

	blueAction_init();

	pwmTimer_CLOCK_init();

	pwmTimer_PORT_init();

	pwmTimer_init();
}
