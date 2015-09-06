#include <node.h>
#include <bcm2835.h>

#define PIN RPI_V2_GPIO_P1_03       // Определяем порт для подключения светодиода
#define PIN_OUT RPI_V2_GPIO_P1_05   // Определяем порт для записи
#define PIN_IN RPI_V2_GPIO_P1_07    // Определяем порт для чтения

using namespace v8;

int light_led(void){

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
    return result;

}

int getCurrentStateDoor(){
    int result = 0;
    if (!bcm2835_init())
            result = -1;
    else{
        bcm2835_gpio_fsel(PIN_OUT, BCM2835_GPIO_FSEL_OUTP);      // Устанавливаем порт PIN_OUT на вывод
        bcm2835_gpio_fsel(PIN_IN, BCM2835_GPIO_FSEL_INPT);       // Устанавливаем порт PIN_IN на ввод

        bcm2835_gpio_set_pud(PIN_IN, 1);                             // Включаем подтяжку порта PIN_IN к "0"

        bcm2835_gpio_write(PIN_OUT, HIGH);                       // Устанавливаем порт PIN_OUT в состояние "1"

        if(!bcm2835_gpio_lev(PIN_IN))    // Повторяем все действия, заключённые в скобки {} пока не будет нажата кнопка
            result = 1;//дверь открыта
        else
            result = 0;//дверь закрыта

        bcm2835_gpio_set_pud(PIN_IN, 0);   // Отключаем подтяжку порта PIN_IN к "0"
        bcm2835_close ();
        }
    return result
}

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  int result = light_led();

  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world" + result));
}

void MethodGetCurrentStateDoor(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  int result = getCurrentStateDoor();

  if(result == 1){
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "Дверь открыта"));
  }else if(result == 0){
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "Дверь закрыта"));
  }else{
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "Произошла ошибка"));
  }
}

void init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
  NODE_SET_METHOD(exports, "getCurrentStateDoor", MethodGetCurrentStateDoor);
}

NODE_MODULE(addon, init)