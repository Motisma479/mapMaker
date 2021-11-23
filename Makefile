
PROGRAM=mapMaker

# Add your objs to generate in OBJS var

SD = ./src/

OBJS=$(SD)main.o $(SD)draw.o $(SD)utils.o#add an objs for each .cpp file

CXX?=g++
TARGET?=$(shell $(CXX) -dumpmachine)

OPTIM_FLAG?=-O0
CFLAGS=$(OPTIM_FLAG) -g -Wall -Wextra -Wno-unused-parameter
CPPFLAGS=-Iinclude -Ithird_party/include -MMD
LDFLAGS=-Lthird_party/libs-$(TARGET)
LDLIBS=-lraylib

ifeq ($(TARGET),x86_64-linux-gnu)
LDLIBS+=-ldl -lpthread -lm
else ifeq ($(TARGET),x86_64-w64-mingw32)#else ifeq ($(TARGET),x86_64-pc-cygwin)
LDLIBS+=-lgdi32 -lWinmm -lWs2_32
else ifeq ($(TARGET),wasm32-unknown-emscripten)
OPTIM_FLAGS=-Os
LDFLAGS+=-s ASYNCIFY
LDFLAGS+=-s USE_GLFW=3
LDFLAGS+=--preload-file assets
EXT=.html
endif

DEPS=$(OBJS:.o=.d)

.PHONY: all clean

all: $(PROGRAM)$(EXT)

-include $(DEPS)

%.o: %.c
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(PROGRAM)$(EXT): $(OBJS)
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

build.tar.gz: $(PROGRAM) $(wildcard assets/*)
	tar czf build.tar.gz $(PROGRAM) assets
	
host: $(PROGRAM)$(EXT)
	python3 -m http.server 8000

clean:
	rm -f $(OBJS) $(DEPS) $(PROGRAM) build.tar.gz
	rm -f $(PROGRAM).html $(PROGRAM).js $(PROGRAM).data $(PROGRAM).wasm
