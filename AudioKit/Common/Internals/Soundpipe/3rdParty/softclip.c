/*
 * SoftClip
 *
 * A soft clipping function that forces the output is always -1 < out < 1.
 * only samples exceeding -3db are altered
 *
 * Note the range and scale have been picked so that the slope is 45deg at 0.7
 * 
 * (c) Fraser Stuart 1998
 * Released in 2009 under the GPL v2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
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
