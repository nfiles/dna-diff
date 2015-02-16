SRC = src
ALL = build release clean rebuild

$(ALL) :
	make -C $(SRC) $@
