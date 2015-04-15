#include <frsa.h>

#define FRSA_BITS 2048

RSA *generateRSA()
{
    BIGNUM *bne;
    RSA *rsa;
    
    bne = BN_new();
    BN_set_word(bne, RSA_F4);

    rsa = RSA_new();
    RSA_generate_key_ex(rsa, FRSA_BITS, bne, NULL);

    free(bne);

    return rsa;
}

RSA *readRSAFromFile(char *filename, int public)
{
    RSA *rsa;
    FILE *fp;

    fp = fopen(filename, "rb");
    
    if (fp == NULL)
    {
        printf("Unable to open file %s \n", filename);
        return NULL;    
    }

    rsa = RSA_new();

    if (public)
    {
        PEM_read_RSA_PUBKEY(fp, &rsa, NULL, NULL);
    }
    else
    {
        PEM_read_RSAPrivateKey(fp, &rsa, NULL, NULL);
    }

    free(fp);

    return rsa;
}

void *writeRSAPublicToFile(RSA *rsa, char *filename)
{
    BIO *bp;

    bp = BIO_new_file(filename, "w+");
    PEM_write_bio_RSAPublicKey(bp, rsa);
    
    free(bp);
}

void *writeRSAPrivateToFile(RSA *rsa, char *filename)
{
    BIO *bp;

    bp = BIO_new_file(filename, "w+");
    PEM_write_bio_RSAPrivateKey(bp, rsa, NULL, NULL, 0, NULL, NULL);

    free(bp);
}

FP *generateFP()
{
    return NULL;
}

RSA *applyFPToRSA(RSA *rsa, FP *fp)
{
    return rsa;
}

void main()
{
    RSA *rsa;
    
    printf("FRSA v0.1\n");

    rsa = generateRSA();
    writeRSAPublicToFile(rsa, "pub.pem");
    writeRSAPrivateToFile(rsa, "priv.pem");

    free(rsa);

    printf("Success, exiting.\n");
}
