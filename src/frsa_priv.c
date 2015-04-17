#include <frsa.h>

FP *generateFP()
{
    return NULL;
}

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

RSA *readRSAPublic(char *infile)
{
    RSA *rsa;
    FILE *fp;

    fp = fopen(infile, "rb");

    if (fp == NULL)
    {
        printf("Unable to open file %s \n", infile);
        return NULL;    
    }

    rsa = RSA_new();

    PEM_read_RSAPublicKey(fp, &rsa, NULL, NULL);

    fclose(fp);

    return rsa;
}

RSA *readRSAPrivate(char *infile)
{
    RSA *rsa;
    FILE *fp;

    fp = fopen(infile, "rb");

    if (fp == NULL)
    {
        printf("Unable to open file %s \n", infile);
        return NULL;    
    }

    rsa = RSA_new();

    PEM_read_RSAPrivateKey(fp, &rsa, NULL, NULL);

    fclose(fp);

    return rsa;
}

void writeRSAPublic(RSA *rsa, char *outfile)
{
    BIO *bp;

    bp = BIO_new_file(outfile, "w+");
    PEM_write_bio_RSAPublicKey(bp, rsa);

    free(bp);
}

void writeRSAPrivate(RSA *rsa, char *outfile)
{
    BIO *bp;

    bp = BIO_new_file(outfile, "w+");
    PEM_write_bio_RSAPrivateKey(bp, rsa, NULL, NULL, 0, NULL, NULL);

    free(bp);
}

RSA *applyFPToRSA(RSA *rsa, FP *fp)
{
    return rsa;
}

void encryptRSA(RSA *rsa, char *infile, char *outfile)
{
    FILE *fp;
    long size;
    unsigned char *plaintext;
    unsigned char *ciphertext;

    fp = fopen(infile, "rb");
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    plaintext = calloc(0, size+1);
    fread(plaintext, size, 1, fp);
    fclose(fp);

    ciphertext = malloc(RSA_size(rsa));
    RSA_public_encrypt(strlen(plaintext), plaintext, ciphertext, rsa, RSA_PKCS1_PADDING); 

    fp = fopen(outfile, "wb");
    fwrite(ciphertext, sizeof(ciphertext), 1, fp);
    fclose(fp);

    return;
}

void decryptRSA(RSA *rsa, char *infile, char *outfile)
{
    return;
}
