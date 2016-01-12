/* Copyright (c) 2015 Wojciech Owczarek,
 *
 * All Rights Reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file   clockdriver.c
 * @date   Sat Jan 9 16:14:10 2015
 *
 * @brief  structure definitions for the clock driver
 *
 */

#ifndef PTPD_CLOCKDRIVER_H_
#define PTPD_CLOCKDRIVER_H_

#include "../ptpd.h"

#define CLOCKDRIVER_NAME_MAX 20

enum {
    CLOCKDRIVER_UNIX = 0,
    CLOCKDRIVER_LINUXPHC = 1
};


typedef struct {

} ClockStatus;

/* MOTHER FUCKING HEADER MESS, GOD DAMN IT TO FUCK!!!! */
typedef struct ClockDriver ClockDriver;

struct ClockDriver {

    ClockStatus _status;
    Boolean	_init;

    int _serial;

    int type;

    char name[CLOCKDRIVER_NAME_MAX];

    int timeScale;
    int utcOffset;
    Boolean systemClock;
    Boolean readOnly;
    Boolean hasRTC;

    void *data;
    void *config;

    double maxFreqAdj;

    /* public interface - implementations must implement all of those */

    int (*shutdown) 	(ClockDriver*);
    int (*init)		(ClockDriver*, const void *);

    Boolean (*getTime) (ClockDriver*, TimeInternal *);
    Boolean (*getUtcTime) (ClockDriver*, TimeInternal *);
    Boolean (*setTime) (ClockDriver*, TimeInternal *);
    Boolean (*setOffset) (ClockDriver*, TimeInternal *);
    Boolean (*setFrequency) (ClockDriver *, double, double);
    double (*getFrequency) (ClockDriver *);
    Boolean (*getStatus) (ClockDriver *, ClockStatus *);
    Boolean (*setStatus) (ClockDriver *, ClockStatus *);
    Boolean (*getOffsetFrom) (ClockDriver *, ClockDriver *, TimeInternal*);

    /* public interface end */

    ClockDriver *_first;
    ClockDriver *_next;
    ClockDriver *_prev;
};


ClockDriver*  createClockDriver(int driverType, const char* name);
Boolean setupClockDriver(ClockDriver* clockDriver, int type, const char* name);
void freeClockDriver(ClockDriver** clockDriver);
ClockDriver* getSystemClock();
void shutdownClockDrivers();

#include "clockdriver_unix.h"
#include "clockdriver_linuxphc.h"

#endif /* PTPD_CLOCKDRIVER_H_ */