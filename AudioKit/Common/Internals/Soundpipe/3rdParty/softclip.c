/*
 * SoftClip
 *
 * A soft clipping function that forces the output is always -1 < out < 1.
 * only samples exceeding -3db are altered
 *
 * Note the range and scale have been picked so that the slope is 45deg at 0.7
 * 
 * Copyright (c) 1998 Fraser Stuart
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif 

#ifndef M_E
#define M_E  2.71828182845904523536
#endif

#include "soundpipe.h"
#include "fsr.h"

int fsr_softclip_create(fsr_softclip **p)
{
    *p = malloc(sizeof(fsr_softclip));
    return SP_OK;
}

int fsr_softclip_destroy(fsr_softclip **p)
{
    free(*p);
    return SP_OK;
}

int fsr_softclip_init(sp_data *sp, fsr_softclip *p)
{
    p->threshold = 0.7;
    return SP_OK;
}

int fsr_softclip_compute(sp_data *sp, fsr_softclip *p, SPFLOAT *in, SPFLOAT *out)
{
    p->threshold = 0.7;
    SPFLOAT threshold = p->threshold;
    SPFLOAT range = 1 - threshold;  //0.3 - anything above 0.7 will be condensed into this range
    SPFLOAT scale = 3.33333333333;  //rate at which we approach 1.
    SPFLOAT x;

    x = *in;

    if ( fabs(x) > threshold ) {
        x = (x>0) ?
            threshold + range * (1-pow(M_E, scale*(threshold-x))):
           -threshold - range * (1-pow(M_E, scale*(threshold+x)));
    }

    *out = x;

    return SP_OK;
}
