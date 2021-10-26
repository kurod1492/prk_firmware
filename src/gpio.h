/* mruby/c VM */
#include <mrubyc.h>

void c_gpio_get(mrb_vm *vm, mrb_value *v, int argc);
void c_gpio_init(mrb_vm *vm, mrb_value *v, int argc);
void c_gpio_set_dir(mrb_vm *vm, mrb_value *v, int argc);
void c_gpio_pull_up(mrb_vm *vm, mrb_value *v, int argc);
void c_gpio_put(mrb_vm *vm, mrb_value *v, int argc);
void c_read_track_ball(mrb_vm *vm, mrb_value *v, int argc);
void c_init_paw3204(mrb_vm *vm, mrb_value *v, int argc);

#define GPIO_INIT() do { \
  mrbc_define_method(0, mrbc_class_object, "gpio_init",    c_gpio_init);    \
  mrbc_define_method(0, mrbc_class_object, "gpio_set_dir", c_gpio_set_dir); \
  mrbc_define_method(0, mrbc_class_object, "gpio_pull_up", c_gpio_pull_up); \
  mrbc_define_method(0, mrbc_class_object, "gpio_put",     c_gpio_put);     \
  mrbc_define_method(0, mrbc_class_object, "gpio_get",     c_gpio_get);     \
  mrbc_define_method(0, mrbc_class_object, "read_track_ball",     c_read_track_ball);     \
  mrbc_define_method(0, mrbc_class_object, "init_paw3204",     c_init_paw3204);     \
} while (0)

