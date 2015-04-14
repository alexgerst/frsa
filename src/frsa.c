#include <frsa.h>

RSA *createRSAWithFilename(char *filename, int public)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        printf("Unable to open file %s \n", filename);
        return NULL;    
    }
    RSA *rsa = RSA_new();

    if (public)
    {
        PEM_read_RSA_PUBKEY(fp, &rsa, NULL, NULL);
    }
    else
    {
        PEM_read_RSAPrivateKey(fp, &rsa, NULL, NULL);
    }

    return rsa;
}

void main()
{
    printf("FRSA\n");
}
