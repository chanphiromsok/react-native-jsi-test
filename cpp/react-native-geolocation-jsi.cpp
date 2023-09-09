#include "react-native-geolocation-jsi.h"
#include <jsi/jsi.h>

#include <thread>
using namespace facebook::jsi;
using namespace std;
namespace geolocationjsi
{
  void install(Runtime &jsiRuntime)
  {

    auto helloWorld = Function::createFromHostFunction(jsiRuntime, PropNameID::forAscii(jsiRuntime, "helloWorld"), 0, [](Runtime &runtime, const Value &thisValue, const Value *arguments, size_t count) -> Value
                                                       {
            string helloworld = "helloworld";
            return Value(runtime, String::createFromUtf8(runtime, helloworld)); });

    jsiRuntime.global().setProperty(jsiRuntime, "helloWorld", move(helloWorld));


    // Multiply
    auto multiply = Function::createFromHostFunction(
        jsiRuntime, PropNameID::forAscii(jsiRuntime, "multiply"), 2,
        [](Runtime &runtime, const Value &thisValue, const Value *arguments,
           size_t count) -> Value
        {
          int x = arguments[0].getNumber();
          int y = arguments[1].getNumber();
          return Value(x * y);
        });

    jsiRuntime.global().setProperty(jsiRuntime, "multiply", move(multiply));
  }

}
