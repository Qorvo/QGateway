#------- Toolchain ------------------------

TOOLCHAIN       ?=$(error specify TOOLCHAIN dir)
TOOLCHAINBIN    ?=$(TOOLCHAIN)/bin
ARCH            ?=$(error specify ARCH)
CROSS_COMPILE   ?=$(error specify CROSS_COMPILE)

# Define programs and commands.
CC          = $(TOOLCHAINBIN)/$(CROSS_COMPILE)gcc
CXX         = $(TOOLCHAINBIN)/$(CROSS_COMPILE)g++
AR          = $(TOOLCHAINBIN)/$(CROSS_COMPILE)ar rsc
LINK        = $(TOOLCHAINBIN)/$(CROSS_COMPILE)ld
OBJCOPY     = $(TOOLCHAINBIN)/$(CROSS_COMPILE)objcopy
OBJDUMP     = $(TOOLCHAINBIN)/$(CROSS_COMPILE)objdump
SIZE        = $(TOOLCHAINBIN)/$(CROSS_COMPILE)size -A
NM          = $(TOOLCHAINBIN)/$(CROSS_COMPILE)nm

#------- Extensions ------------------------

PROGRAM_EXT :=elf
LIB_EXT     :=a

#------- Specific defines ------------------------

MCU_HAL ?= halLinux

#------- C compiler options ------------------------

# Compiler flag to set the C Standard level.
#     c89   = "ANSI" C
#     gnu89 = c89 plus GCC extensions
#     c99   = ISO C99 standard (not yet fully implemented)
#     gnu99 = c99 plus GCC extensions
CFLAGS_COMPILER +=-std=gnu99
CFLAGS_COMPILER +=$(subst $<,-Werror,$(filter $<,$(SRC_NOWARNING)))
ifneq (,$(PREINCLUDE_HEADER))
CFLAGS_COMPILER +=-include $(PREINCLUDE_HEADER)
endif

#------- C++ compiler options ------------------------

CXXFLAGS_COMPILER +=-std=c++11
ifneq (,$(PREINCLUDE_HEADER))
CXXFLAGS_COMPILER +=-include $(PREINCLUDE_HEADER)
endif

#------- Assemble options ------------------------

ASFLAGS_COMPILER +=

#------- Linker options ------------------------

ifneq (,$(BUILDOPT_STRIP))
  # Strip symbols and debug info from executable file.
  LDFLAGS_COMPILER += -Wl,--strip-all
endif

# FIXME - Check use - Compiler flags to generate dependency files.
GENDEPFLAGS_COMPILER = -MM -MF $(DIRDEP)/$(*F).d -MT $(DIROBJ)/$(*F).o
#------- Library options ------------------------

#Check if real location of library was used
LIBFILES    =$(wildcard $(LIB))
LIBIMPLICIT =$(filter-out $(LIBFILES),$(LIB))

LIBFLAGS_DIR=$(sort $(subst \,/, $(patsubst %, -L%, $(dir $(LIBFILES)))))
#end up with -lLibName for full location and implicit location
LIBNAMES    =$(sort $(addprefix -l,$(patsubst lib%,%,$(notdir $(basename $(LIBFILES)) $(LIBIMPLICIT)))))

LIBFLAGS_COMPILER+=-Wl,--start-group $(LIBNAMES) -Wl,--end-group
ifneq (,$(LIBNAMES_WHOLE))
LIBFLAGS_COMPILER+=-Wl,--whole-archive $(LIBNAMES_WHOLE) -Wl,--no-whole-archive
endif
LIBFLAGS_COMPILER+=$(LIBFLAGS_DIR)

#------- Linkerscripts ------------------------

