#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include "signalmanage.h"

extern bool IS_useinPath;

extern QString outFliePath;

extern int gcyptLV;

extern int maxthread_num;

extern Signalmange signalmanage;

//////// Macros ////////
#define SAFE_DELETE(p) if (p) { delete [] p; p = NULL; }
#define SAFE_DELETE_SINGLE(p) if (p) { delete p; p = NULL; }

//////// Type ////////
typedef unsigned char BYTE;
//typedef long long LINT;


#endif // GLOBAL_H
