# 如果是.c后缀,需要将allobjcpp换成allobjc
target := libPathTree.a
allobjcpp := $(shell ls *.cpp)
allobj := $(allobjcpp:.cpp=.o)
alldep := $(allobjcpp:.cpp=.d)
CXX := g++
AR := ar -r

all: $(target) 

# %为通配符
%.d: %.cpp
	$(CXX) -MM $< > $@

-include $(alldep)

%.o: %.cpp
	$(CXX) -c $<

$(target): $(allobj)
	$(AR) -o $@  $^

.POHONY clean:
	rm -rf *.o *.d $(target) 

