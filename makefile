LIBS=-lSDL2 -lSDL2_image
BUILDDIR=build
CFLAGS=-MMD -MP -c -std=gnu++14 -Wall -Wextra -Wpedantic

CXX = g++
srcs = $(wildcard *.cpp)
objs = $(addprefix $(BUILDDIR)/,$(srcs:.cpp=.o))
deps = $(addprefix $(BUILDDIR)/,$(srcs:.cpp=.d))

gra: $(objs)
	$(CXX) $^ -o $@ $(LIBS)

$(BUILDDIR)/%.o: %.cpp
	$(CXX) $(CFLAGS) $< -o $@

.PHONY: clean

# $(RM) is rm -f by defaultq
clean:
	$(RM) $(objs) $(deps)

-include $(deps)
