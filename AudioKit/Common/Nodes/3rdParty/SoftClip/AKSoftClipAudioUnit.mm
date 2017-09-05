//
//  AKSoftClipAudioUnit.mm
//  AudioKit
//
//  Created by Fraser Stuart, revision history on Github.
//  Copyright © 2017 Fraser Stuart. All rights reserved.
//
//  Based on AKClipperAudioUnit.mm
//  Which was Created by Aurelius Prochazka
//  and is Copyright © 2017 Aurelius Prochazka. All rights reserved.
//

#import "AKSoftClipAudioUnit.h"
#import "AKSoftClipDSPKernel.hpp"

#import "BufferedAudioBus.hpp"

#import <AudioKit/AudioKit-Swift.h>

@implementation AKSoftClipAudioUnit {
    // C++ members need to be ivars; they would be copied on access if they were properties.
    AKSoftClipDSPKernel _kernel;
    BufferedInputBus _inputBus;
}


standardKernelPassthroughs()



AUAudioUnitOverrides(SoftClip);

@end


