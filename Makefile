#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := Circle.cpp Line.cpp MoveableObject.cpp Picture.cpp Rectangle.cpp Operators.cpp Exceptions.cpp

# header files in this project
HEADERS :=  Circle.hpp Collection.hpp Exceptions.hpp Factory.hpp Line.hpp MoveableObject.hpp Operators.hpp Picture.hpp Rectangle.hpp Storage.hpp Shapes.hpp Action.hpp

# other places to look for files for this project
SEARCH  := Shapes/

# set REATIVE to the next higher directory 
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.native
