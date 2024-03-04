NAME = Project
CLANG_FORMAT ?= clang-format

.PHONY: all
all: clean install

.PHONY: dvi
dvi:
	open readme.html

.PHONY: clean
clean:
	@rm -rf ../Archive_Maze
	@rm -rf *tgz
	@rm -rf build*
	@rm -rf ./Maze/build*
	@rm -rf ../Archive_Maze.zip
	@rm -rf ../Archive_Maze.tgz
	@rm -rf ./Tests/build*

.PHONY: install
install:
	make clean
	mkdir build && cd build && cmake ../CMakeLists.txt && make -j8
	cd build/Maze.app/Contents/MacOS/ && ./Maze

.PHONY: test
test:
	cd Tests && rm -rf build*
	cd Tests && mkdir build && cd build && cmake ../CMakeLists.txt && cmake --build . -j8 && ctest

.PHONY: uninstall
uninstall:
	@rm -rf build*
	@rm -rf ./Maze/build*

.PHONY: open
open:
	cd build/Maze.app/Contents/MacOS/ && ./Maze

.PHONY: open_leaks
open_leaks:
	cd build/Maze.app/Contents/MacOS/ && CK_FORK=no leaks --atExit -- ./Maze

.PHONY: dist
dist:
	rm -rf ../Archive_Maze/
	mkdir ../Archive_Maze/
	mkdir ../Archive_Maze/src
	cp build/Maze.app/Contents/MacOS/Maze ../Archive_Maze/src/
	cd .. && tar cvzf Archive_Maze.tgz ./Archive_Maze
	@rm -rf ../Archive_Maze

.PHONY: check
check:
	@find Controlers -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -n --style=Google
	@find Models -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -n --style=Google
	@find Views -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -n --style=Google
	@find Tests -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -n --style=Google

.PHONY: correct
correct:
	@find Controlers -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -i --style=Google
	@find Models -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -i --style=Google
	@find Views -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -i --style=Google
	@find Tests -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -i --style=Google

.PHONY: rebuild
rebuild:
	$(MAKE) clean
	$(MAKE) all

