import * as React from 'react';

import { StyleSheet, View, Text } from 'react-native';

import GeolocationJsi,{ NativeModules, isLoaded } from 'react-native-geolocation-jsi';
export default function App() {
  React.useEffect(() => {
    console.log(NativeModules.GeolocationJsi.install());
  }, []);

  return (
    <View style={styles.container}>
      <Text>Result: {GeolocationJsi.multiply(10,200)} </Text>
      <Text>Hello Word: {GeolocationJsi.helloWorld()} </Text>
      <Text>Is Installed {isLoaded() ? "true" : "false"}</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
  box: {
    width: 60,
    height: 60,
    marginVertical: 20,
  },
});
