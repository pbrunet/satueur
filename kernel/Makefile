#===============================================================================
#
# Makefile for kernel core
#
#===============================================================================

#-------------------------------------------------------------------------------
# features activated
#-------------------------------------------------------------------------------
features =

# mandatory features
features += tools
features += boot
features += console
features += descriptors

# optional features
# feature += pit
ifdef STR_AUTOTEST
features += autotests
endif

#-------------------------------------------------------------------------------
# corresponding inclusion
#-------------------------------------------------------------------------------
$(eval $(makefile_inc))
include $(includes)