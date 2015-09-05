#include <node.h>
#include <./gpio_functions.h>

using namespace v8;

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  int result = lightLED();

  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world" + result));
}

void init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
}

NODE_MODULE(addon, init)