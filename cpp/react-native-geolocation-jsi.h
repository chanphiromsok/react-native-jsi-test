#ifndef GEOLOCATIONJSI_H
#define GEOLOCATIONJSI_H

namespace facebook {
namespace jsi {
class Runtime;
}
}
namespace geolocationjsi {
  void install(facebook::jsi::Runtime &jsiRuntime);
}

#endif /* GEOLOCATIONJSI_H */
