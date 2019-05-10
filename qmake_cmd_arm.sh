#!/bin/sh
# Author:  Leon Shaner
#
# Purpose: This is a workaround for ARM platforms regarding the following
# compilation error:
#
#  // In file included from laumemoryobject.cpp:33:0:
#  // laumemoryobject.h:37:23: fatal error: emmintrin.h: No such file or directory
#
# Note, it should have been enough to add $[[DEFINE]] to the DEFINES line in the
# project file, but the default value (a la "qmake -query") may simply be:
#
#    "Q_PROCESSOR_ARM"
#
# and not
#
#    "Q_PROCESSOR_ARM=__ARM_ARCH"
#
# It takes the latter form to satsify the build requirements without introducing
# numerous compliation warnings.
#
# The following command passes the necessary Q_PROCESSOR_ARM definition to qmake:

qmake DEFINES+="Q_PROCESSOR_ARM=__ARM_ARCH"
