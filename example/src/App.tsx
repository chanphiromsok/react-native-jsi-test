import * as React from 'react';

import { StyleSheet, View, Text } from 'react-native';

import { NativeModules, isLoaded } from 'react-native-geolocation-jsi';
export default function App() {
  React.useEffect(() => {
    console.log(NativeModules.GeolocationJsi.install(), 'isLoad', isLoaded());
  }, []);

  return (
    <View style={styles.container}>
      <Text>Result: {isLoaded() ? 'True' : 'False'}</Text>
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
