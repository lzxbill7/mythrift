TOP := $(CURDIR)
BUILD := $(TOP)/build
MAKE := $(MAKE) -j$(shell grep -c ^processor /proc/cpuinfo)
CMAKE := $(shell which cmake28 > /dev/null 2>&1 && echo cmake28 || echo cmake)
CCMAKE := $(shell which ccmake28 > /dev/null 2>&1 && echo ccmake28 || echo ccmake)

include *.make

all:
	test -d $(BUILD) || (mkdir -p $(BUILD) && cd $(BUILD) && $(CMAKE) -D CMAKE_BUILD_TYPE=RelWithDebInfo $(TOP))
	cd $(BUILD) && $(MAKE)
.PHONY: all


help:
	@echo
	@echo "| Help"
	@echo "+======"
	@echo
	@echo "Available targets:"
	@echo  "    all:                the default"
	@echo  "    debug:              debug build"
	@echo  "    debugc:             debug build with clang"
	@echo  "    release:            release build"
	@echo  "    releasec:           release build with clang"
	@echo  "    relwithdebinfo:     release build with debug info"
	@echo  "    relwithdebinfoc:    release build with debug info and clang"
	@echo  "    minsizerel:         minimum size release build (-Os)"
	@echo  "    minsizerelc:        minimum size release build (-Os) and clang"
	@echo
	@echo  "    test:               run all tests"
	@echo  "    memtest:            run all tests with valgrind"
	@echo  "    doxygen:            run doxygen"
	@echo
	@echo  "    clean:              clean the build tree"
	@echo  "    distclean:          remove all build files"
	@echo
	@echo  "    edit_cache:         edit the ccmake build options"
	@echo
.PHONY: help


prebuild:
	mkdir -p $(BUILD) || true
.PHONY: prebuild


debug: prebuild
	cd $(BUILD) && $(CMAKE) -D CMAKE_BUILD_TYPE=Debug $(TOP) && $(MAKE)
.PHONY: debug


debugc: prebuild
	cd $(BUILD) && CC=clang CXX=clang++ $(CMAKE) -D CMAKE_BUILD_TYPE=Debug $(TOP) && $(MAKE)
.PHONY: debugc


release: prebuild
	cd $(BUILD) && $(CMAKE) -D CMAKE_BUILD_TYPE=Release $(TOP) && $(MAKE)
.PHONY: release


releasec: prebuild
	cd $(BUILD) && CC=clang CXX=clang++ $(CMAKE) -D CMAKE_BUILD_TYPE=Release $(TOP) && $(MAKE)
.PHONY: releasec


relwithdebinfo: prebuild
	cd $(BUILD) && $(CMAKE) -D CMAKE_BUILD_TYPE=RelWithDebInfo $(TOP) && $(MAKE)
.PHONY: relwithdebinfo


relwithdebinfoc: prebuild
	cd $(BUILD) && CC=clang CXX=clang++ $(CMAKE) -D CMAKE_BUILD_TYPE=RelWithDebInfo $(TOP) && $(MAKE)
.PHONY: relwithdebinfoc


minsizerel: prebuild
	cd $(BUILD) && $(CMAKE) -D CMAKE_BUILD_TYPE=MinSizeRel $(TOP) && $(MAKE)
.PHONY: minsizerel


minsizerelc: prebuild
	cd $(BUILD) && CC=clang CXX=clang++ $(CMAKE) -D CMAKE_BUILD_TYPE=MinSizeRel $(TOP) && $(MAKE)
.PHONY: minsizerelc


test:
	(cd $(BUILD) && $(MAKE) test)
.PHONY: test

memtest:
	(cd $(BUILD) && $(MAKE) ExperimentalMemCheck)
.PHONY: memtest


clean:
	-(cd $(BUILD) && $(MAKE) clean)
.PHONY: clean
c: clean


distclean:
	-rm -rf $(BUILD)
.PHONY: distclean
dc: distclean


edit_cache:
	cd $(BUILD) && $(CCMAKE) $(TOP)
.PHONY: edit_cache


.PHONY: serverconf

doxygen:
	doxygen docs/Doxyfile
.PHONY: doxygen
