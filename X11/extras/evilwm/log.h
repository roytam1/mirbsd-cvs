/* evilwm - Minimalist Window Manager for X
 * Copyright (C) 1999-2005 Ciaran Anscomb <evilwm@6809.org.uk>
 * see README for license and other details. */

#ifndef LOG_H
#define LOG_H "$MirOS$"

#if defined(STDIO) || defined(DEBUG) || defined(XDEBUG)
# include <stdio.h>
#endif

#ifdef STDIO
# define LOG_INFO(...) printf(__VA_ARGS__);
# define LOG_ERROR(...) fprintf(stderr, __VA_ARGS__);
#else
# define LOG_INFO(...)
# define LOG_ERROR(...)
#endif

#ifdef DEBUG
# define LOG_DEBUG(...) fprintf(stderr, __VA_ARGS__);
#else
# define LOG_DEBUG(...)
#endif

#ifdef XDEBUG
# define LOG_XDEBUG(...) fprintf(stderr, __VA_ARGS__);
#else
# define LOG_XDEBUG(...)
#endif

#endif
