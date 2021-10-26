#include "gpio.h"

#include "hardware/gpio.h"
#include "pico/stdlib.h"

#define PAW3204_SCLK 26
#define PAW3204_DATA 27

void
c_gpio_get(mrb_vm *vm, mrb_value *v, int argc)
{
  int gpio = GET_INT_ARG(1);
  if (gpio_get(gpio)) {
    SET_INT_RETURN(1);
  } else {
    SET_INT_RETURN(0);
  }
}

void
c_gpio_init(mrb_vm *vm, mrb_value *v, int argc)
{
  gpio_init(GET_INT_ARG(1));
}

void
c_gpio_set_dir(mrb_vm *vm, mrb_value *v, int argc)
{
  gpio_set_dir(GET_INT_ARG(1), GET_INT_ARG(2));
}

void
c_gpio_pull_up(mrb_vm *vm, mrb_value *v, int argc)
{
  gpio_pull_up(GET_INT_ARG(1));
}

void
c_gpio_put(mrb_vm *vm, mrb_value *v, int argc)
{
  int gpio = GET_INT_ARG(1);
  int value = GET_INT_ARG(2);
  gpio_put(gpio, value);
}

void
c_read_track_ball(mrb_vm *vm, mrb_value *v, int argc)
{
  gpio_set_dir(PAW3204_DATA, GPIO_OUT);
  gpio_disable_pulls(PAW3204_DATA);
  uint8_t tx_data = GET_INT_ARG(1);
  for (int i = 7; i >= 0; i--) {
    uint8_t bit = (tx_data >> i) & 0x01;
    gpio_put(PAW3204_SCLK, 0);
    busy_wait_us_32(5);
    gpio_put(PAW3204_DATA, bit);
    busy_wait_us_32(5);
    gpio_put(PAW3204_SCLK, 1);
    busy_wait_us_32(5);
  }
  busy_wait_us_32(5);
  gpio_set_dir(PAW3204_DATA, GPIO_IN);
  gpio_pull_up(PAW3204_DATA);
  int8_t rx_data = 0;
  for (int i = 7; i >= 0; i--) {
    gpio_put(PAW3204_SCLK, 0);
    busy_wait_us_32(5);
    gpio_put(PAW3204_SCLK, 1);
    busy_wait_us_32(5);
    uint8_t bit = gpio_get(PAW3204_DATA);
    busy_wait_us_32(5);
    rx_data += (bit << i);
  }
  busy_wait_us_32(5);
  SET_INT_RETURN(rx_data);
}

void
c_init_paw3204(mrb_vm *vm, mrb_value *v, int argc)
{
  gpio_init(PAW3204_SCLK);
  gpio_set_dir(PAW3204_SCLK, GPIO_OUT);
  gpio_put(PAW3204_SCLK, 1);


  gpio_init(PAW3204_DATA);
  gpio_pull_up(PAW3204_DATA);
  gpio_set_dir(PAW3204_DATA, 0);

  sleep_ms(2);
  gpio_put(PAW3204_SCLK, 0);
  busy_wait_us_32(100);
  gpio_put(PAW3204_SCLK, 1);
  sleep_ms(2);
}
