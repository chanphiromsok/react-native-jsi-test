#include <jni.h>
#include "react-native-geolocation-jsi.h"
#include "sys/types.h"
#include "pthread.h"
#include <jsi/jsi.h>

using namespace facebook::jsi;
using namespace std;

JavaVM *java_vm;
jclass java_class;
jobject java_object;

void DeferThreadDetach(JNIEnv *env)
{
  static pthread_key_t thread_key;

  static auto run_once = []
  {
    const auto err = pthread_key_create(&thread_key, [](void *ts_env)
                                        {
            if (ts_env) {
                java_vm->DetachCurrentThread();
            } });
    if (err)
    {
      // Failed to create TSD key. Throw an exception if you want to.
    }
    return 0;
  };

  const auto ts_env = pthread_getspecific(thread_key);
  if (!ts_env)
  {
    if (pthread_setspecific(thread_key, env))
    {
      // Failed to set thread-specific value for key. Throw an exception if you
      // want to.
    }
  }
}

/**
 * Get a JNIEnv* valid for this thread, regardless of whether
 * we're on a native thread or a Java thread.
 * If the calling thread is not currently attached to the JVM
 * it will be attached, and then automatically detached when the
 * thread is destroyed.
 *
 * See https://stackoverflow.com/a/30026231 for detailed explanation
 */
JNIEnv *GetJniEnv()
{
  JNIEnv *env = nullptr;
  // We still call GetEnv first to detect if the thread already
  // is attached. This is done to avoid setting up a DetachCurrentThread
  // call on a Java thread.

  // g_vm is a global.
  auto get_env_result = java_vm->GetEnv((void **)&env, JNI_VERSION_1_6);
  if (get_env_result == JNI_EDETACHED)
  {
    if (java_vm->AttachCurrentThread(&env, NULL) == JNI_OK)
    {
      DeferThreadDetach(env);
    }
    else
    {
      // Failed to attach thread. Throw an exception if you want to.
    }
  }
  else if (get_env_result == JNI_EVERSION)
  {
    // Unsupported JNI version. Throw an exception if you want to.
  }
  return env;
}

void install(Runtime &jsiRuntime)
{
  auto getDeviceName = Function::createFromHostFunction(
      jsiRuntime, PropNameID::forAscii(jsiRuntime, "getDeviceName"), 0,
      [](Runtime &runtime, const Value &thisValue, const Value *arguments,
         size_t count) -> Value
      {
        JNIEnv *jniEnv = GetJniEnv();

        java_class = jniEnv->GetObjectClass(java_object);
        jmethodID getModel =
            jniEnv->GetMethodID(java_class, "getModel", "()Ljava/lang/String;");
        jobject result = jniEnv->CallObjectMethod(java_object, getModel);
        const char *str = jniEnv->GetStringUTFChars((jstring)result, NULL);

        return Value(runtime, String::createFromUtf8(runtime, str));
      });
  jsiRuntime.global().setProperty(jsiRuntime, "getDeviceName",
                                  move(getDeviceName));

  // ====
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

extern "C" JNIEXPORT void JNICALL
Java_com_geolocationjsi_GeolocationJsiModule_nativeInstall(JNIEnv *env, jobject thiz, jlong jsi)
{
  auto runtime = reinterpret_cast<facebook::jsi::Runtime *>(jsi);

  if (runtime)
  {
    // geolocationjsi::install(*runtime);
    install(*runtime);
  }
  env->GetJavaVM(&java_vm);
  java_object = env->NewGlobalRef(thiz);
}
