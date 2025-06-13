SYSCONF_LINK = g++
CPPFLAGS     =
CXXFLAGS     = -Wall -O3
LDFLAGS      =
LIBS         = -lm

DESTDIR = ./
TARGET  = main

OBJECTS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all: $(DESTDIR)$(TARGET)

$(DESTDIR)$(TARGET): $(OBJECTS)
	$(SYSCONF_LINK) -g $(CXXFLAGS) $(LDFLAGS) -o $(DESTDIR)$(TARGET) $(OBJECTS) $(LIBS)

$(OBJECTS): %.o: %.cpp
	$(SYSCONF_LINK) -g -Wall $(CXXFLAGS) -c $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)
	-rm -f *.tga

