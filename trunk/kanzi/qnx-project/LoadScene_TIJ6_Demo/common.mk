# This is an automatically generated record.
# The area between QNX Internal Start and QNX Internal End is controlled by
# the QNX IDE properties.

ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

#===== USEFILE - the file containing the usage message for the application. 
USEFILE=
NAME=ChangAnDemo

#==== search paths includes and files 

#===== EXTRA_SRCVPATH - a space-separated list of directories to search for source files.
EXTRA_SRCVPATH+=$(PROJECT_ROOT)/src

#===== EXTRA_INCVPATH - a space-separated list of directories to search for include files.
EXTRA_INCVPATH+=$(PROJECT_ROOT)/headers/application_framework/common/include  \
	$(PROJECT_ROOT)/headers/core/include  \
	$(PROJECT_ROOT)/headers/user/include  \
	$(PROJECT_ROOT)/headers/system/common/include  \
#	$(PROJECT_ROOT)/headers/system/operating_system/qnx/include  \
#	$(PROJECT_ROOT)/headers/system/graphics_context/egl/include  \
#	$(PROJECT_ROOT)/headers/system/windowing_system/screen/include
	
#==== lib paths 

#===== EXTRA_LIBVPATH - a space-separated list of directories to search for library files.
EXTRA_LIBVPATH+=$(PROJECT_ROOT)/lib/screen/common/armle-v7/usr/lib  \
$(PROJECT_ROOT)/lib/ipc \
	$(PROJECT_ROOT)/lib/kanzi/engine/release

#=== linked libs 
LIBS+=ipc applicationframework user core system
LIBS+=freetype jpeg png z
LIBS+=m screen
LIBS+=EGL GLESv2

# Suppress unused function warning
CCFLAGS+=-Wno-unused-function

# Next lines are for C++ projects only

EXTRA_SUFFIXES+=cxx cpp

#===== LDFLAGS - add the flags to the linker command line.
LDFLAGS+=-lang-c++ -Y _gpp

VFLAG_g=-gstabs+

#===== CCFLAGS - add the flags to the C compiler command line. 
CCFLAGS+=-Y _gpp

include $(MKFILES_ROOT)/qmacros.mk
ifndef QNX_INTERNAL
QNX_INTERNAL=$(PROJECT_ROOT)/.qnx_internal.mk
endif
include $(QNX_INTERNAL)

include $(MKFILES_ROOT)/qtargets.mk

OPTIMIZE_TYPE_g=none
OPTIMIZE_TYPE=$(OPTIMIZE_TYPE_$(filter g, $(VARIANTS)))

