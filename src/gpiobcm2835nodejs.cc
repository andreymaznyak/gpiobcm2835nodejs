#include <node.h>
#include <bcm2835.h>

#define PIN RPI_V2_GPIO_P1_03

using namespace v8;

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  int result = 0;
  if (!bcm2835_init())         // ������������� GPIO
         result = 1;                //���������� ���������, ���� ������������� �� �������
  else{
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);

    bcm2835_gpio_write(PIN, LOW);   // ������������� ���� � 0, ��������� �����
    bcm2835_delay(5000);             // ��� 500 ����������
    bcm2835_gpio_write(PIN, HIGH);  // ������������� ���� � 1, ��������� �� �����

    result = cm2835_close();
  }

  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
}

void init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
}

NODE_MODULE(addon, init)