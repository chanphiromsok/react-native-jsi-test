#ifdef __cplusplus
#import "react-native-geolocation-jsi.h"
#endif

#ifdef RCT_NEW_ARCH_ENABLED
#import "RNGeolocationJsiSpec.h"

@interface GeolocationJsi : NSObject <NativeGeolocationJsiSpec>
#else
#import <React/RCTBridgeModule.h>

@interface GeolocationJsi : NSObject <RCTBridgeModule>
#endif

@end
