TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS BELOW HERE

# xxxRecord.h will be created from xxxRecord.dbd
DBDINC += xxxRecord

# Install xxxSupport.dbd into <top>/dbd
DBD += xxxSupport.dbd

# Build an IOC support library
LIBRARY_IOC += extendsSupport

# Compile and add the code to the support library
extendsSupport_SRCS += xxxRecord.c
extendsSupport_SRCS += devXxxSoft.c

# Link locally-provided code into the support library,
# rather than directly into the IOC application.
# This is required for Windows DLL builds.
extendsSupport_SRCS += dbSubExample.c
extendsSupport_SRCS += extendsHello.c
extendsSupport_SRCS += initTrace.c
extendsSupport_SRCS += dbSubExtends.c

extendsSupport_LIBS += $(EPICS_BASE_IOC_LIBS)


# Build the IOC application
PROD_IOC = extends

# extends.dbd will be created and installed
DBD += extends.dbd

# extends.dbd will include these files:
extends_DBD += base.dbd
extends_DBD += xxxSupport.dbd
extends_DBD += dbSubExample.dbd
extends_DBD += extendsHello.dbd
extends_DBD += initTrace.dbd
extends_DBD += dbSubExtends.dbd

# extends_registerRecordDeviceDriver.cpp derives from extends.dbd
extends_SRCS += extends_registerRecordDeviceDriver.cpp

# Build the main IOC entry point where needed
extends_SRCS_DEFAULT += extendsMain.cpp
extends_SRCS_vxWorks += -nil-

# Link in the code from our support library
extends_LIBS += extendsSupport

# To build SNL programs, SNCSEQ must be defined
# in the <top>/configure/RELEASE file
ifneq ($(SNCSEQ),)
    # Build sncExample into extendsSupport
    sncExample_SNCFLAGS += +r
    extends_DBD += sncExample.dbd
    # A .stt sequence program is *not* pre-processed:
    extendsSupport_SRCS += sncExample.stt
    extendsSupport_LIBS += seq pv
    extends_LIBS += seq pv

    # Build sncProgram as a standalone program
    PROD_HOST += sncProgram
    sncProgram_SNCFLAGS += +m
    # A .st sequence program *is* pre-processed:
    sncProgram_SRCS += sncProgram.st
    sncProgram_LIBS += seq pv
    sncProgram_LIBS += $(EPICS_BASE_HOST_LIBS)
endif

# Finally link IOC to the EPICS Base libraries
extends_LIBS += $(EPICS_BASE_IOC_LIBS)

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD EXTRA GNUMAKE RULES BELOW HERE

