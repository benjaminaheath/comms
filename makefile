# Project Makefile

bin/main.exe:
	@$(MAKE) -C $(SRC_DIR)

.PHONY: clean
clean:
	@$(MAKE) -C src clean