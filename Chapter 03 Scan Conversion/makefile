CXX = clang++
FRAMEWORKS = -framework GLUT -framework OpenGL

run:
	$(CXX) $(filter %.cpp,$(MAKECMDGOALS)) -o main $(FRAMEWORKS)
	./main

clean:
	rm -f main

# Prevent make from erroring on extra targets
%:
	@:
