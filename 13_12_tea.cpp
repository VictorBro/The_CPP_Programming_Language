#include <iostream>


void encipher(unsigned long *const v,unsigned long *const w,
    const unsigned long *const k)
{
    unsigned long   y=v[0],z=v[1],sum=0,delta=0x9E3779B9,
                    a=k[0],b=k[1],c=k[2],d=k[3],n=32;

    while(n-->0) {
        sum += delta;
        y += (z << 4)+a ^ z+sum ^ (z >> 5)+b;
        z += (y << 4)+c ^ y+sum ^ (y >> 5)+d;
    }

    w[0]=y; w[1]=z;
}

void decipher(unsigned long *const v,unsigned long *const w,
    const unsigned long *const k)
{
    unsigned long   y=v[0],z=v[1],sum=0xC6EF3720,
                    delta=0x9E3779B9,a=k[0],b=k[1],
                    c=k[2],d=k[3],n=32;

    /* sum = delta<<5, in general sum = delta * n */

    while(n-->0) {
        z -= (y << 4)+c ^ y+sum ^ (y >> 5)+d;
        y -= (z << 4)+a ^ z+sum ^ (z >> 5)+b;
        sum -= delta;
    }

    w[0]=y; w[1]=z;
}

int main() {
    unsigned long v[] = {0xe15034c8, 0x260fd6d5};
    unsigned long k[] = {0xbe168aa1, 0x16c498a3, 0x5e87b018, 0x56de7805};
    unsigned long w[2];

    encipher(v, w, k);
    printf("%X %X\n", w[0], w[1]);
    decipher(w, v, k);
    printf("%X %X\n", v[0], v[1]);
}