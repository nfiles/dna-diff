SRC = src
ALL = build release clean rebuild
ifeq ($(OS),Windows_NT)
	MAKE = mingw32-make
else
	MAKE = make
endif

$(ALL) :
	$(MAKE) -C $(SRC) $@
