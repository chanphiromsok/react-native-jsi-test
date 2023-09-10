import { NativeModules, Platform } from 'react-native';

// const LINKING_ERROR =
//   `The package 'react-native-geolocation-jsi' doesn't seem to be linked. Make sure: \n\n` +
//   Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
//   '- You rebuilt the app after installing the package\n' +
//   '- You are not using Expo Go\n';

// @ts-ignore
const GeolocationJsi: {
  multiply(x: number, y: number): number;
  helloWorld(): string;
  getDeviceName:()=>string
  //@ts-ignore
} = global;

export function isLoaded() {
  return typeof NativeModules.GeolocationJsi.install === 'function';
}


if(typeof NativeModules.GeolocationJsi.install === 'function'){
  NativeModules.GeolocationJsi.install();
}
// if (!isLoaded()) {
//   const result = NativeModules.GeolocationJsi?.install();
//   if (!result && !isLoaded())
//     throw new Error('JSI bindings were not installed for: SimpleJsi Module');

//   if (!isLoaded()) {
//     throw new Error('JSI bindings were not installed for: SimpleJsi Module');
//   }
// }
export { NativeModules };
export default GeolocationJsi;
