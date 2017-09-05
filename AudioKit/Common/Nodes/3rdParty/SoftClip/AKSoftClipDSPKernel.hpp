//
//  AKSoftClipDSPKernel.hpp
//  AudioKit
//
//  Created by Fraser Stuart, revision history on Github.
//  Copyright © 2017 Fraser Stuart. All rights reserved.
//
//  Based on AKSoftClipDSPKernel.hpp
//  Which was Created by Aurelius Prochazka
//  and is Copyright © 2017 Aurelius Prochazka. All rights reserved.
//

#pragma once

#import "DSPKernel.hpp"
#import "ParameterRamper.hpp"

#import <AudioKit/AudioKit-Swift.h>

extern "C" {
#include "soundpipe.h"
#include "fsr.h"
}

class AKSoftClipDSPKernel : public AKSoundpipeKernel, public AKBuffered {
public:
    // MARK: Member Functions

    AKSoftClipDSPKernel() {}

    void init(int _channels, double _sampleRate) override {
        AKSoundpipeKernel::init(_channels, _sampleRate);

        fsr_softclip_create(&sclip0);
        fsr_softclip_create(&sclip1);
        fsr_softclip_init(sp, sclip0);
        fsr_softclip_init(sp, sclip1);

    }

    void start() {
        started = true;
    }

    void stop() {
        started = false;
    }

    void destroy() {
        fsr_softclip_destroy(&sclip0);
        fsr_softclip_destroy(&sclip1);
        AKSoundpipeKernel::destroy();
    }

    void reset() {
        resetted = true;
    }


    void setParameter(AUParameterAddress address, AUValue value) {
//
    }

//    AUValue getParameter(AUParameterAddress address) {
//
//    }

    void startRamp(AUParameterAddress address, AUValue value, AUAudioFrameCount duration) override {
//
    }

    void process(AUAudioFrameCount frameCount, AUAudioFrameCount bufferOffset) override {

        for (int frameIndex = 0; frameIndex < frameCount; ++frameIndex) {

            int frameOffset = int(frameIndex + bufferOffset);



            for (int channel = 0; channel < channels; ++channel) {
                float *in  = (float *)inBufferListPtr->mBuffers[channel].mData  + frameOffset;
                float *out = (float *)outBufferListPtr->mBuffers[channel].mData + frameOffset;

                if (started) {
                    if (channel == 0) {
                        fsr_softclip_compute(sp, sclip0, in, out);
                    } else {
                        fsr_softclip_compute(sp, sclip1, in, out);
                    }
                } else {
                    *out = *in;
                }
            }
        }
    }

    // MARK: Member Variables

private:

    fsr_softclip *sclip0;
    fsr_softclip *sclip1;


public:
    bool started = true;
    bool resetted = false;

};
