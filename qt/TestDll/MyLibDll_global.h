#ifndef MYLIBDLL_GLOBAL_H
#define MYLIBDLL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MYLIBDLL_LIBRARY)
#define MYLIBDLL_EXPORT Q_DECL_EXPORT
#else
#define MYLIBDLL_EXPORT Q_DECL_IMPORT
#endif

#endif // MYLIBDLL_GLOBAL_H
