#ifndef MUSICRUNGLOBALDEFINE_H
#define MUSICRUNGLOBALDEFINE_H

/* =================================================
 * This file is part of the MMM Music Player project
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicglobal.h"

//////////////////////////////////////
///exoprt
///
///
#define MUSIC_EXPORT

#ifdef MUSIC_EXPORT
#  define MUSIC_RUN_EXPORT Q_DECL_EXPORT
#else
#  define MUSIC_RUN_EXPORT Q_DECL_IMPORT
#endif

#endif // MUSICRUNGLOBALDEFINE_H
