#include <frsa.h>

// argp parameters
const char *argp_program_version = 
    "frsa 0.1";
const char *argp_program_bug_address = 
    "<alexgerst93@gmail.com>";
static char doc[] = 
    "fRSA -- a utility for fingerprint RSA cryptography\vValid commands:\n\n  private\t\tgenerates private key to OUTFILE\n  public\t\tcomputes public key to OUTFILE based on PRIVKEY\n  encrypt\t\tencrypts INFILE to OUTFILE based on PUBKEY\n  decrypt\t\tdecrypts INFILE to OUTFILE based on PRIVKEY";
static char args_doc[] =
    "COMMAND";
static struct argp_option options[] = {
    {"in",      'i',    "INFILE",   0,  "Input file" },
    {"out",     'o',    "OUTFILE",  0,  "Output file" },
    {"priv",    'v',    "PRIVKEY", 0,   "Private key" },
    {"pub",     'b',    "PUBKEY",  0,   "Public key" },
    {0}
};
struct args
{
    char *cmd;
    char *infile;
    char *outfile;
    char *privkey;
    char *pubkey;
};

// parse a single option
static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct args *args = state->input;

    switch (key)
    {
        case 'i':
            args->infile = arg;
            break;
        case 'o':
            args->outfile = arg;
            break;
        case 'v':
            args->privkey = arg;
            break;
        case 'b':
            args->pubkey = arg;
            break;
        case ARGP_KEY_NO_ARGS:
            argp_usage(state);
        case ARGP_KEY_ARG:
            if (state->arg_num > 0 ||
               (strcmp(arg, "private") && 
               strcmp(arg, "public") && 
               strcmp(arg, "encrypt") &&
               strcmp(arg, "decrypt")))
                argp_usage(state);
            else
                args->cmd = arg;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

// argp parser
static struct argp argp = {options, parse_opt, args_doc, doc};

// error handler
void frsa_error(char *str)
{
    printf("frsa: %s\nTry `frsa --help' or `frsa --usage' for more information.\n", str);
    exit(1);
}

// command - private
void cmd_private(struct args args)
{
    if (args.outfile == NULL)
    {
        frsa_error("'private' command requires outfile");
    }

    RSA *rsa;

    rsa = generateRSA();

    writeRSAPrivateToFile(rsa, args.outfile);
}

// command - public
void cmd_public(struct args args)
{
    if (args.outfile == NULL)
    {
        frsa_error("'public' command requires outfile");
    }
    
    if (args.privkey == NULL)
    {
        frsa_error("'public' command requires privkey");
    }
}

// command - encrypt
void cmd_encrypt(struct args args)
{
    if (args.infile == NULL)
    {
        frsa_error("'encrypt' command requires infile");
    }
    
    if (args.outfile == NULL)
    {
        frsa_error("'encrypt' command requires outfile");
    }
    
    if (args.pubkey == NULL)
    {
        frsa_error("'encrypt' command requires pubkey");
    }

}

// command - decrypt
void cmd_decrypt(struct args args)
{
    if (args.infile == NULL)
    {
        frsa_error("'decrypt' command requires infile");
    }
    
    if (args.outfile == NULL)
    {
        frsa_error("'decrypt' command requires outfile");
    }
    
    if (args.privkey == NULL)
    {
        frsa_error("'decrypt' command requires privkey");
    }

}

// main function
void main(int argc, char **argv)
{
    struct args args;

    args.cmd = NULL;
    args.infile = NULL;
    args.outfile = NULL;
    args.privkey = NULL;
    args.pubkey = NULL;
    
    argp_parse (&argp, argc, argv, 0, 0, &args);

    if (strcmp(args.cmd, "private") == 0)
    {
        cmd_private(args);
    }
    else if (strcmp(args.cmd, "public") == 0)
    {
        cmd_public(args);
    }
    else if (strcmp(args.cmd, "encrypt") == 0)
    {
        cmd_encrypt(args);
    }
    else if (strcmp(args.cmd, "decrypt") == 0)
    {
        cmd_decrypt(args);
    }
    else
    {
        exit(1);
    }

    exit(0);
}
