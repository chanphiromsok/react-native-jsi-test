#include "react-native-geolocation-jsi.h"
#include <jsi/jsi.h>

#include <thread>
using namespace facebook::jsi;
using namespace std;
#include <vector>

// constexpr double kPolylinePrecision = 1E6;
// constexpr double kInvPolylinePrecision = 1.0 / kPolylinePrecision;

// struct PointLL
// {
//   float lat;
//   float lon;
// };
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

    // decode route
    auto decodeRoute = Function::createFromHostFunction(
        jsiRuntime, PropNameID::forAscii(jsiRuntime, "decodeRoute"), 1,
        [](Runtime &runtime, const Value &thisValue, const Value *arguments,
           size_t count) -> Value
        {
          string encoded = arguments[0].asString(runtime).utf8(runtime);
          return Value(runtime, String::createFromUtf8(runtime, encoded));
        });
    jsiRuntime.global().setProperty(jsiRuntime, "decodeRoute", move(decodeRoute));
  }

  // std::vector<PointLL> decode(String &encoded)
  // {
  //   size_t i = 0; // what byte are we looking at

  //   // Handy lambda to turn a few bytes of an encoded string into an integer
  //   auto deserialize = [&encoded, &i](const int previous)
  //   {
  //     // Grab each 5 bits and mask it in where it belongs using the shift
  //     int byte, shift = 0, result = 0;
  //     do
  //     {
  //       byte = static_cast<int>(encoded[i++]) - 63;
  //       result |= (byte & 0x1f) << shift;
  //       shift += 5;
  //     } while (byte >= 0x20);
  //     // Undo the left shift from above or the bit flipping and add to previous
  //     // since its an offset
  //     return previous + (result & 1 ? ~(result >> 1) : (result >> 1));
  //   };

  //   // Iterate over all characters in the encoded string
  //   std::vector<PointLL> shape;
  //   int last_lon = 0, last_lat = 0;
  //   while (i < encoded.length())
  //   {
  //     // Decode the coordinates, lat first for some reason
  //     int lat = deserialize(last_lat);
  //     int lon = deserialize(last_lon);

  //     // Shift the decimal point 5 places to the left
  //     shape.emplace_back(static_cast<float>(static_cast<double>(lat) *
  //                                           kInvPolylinePrecision),
  //                        static_cast<float>(static_cast<double>(lon) *
  //                                           kInvPolylinePrecision));

  //     // Remember the last one we encountered
  //     last_lon = lon;
  //     last_lat = lat;
  //   }
  //   return shape;
  // }

}
