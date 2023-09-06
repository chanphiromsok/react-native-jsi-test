#include <jni.h>
#include "react-native-geolocation-jsi.h"

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_geolocationjsi_GeolocationJsiModule_nativeMultiply(JNIEnv *env, jclass type, jdouble a, jdouble b) {
    return geolocationjsi::multiply(a, b);
}
