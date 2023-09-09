package com.geolocationjsi;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.facebook.react.bridge.JavaScriptContextHolder;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.module.annotations.ReactModule;

@ReactModule(name = GeolocationJsiModule.NAME)
public class GeolocationJsiModule extends ReactContextBaseJavaModule {
  public static final String NAME = "GeolocationJsi";
  private native void nativeInstall(long jsiPtr);

  public GeolocationJsiModule(ReactApplicationContext reactContext) {
    super(reactContext);
  }

  @Override
  @NonNull
  public String getName() {
    return NAME;
  }

  @ReactMethod(isBlockingSynchronousMethod = true)
  public boolean install() {
    try {
      Log.i(NAME, "Loading C++ library...");
      System.loadLibrary("cpp");

      JavaScriptContextHolder jsContext = getReactApplicationContext().getJavaScriptContextHolder();
//      if (rootDirectory == null) {
//        rootDirectory = getReactApplicationContext().getFilesDir().getAbsolutePath();
//      }
      nativeInstall(jsContext.get());
      Log.i(NAME, "Successfully installed Geolocation JSI Bindings!");
      return true;
    } catch (Exception exception) {
      Log.e(NAME, "Failed to install Geolocation JSI Bindings!", exception);
      return false;
    }
  }


}
