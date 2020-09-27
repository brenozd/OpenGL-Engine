# Compiler settings - Can be customized.
CC = g++
CXXFLAGS = -std=c++11
LDFLAGS = -lglfw -lGL -lGLEW

# Makefile settings - Can be customized.
APPNAME = OpenGL
EXT = .cpp
BUILDDIR = builds
SRCDIR = src
OBJDIR = obj
LINKDIR = $(OBJDIR)/links

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)

# UNIX-based OS variables & settings
RM = rm
DELOBJ = $(OBJ)
DELLINK = $(SRC:$(SRCDIR)/%$(EXT)=$(LINKDIR)/%.d)

# Windows OS variables & settings
DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $(BUILDDIR)/$@ $^ $(LDFLAGS)

#Build a debuggable app
.PHONY: debuggable
debuggable: $(OBJ)
	$(RM) $(BUILDDIR)/$(APPNAME).debug
	$(CC) $(CXXFLAGS) -g -o $(BUILDDIR)/$(APPNAME).debug $^ $(LDFLAGS)

# Creates the dependecy rules
%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$(LINKDIR)/$@

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DELLINK) $(BUILDDIR)/$(APPNAME)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

#################### Cleaning rules for Windows OS #####################
# Cleans complete project
.PHONY: cleanw
cleanw:
	$(DEL) $(WDELOBJ) $(DEP) $(APPNAME)$(EXE)

# Cleans only all files with the extension .d
.PHONY: cleandepw
cleandepw:
	$(DEL) $(DEP)