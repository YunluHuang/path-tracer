CC = g++ -MMD -O3 -std=c++11
CFLAGS = -g -Wall -DGL_GLEXT_PROTOTYPES
#INCFLAGS = -I./glm-0.9.7.1 -I/usr/X11/include

MODULES 	:= Basics DataStructure Lights Materials Objects PathTracing Tools
CPP_DIR		:= $(addprefix ./private/, $(MODULES))
H_DIR			:= $(addprefix ./public/, $(MODULES))
BUILD_DIR := $(addprefix ./build/, $(MODULES))

INCLUDES	:= $(addprefix -I,$(H_DIR) ./glm-0.9.7.1 /usr/X11/include)

CPP_FILES := $(foreach sdir,$(CPP_DIR),$(wildcard $(sdir)/*.cpp))
OBJ_FILES := $(patsubst ./private/%.cpp, ./build/%.o, $(CPP_FILES))
MAIN 			:= ./private/main.cpp

vpath %.cpp $(CPP_DIR)
vpath %.h $(H_DIR)

RM = /bin/rm -f
RMDIR = /bin/rm -rf

define make-goal
$1/%.o: %.cpp %.h
	$(CC) $(INCLUDES) -c $$< -o $$@
endef

all: build pathtrace

build: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

pathtrace: $(OBJ_FILES) $(MAIN)
	$(CC) $(CFLAGS) $^ $(INCLUDES) -o $@

rebuild: clean all

clean:
	$(RM) pathtrace *.o *.d
	$(RMDIR) *.dSYM build

cleanbmp:
	find *.bmp -maxdepth 1 ! -name *final.bmp -type f -delete

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))
