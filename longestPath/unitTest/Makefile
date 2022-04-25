# 如果是.c后缀,需要将allobjcpp换成allobjc
target := unitTestLongestPath
allobjcpp := $(shell ls *.cpp)
allobj := $(allobjcpp:.cpp=.o)
alldep := $(allobjcpp:.cpp=.d)
CXX := g++

THE_INCLUDE      := -I./  \
                   -I../pathTreelib \
                   -I../catch2lib

THE_LIBPATH      = -L./  \
                   -L../pathTreelib \
                   -L../catch2lib

THE_LIB          := -lPathTree -lCatch2

CXXFLAGS := -g ${THE_INCLUDE}
LDLIB    := ${THE_LIBPATH} ${THE_LIB}

all: $(target) 

# %为通配符
%.d: %.cpp
	$(CXX) -MM $< > $@

-include $(alldep)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $<

$(target): $(allobj)
	$(CXX) -o $@  $^ $(LDLIB)

.POHONY clean:
	rm -rf *.o *.d $(target) 

