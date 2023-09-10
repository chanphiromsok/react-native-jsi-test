package com.geolocationjsi;
import android.content.SharedPreferences;
import android.os.Build;
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
      System.loadLibrary("geolocationjsi");

      JavaScriptContextHolder jsContext = getReactApplicationContext().getJavaScriptContextHolder();
//      if (rootDirectory == null) {
//        rootDirectory = getReactApplicationContext().getFilesDir().getAbsolutePath();
//      }
      nativeInstall(jsContext.get());
      Log.i(NAME, "Successfully installed geolocationjsi JSI Bindings!");
      return true;
    } catch (Exception exception) {
      Log.e(NAME, "Failed to install geolocationjsi JSI Bindings!", exception);
      return false;
    }
  }

public String getModel() {
  String manufacturer = Build.MANUFACTURER;
  String model = Build.MODEL;
  if (model.startsWith(manufacturer)) {
    return model;
  } else {
    return manufacturer + " " + model;
  }
}

public void setItem(final String key, final String value) {
  SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(this.getReactApplicationContext());
  SharedPreferences.Editor editor = preferences.edit();
  editor.putString(key, value);
  editor.apply();
}

public String getItem(final String key) {
  SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(this.getReactApplicationContext());
  return preferences.getString(key, "");
}
}
