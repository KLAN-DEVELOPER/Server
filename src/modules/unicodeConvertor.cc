#include "unicodeConvertor.h"


char* convertToCP1251(const char* utf8)
{
    UErrorCode status = U_ZERO_ERROR;
    UConverter *conv = ucnv_open("cp1251", &status);
    if (status)
    {
	printf("Failed to obtain char set converter: %d\r\n", status);
	return nullptr;
    }
    icu::UnicodeString unicode_buffer(utf8);
    unsigned int ulen = unicode_buffer.length();
    char* cp1251 = new char[ulen + 1];
    unicode_buffer.extract(cp1251, ulen, conv, status);
    ucnv_close(conv);
    return cp1251;
}