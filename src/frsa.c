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
struct arguments
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
    struct arguments *arguments = state->input;

    switch (key)
    {
        case 'i':
            arguments->infile = arg;
            break;
        case 'o':
            arguments->outfile = arg;
            break;
        case 'v':
            arguments->privkey = arg;
            break;
        case 'b':
            arguments->pubkey = arg;
            break;
        case ARGP_KEY_NO_ARGS:
            argp_usage(state);
        case ARGP_KEY_ARG:
            if (state->arg_num > 0)
                argp_usage(state);
            else
                arguments->cmd = arg;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

// argp parser
static struct argp argp = {options, parse_opt, args_doc, doc};

// main function
void main(int argc, char **argv)
{
    struct arguments arguments;

    arguments.infile = "-";
    arguments.outfile = "-";
    arguments.privkey = "-";
    arguments.pubkey = "-";
    
    argp_parse (&argp, argc, argv, 0, 0, &arguments);
}
