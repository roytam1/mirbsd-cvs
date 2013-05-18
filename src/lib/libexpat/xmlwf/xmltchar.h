/* $MirOS: src/lib/libexpat/xmlwf/xmltchar.h,v 1.4 2005/11/03 22:28:14 tg Exp $ */

#ifdef XML_UNICODE
#ifndef XML_UNICODE_WCHAR_T
#error xmlwf requires a 16-bit Unicode-compatible wchar_t 
#endif
#define T(x) L ## x
#define ftprintf fwprintf
#define tfopen _wfopen
#define fputts fputws
#define puttc putwc
#define tcscmp wcscmp
#define tcscpy(a,b,c) wcslcpy((a),(b),(c))
#define tcscat(a,b,c) wcslcat((a),(b),(c))
#define tcschr wcschr
#define tcsrchr wcsrchr
#define tcslen wcslen
#define tperror _wperror
#define topen _wopen
#define tmain wmain
#define tremove _wremove
#else /* not XML_UNICODE */
#define T(x) x
#define ftprintf fprintf
#define tfopen fopen
#define fputts fputs
#define puttc putc
#define tcscmp strcmp
#define tcscpy(a,b,c) strlcpy((a),(b),(c))
#define tcscat(a,b,c) strlcat((a),(b),(c))
#define tcschr strchr
#define tcsrchr strrchr
#define tcslen strlen
#define tperror perror
#define topen open
#define tmain main
#define tremove remove
#endif /* not XML_UNICODE */
