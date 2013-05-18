/* fake the functions used by vnconfig(8) for FLOPPY kernel */

#include <stdlib.h>

__RCSID("$MirOS$");

__dead void
ASN1_OCTET_STRING_new(void)
{
	abort();
}

__dead void
ASN1_STRING_data(void)
{
	abort();
}

__dead void
ASN1_STRING_free(void)
{
	abort();
}

__dead void
ASN1_STRING_length(void)
{
	abort();
}

__dead void
ASN1_STRING_set(void)
{
	abort();
}

__dead void
ERR_error_string(void)
{
	abort();
}

__dead void
ERR_free_strings(void)
{
	abort();
}

__dead void
ERR_get_error(void)
{
	abort();
}

__dead void
ERR_load_crypto_strings(void)
{
	abort();
}

__dead void
ERR_print_errors_fp(void)
{
	abort();
}

__dead void
EVP_cleanup(void)
{
	abort();
}

__dead void
EVP_get_cipherbyname(void)
{
	abort();
}

__dead void
OpenSSL_add_all_ciphers(void)
{
	abort();
}

__dead void
PEM_ASN1_read(void)
{
	abort();
}

__dead void
PEM_ASN1_write(void)
{
	abort();
}

__dead void
d2i_ASN1_OCTET_STRING(void)
{
	abort();
}

__dead void
i2d_ASN1_OCTET_STRING(void)
{
	abort();
}
