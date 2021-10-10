/* mruby/c VM */
#include <mrubyc.h>
void c_adc_init(mrb_vm *vm, mrb_value *v, int argc);
void c_adc_set_dir(mrb_vm *vm, mrb_value *v, int argc);
void c_adc_read(mrb_vm *vm, mrb_value *v, int argc);
void c_adc_read_v(mrb_vm *vm, mrb_value *v, int argc);

#define ADC_INIT() do { \
  mrbc_define_method(0, mrbc_class_object, "adc_init",    c_adc_init);    \
  mrbc_define_method(0, mrbc_class_object, "adc_set_dir", c_adc_set_dir); \
  mrbc_define_method(0, mrbc_class_object, "adc_read",    c_adc_read);    \
  mrbc_define_method(0, mrbc_class_object, "adc_read_v",  c_adc_read_v);  \
} while (0)