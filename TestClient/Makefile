TARGET = Main

BUILD_DIR = build
SRC_DIR   = src

DEBUG = 1
OPT   = -Og

CC =   gcc -std=c17 -pthread
CXX =  g++ -std=c++17 -pthread
AS =   g++ -S

C_SOURCES   := $(wildcard $(SRC_DIR)/*.c)
CPP_SOURCES := $(wildcard $(SRC_DIR)/*.cpp)

# AS includes
AS_INCLUDES =  

# C includes
C_INCLUDES = -Iinc

# C++ includes
CPP_INCLUDES = $(C_INCLUDES)


ASFLAGS  = $(AS_INCLUDES) 
CFLAGS   = $(C_INCLUDES) 
CPPFLAGS = $(CPP_INCLUDES) 
LDFLAGS  =

CFLAGS   +=-Wall -W -fdiagnostics-color=always
CPPFLAGS +=-Wall -W -fdiagnostics-color=always

CFLAGS   += -MMD -MP -MF"$(@:%.o=%.d)" $(OPT)
CPPFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" $(OPT)

ifeq ($(DEBUG), 1)
CFLAGS   += -g 
CPPFLAGS += -g 
endif





OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))





all: $(BUILD_DIR)/$(TARGET).out
	


$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -a $< -o $@

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR) 
	$(CXX) -c $(CPPFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).out: $(OBJECTS) Makefile | $(BUILD_DIR)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

$(BUILD_DIR):
	mkdir $@


.PHONY: run
run:
	sudo ip netns exec client $(BUILD_DIR)/$(TARGET).out

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*
