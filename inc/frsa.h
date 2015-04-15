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

RSA *generateRSA();
RSA *readRSAFromFile(char *filename, int public);
void *writeRSAPublicToFile(RSA *rsa, char *filename);
void *writeRSAPrivateToFile(RSA *rsa, char *filename);
FP *generateFP();
RSA *applyTPToRSA(RSA *rsa, FP *fp);
