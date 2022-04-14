#ifndef REST_API_GLOBAL_H
#define REST_API_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(REST_API_LIBRARY)
#  define REST_API_EXPORT Q_DECL_EXPORT
#else
#  define REST_API_EXPORT Q_DECL_IMPORT
#endif

#endif // REST_API_GLOBAL_H
