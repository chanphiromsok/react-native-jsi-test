#include <jni.h>
#include "react-native-geolocation-jsi.h"

// extern "C"
// JNIEXPORT jdouble JNICALL
// Java_com_geolocationjsi_GeolocationJsiModule_nativeMultiply(JNIEnv *env, jclass type, jdouble a, jdouble b) {
//     return geolocationjsi::multiply(a, b);
// }

extern "C"
JNIEXPORT void JNICALL
Java_com_geolocationjsi_GeolocationJsiModule_nativeInstall(JNIEnv *env, jobject thiz, jlong jsi) {
     auto runtime = reinterpret_cast<facebook::jsi::Runtime *>(jsi);

    if (runtime) {
        geolocationjsi::install(*runtime);
    }
}
