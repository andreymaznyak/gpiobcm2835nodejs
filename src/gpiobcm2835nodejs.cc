#include <node.h>
#include <bcm2835.h>

#define PIN RPI_V2_GPIO_P1_03

using namespace v8;

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  int result = 0;
  if (!bcm2835_init())         // Инициализация GPIO
         result = 1;                //Завершение программы, если инициализация не удалась
  else{
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);

    bcm2835_gpio_write(PIN, LOW);   // Устанавливаем порт в 0, светодиод горит
    bcm2835_delay(5000);             // Ждём 500 милисекунд
    bcm2835_gpio_write(PIN, HIGH);  // Устанавливаем порт в 1, светодиод не горит

    result = cm2835_close();
  }

  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
}

void init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
}

NODE_MODULE(addon, init)