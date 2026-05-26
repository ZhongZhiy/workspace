tar := $(MAKEFILE_LIST)

all:
	$(MAKE) -C $(abspath $(tar))
	git add . && git commit -m "auto sync" && git push
