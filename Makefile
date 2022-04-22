# 如果是.c后缀,需要将allobjcpp换成allobjc
target := testLongestPath
allobjcpp := $(shell ls *.cpp)
allobj := $(allobjcpp:.cpp=.o)
alldep := $(allobjcpp:.cpp=.d)
CXX := g++

all: $(target) 

# %为通配符
%.d: %.cpp
	$(CXX) -MM $< > $@

-include $(alldep)

%.o: %.cpp
	$(CXX) -c $<

$(target): $(allobj)
	$(CXX) -o $@  $^

.POHONY clean:
	rm *.o *.d $(target) 

