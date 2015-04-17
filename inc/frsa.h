#include <stdio.h>
#include <stdlib.h>
#include <argp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

#define FRSA_BITS 2048

typedef struct
{
    int x;
} FP;

FP *generateFP();
RSA *generateRSA();
RSA *readRSAPublic(char *infile);
RSA *readRSAPrivate(char *infile);
void writeRSAPublic(RSA *rsa, char *outfile);
void writeRSAPrivate(RSA *rsa, char *outfile);
RSA *applyFPToRSA(RSA *rsa, FP *fp);
void encryptRSA(RSA *rsa, char *infile, char *outfile);
void decryptRSA(RSA *rsa, char *infile, char *outfile);
