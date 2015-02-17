SRC = src
ALL = build release clean rebuild
MAKE = mingw32-make

$(ALL) :
	$(MAKE) -C $(SRC) $@
