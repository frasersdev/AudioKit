#ifndef FSR_H
#define FSR_H


typedef struct{
    SPFLOAT threshold;
} fsr_softclip;

int fsr_softclip_create(fsr_softclip **p);
int fsr_softclip_destroy(fsr_softclip **p);
int fsr_softclip_init(sp_data *sp, fsr_softclip *p);
int fsr_softclip_compute(sp_data *sp, fsr_softclip *p, SPFLOAT *in, SPFLOAT *out);


#endif
