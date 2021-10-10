#include "adc.h"

#include "hardware/adc.h"

void
c_adc_init(mrb_vm *vm, mrb_value *v, int argc)
{
  adc_gpio_init(GET_INT_ARG(1));
}

void
c_adc_set_dir(mrb_vm *vm, mrb_value *v, int argc)
{
  adc_select_input(GET_INT_ARG(1));
}

void
c_adc_read(mrb_vm *vm, mrb_value *v, int argc)
{
  SET_INT_RETURN(adc_read());
}

void
c_adc_read_v(mrb_vm *vm, mrb_value *v, int argc)
{
  SET_FLOAT_RETURN(3.3 * adc_read() / 0x1000);
}
