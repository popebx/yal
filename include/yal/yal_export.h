#ifndef _yal_export_h_INClude
#define _yal_export_h_INClude
#if defined(WIN32) || defined(WIN64)
#if defined(EXPORT_YAL)
#define EXPORT_YAL_API __declspec(dllexport)
#else
#define EXPORT_YAL_API __declspec(dllimport)
#endif
#else
#define EXPORT_YAL_API
#endif
#endif //_yal_export_h_INClude
