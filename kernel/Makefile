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
features += boot
features += console
features += descriptors
features += logger

# optional features
# feature += pit
ifdef STR_DEBUG
features += autotests
endif

#-------------------------------------------------------------------------------
# corresponding inclusion
#-------------------------------------------------------------------------------
$(eval $(makefile_inc))
include $(includes)