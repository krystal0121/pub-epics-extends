#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <registryFunction.h>
#include <subRecord.h>
#include <aSubRecord.h>
#include <epicsExport.h>
#include <dbFldTypes.h>

#define NUM_ARGS 21

int myDebugger;

static long addAsub(aSubRecord *prec);


static long mySubTest(subRecord *precord)
{
    if (myDebugger)
        printf("Record %s called mySubTest(%p)\n",
               precord->name, (void *) precord);
    return 0;
}


static long addAsub(aSubRecord *prec)
{
    epicsEnum16 *pft = &prec->ftva; /* output type */
    epicsUInt32 *pnov = &prec->nova; /* output array capacity */
    epicsUInt32 *pnev = &prec->neva; /* output array size */
    void **pval = &prec->vala;      /* output array */

    /* get output field and field type */
    for (int i = 0; i < NUM_ARGS; i++, pnov++, pft++, pnev++, pval++) {
        if (*pnov > 1) {
            if (*pft < DBF_SHORT || *pft > DBF_DOUBLE)
            {
                printf("Record %s / addAsub(): "
                       "field type is not supported,"
                       "supported as below:\n"
                       "1. SHORT"
                       "2. USHORT"
                       "3. LONG"
                       "4. ULONG"
                       "5. FLOAT"
                       "6. DOUBLE\n",
                       prec->name);
                return -1;
            }
            break;
        }
    }

    /* check input array size and type */
    for (int i = 0; i < NUM_ARGS; i++) {
        if ((&prec->noa)[i] == 1) continue;
        if ((&prec->noa)[i] != *pnov) {
            printf("Record %s / addAsub(): "
                   "if field NOx and NOVx are set, then must be same\n",
                   prec->name);
            return -1;
        }
        if ((&prec->fta)[i] != *pft) {
            printf("Record %s / addAsub(): "
                   "if field FTx and FTVx are set, then must be same\n",
                   prec->name);
            return -1;
        }
    }
    /* do add */
    switch (*pft) {
        case DBF_SHORT: {
            typedef short ftype;
            ftype *res = (ftype *)malloc(sizeof(ftype) * (*pnov));
            for (int i = 0; i < *pnov; i++) res[i] = 0;
            for (int i = 0; i < NUM_ARGS; i++) {
                if ((&prec->noa)[i] == 1) continue;
                ftype *px = (&prec->a)[i];
                for (int j = 0; j < *pnov; j++) {
                    res[j] += px[j];
                }
            }
            memcpy(*pval, res, sizeof(ftype) * (*pnov));
            free(res);
            break;
        }
        case DBF_USHORT: {
            typedef unsigned short ftype;
            ftype *res = (ftype *)malloc(sizeof(ftype) * (*pnov));
            for (int i = 0; i < *pnov; i++) res[i] = 0;
            for (int i = 0; i < NUM_ARGS; i++) {
                if ((&prec->noa)[i] == 1) continue;
                ftype *px = (&prec->a)[i];
                for (int j = 0; j < *pnov; j++) {
                    res[j] += px[j];
                }
            }
            memcpy(*pval, res, sizeof(ftype) * (*pnov));
            free(res);
            break;;
        }
        case DBF_LONG: {
            typedef long ftype;
            ftype *res = (ftype *)malloc(sizeof(ftype) * (*pnov));
            for (int i = 0; i < *pnov; i++) res[i] = 0;
            for (int i = 0; i < NUM_ARGS; i++) {
                if ((&prec->noa)[i] == 1) continue;
                ftype *px = (&prec->a)[i];
                for (int j = 0; j < *pnov; j++) {
                    res[j] += px[j];
                }
            }
            memcpy(*pval, res, sizeof(ftype) * (*pnov));
            free(res);
            break;
        }
        case DBF_ULONG: {
            typedef unsigned long ftype;
            ftype *res = (ftype *)malloc(sizeof(ftype) * (*pnov));
            for (int i = 0; i < *pnov; i++) res[i] = 0;
            for (int i = 0; i < NUM_ARGS; i++) {
                if ((&prec->noa)[i] == 1) continue;
                ftype *px = (&prec->a)[i];
                for (int j = 0; j < *pnov; j++) {
                    res[j] += px[j];
                }
            }
            memcpy(*pval, res, sizeof(ftype) * (*pnov));
            free(res);
            break;
        }
        case DBF_FLOAT: {
            typedef float ftype;
            ftype *res = (ftype *)malloc(sizeof(ftype) * (*pnov));
            for (int i = 0; i < *pnov; i++) res[i] = 0;
            for (int i = 0; i < NUM_ARGS; i++) {
                if ((&prec->noa)[i] == 1) continue;
                ftype *px = (&prec->a)[i];
                for (int j = 0; j < *pnov; j++) {
                    res[j] += px[j];
                }
            }
            memcpy(*pval, res, sizeof(ftype) * (*pnov));
            free(res);
            break;
        }
        case DBF_DOUBLE: {
            typedef double ftype;
            ftype *res = (ftype *)malloc(sizeof(ftype) * (*pnov));
            for (int i = 0; i < *pnov; i++) res[i] = 0;
            for (int i = 0; i < NUM_ARGS; i++) {
                if ((&prec->noa)[i] == 1) continue;
                ftype *px = (&prec->a)[i];
                for (int j = 0; j < *pnov; j++) {
                    res[j] += px[j];
                }
            }
            memcpy(*pval, res, sizeof(ftype) * (*pnov));
            free(res);
            break;
        }
        default:
            return -1;
    }

    /* set output array size */
    *pnev = *pnov;

    return 0;
}


epicsExportAddress(int, myDebugger);
epicsRegisterFunction(mySubTest);
epicsRegisterFunction(addAsub);