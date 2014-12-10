#===============================================================================
#
# Makefile for utils mk functions
#
#===============================================================================

#-------------------------------------------------------------------------------
# vars
#-------------------------------------------------------------------------------
dir = $(dir $(lastword $(MAKEFILE_LIST)))
dirname = $(lastword $(subst /, ,$(dir)))

#-------------------------------------------------------------------------------
# functions to build .o objects name from sources
#-------------------------------------------------------------------------------
define add_objects
objects+=$(patsubst %.$2,%.o,$1)
endef

cpp_objects = $(call add_objects,$(wildcard $(dir)*.cpp),cpp)
c_objects = $(call add_objects,$(wildcard $(dir)*.c),c)
asm_objects = $(call add_objects,$(wildcard $(dir)*.s),s)

#-------------------------------------------------------------------------------
# functions to build includes corresponding to activated features
#-------------------------------------------------------------------------------
define makefile_includes
includes = $(foreach d, $2, $1$d/Makefile)
endef

makefile_inc = $(call makefile_includes,$(dir),$(features))
