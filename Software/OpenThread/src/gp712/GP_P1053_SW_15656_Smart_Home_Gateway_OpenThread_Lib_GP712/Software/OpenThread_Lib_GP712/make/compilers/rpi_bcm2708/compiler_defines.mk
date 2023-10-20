#------- Toolchain ------------------------

# Define directories, if needed.

include $(ENV_PATH)/make/compilers/bcmcommon/compiler_defines.mk

#---------------- Compiler Options ----------------
#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual and avr-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing

FLAGS_COMPILER += -Os
FLAGS_COMPILER += -march=armv6j
FLAGS_COMPILER += -Wall
#Find alignment problems due to casting
#FLAGS_COMPILER += -Wcast-align
FLAGS_COMPILER += -fomit-frame-pointer
FLAGS_COMPILER += -fno-strict-aliasing
#CFLAGS_COMPILER += -mno-abicalls
ifneq (,$(FLAGS_COMPILER_PIC_CODE))
FLAGS_COMPILER += -fPIC
else
FLAGS_COMPILER += -fno-pic
endif
FLAGS_COMPILER += -ffreestanding
ifneq (,$(PREINCLUDE_HEADER))
FLAGS_COMPILER += -include $(PREINCLUDE_HEADER)
endif

#-- folowing compiler flags added by BRDB
FLAGS_COMPILER += -mfloat-abi=hard
FLAGS_COMPILER += -mfpu=vfp
FLAGS_COMPILER += -pipe
FLAGS_COMPILER +=--sysroot=$(SYSTEMROOT)

ifeq (,$(FLAGS_COMPILER_DISABLE_ALIGNMENT_WARNING))
FLAGS_COMPILER += $(if $(filter $<,$(SRC_DISABLE_ALIGNMENT_WARNING)),,-Wcast-align)
endif

#Option to remove FLAGS
FLAGS_COMPILER_FILTERED = $(filter-out $(FLAGS_COMPILER_FILTER_OUT), $(FLAGS_COMPILER))
ifneq (,$(FLAGS_COMPILER_FILTER_OUT))
$(warning Filtering out compiler flags: $(FLAGS_COMPILER_FILTER_OUT))
endif
#------- C compiler options ------------------------

CFLAGS_COMPILER += $(FLAGS_COMPILER_FILTERED)

#------- C++ compiler options ------------------------

CXXFLAGS_COMPILER += $(FLAGS_COMPILER_FILTERED)
CXXFLAGS_COMPILER +=-Wno-reorder
CXXFLAGS_COMPILER +=-Wno-unknown-pragmas
CXXFLAGS_COMPILER +=-Wno-sign-compare
CXXFLAGS_COMPILER +=-Wno-unused-function
CXXFLAGS_COMPILER +=-std=c++11
CXXFLAGS_COMPILER +=-g


#------- Assemble options ------------------------

ASFLAGS_COMPILER+=

#------- Linker options ------------------------

LDFLAGS_COMPILER+=--sysroot=$(SYSTEMROOT)

#Split in file and extension - if rule linking has no $*
word-dot = $(word $2,$(subst ., ,$1))
MAP_FILENAME=$(call word-dot,$@,1).map

LDFLAGS_COMPILER+=-Wl,-Map=$(MAP_FILENAME),--cref
#Drop unused sections
LDFLAGS_COMPILER+=-Wl,--gc-sections
#LDFLAGS_COMPILER+=-Wl,--print-gc-sections

#------- Library options ------------------------

LIBFLAGS_COMPILER+=

#------- Linkerscripts ------------------------

