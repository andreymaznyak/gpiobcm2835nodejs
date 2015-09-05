#include <node.h>
#include <bcm2835.h>

#define PIN RPI_V2_GPIO_P1_03

using namespace v8;

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  int result = 0;
  if (!bcm2835_init())
         result = 1;
  else{
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);

    bcm2835_gpio_write(PIN, LOW);
    bcm2835_delay(5000);
    bcm2835_gpio_write(PIN, HIGH);

    result = bcm2835_close();
  }

  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world" + result));
}

void init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
}

NODE_MODULE(addon, init)