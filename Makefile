#
# Makefile
#   This makefile only works right now with gmake :(
#

SHELL  = bash
TARGET = idolon
CC     = g++

# Flags that are used regardless of compiliation options go here
CCFL := -c -g -Wall -Wno-sign-compare
LDFL := -Wall -lGL -lGLU -lGLEW -lSDL2 -lpng

# List of source files
SRCS := BoneSprite.cpp Input.cpp main.cpp StatSprite.cpp Sprite.cpp GameOptions.cpp Level.cpp ShaderHelp.cpp Textures.cpp Entity.cpp Rect.cpp

# Construct file lists
OBJS := $(addprefix build/obj/,$(patsubst %.cpp,%.o,$(SRCS)))
DEPS := $(addprefix build/dep/,$(patsubst %.cpp,%.d,$(SRCS)))
SRCS := $(addprefix src/,$(SRCS))

# All the make rules
.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFL) -o $(TARGET)

$(SERVER_TARGET): $(SERVER_OBJS)
	$(CC) $(SERVER_OBJS) $(SERVER_LDFL) -o $(SERVER_TARGET)

build/obj/%.o: src/%.cpp
	@ mkdir -p $(@D)
	@ mkdir -p $(subst obj,dep,$(@D))
	@ $(CC) -MM -MP -MT $@ -MF $(patsubst %.o,%.d,$(subst obj,dep,$@)) $<
	$(CC) $(CCFL) $< -o $@

clean:
	rm -rf build
	rm -f $(TARGET)

# Include automagically generated dependencies
-include $(DEPS)

