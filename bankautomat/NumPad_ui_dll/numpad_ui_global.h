#ifndef NUMPAD_UI_GLOBAL_H
#define NUMPAD_UI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NUMPAD_UI_LIBRARY)
#  define NUMPAD_UI_EXPORT Q_DECL_EXPORT
#else
#  define NUMPAD_UI_EXPORT Q_DECL_IMPORT
#endif

#endif // NUMPAD_UI_GLOBAL_H
