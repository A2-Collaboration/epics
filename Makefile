SUBDIRS = base modules extensions

DEBIAN_LIKE := $(shell command -v apt-get 2> /dev/null)
FEDORA_LIKE := $(shell command -v yum 2> /dev/null)
ARCH_LIKE := $(shell command -v pacman 2> /dev/null)

ifndef_any_of = $(filter undefined,$(foreach v,$(1),$(origin $(v))))
ifdef_any_of = $(filter-out undefined,$(foreach v,$(1),$(origin $(v))))

ifdef DEBIAN_LIKE
	MSG = "=== Installing Dependencies (Debian-like system) ==="
	PACKAGEMANAGER = sudo apt-get install
	DEPS = libreadline-dev re2c libpcre3-dev build-essential
endif
ifdef FEDORA_LIKE
	MSG = "=== Installing Dependencies (Fedora-like system) ==="
	PACKAGEMANAGER = sudo yum install
	DEPS = readline-devel re2c pcre-devel
endif
ifdef ARCH_LIKE
	MSG = "=== Installing Dependencies (Arch-like system) ==="
	PACKAGEMANAGER = sudo pacman -S
	DEPS = readline re2c pcre
endif
ifeq ($(call ifdef_any_of, ARCH_LIKE FEDORA_LIKE DEBIAN_LIKE),)
	MSG = "System not covered, installing dependencies failed"
endif


.PHONY: deps all $(SUBDIRS) clean

all: deps $(SUBDIRS)

$(SUBDIRS): deps
	@echo ""
	@echo ""
	@echo "===== Building $@ ====="
	$(MAKE) -C $@

modules: base

extensions: base modules

deps:
	@echo ""
	@echo ""
ifeq ($(call ifdef_any_of, ARCH_LIKE FEDORA_LIKE DEBIAN_LIKE),)
	$(error $(MSG))
endif
	@echo $(MSG)
	$(PACKAGEMANAGER) $(DEPS)

clean:
	for dir in $(SUBDIRS); do $(MAKE) -C $$dir clean; done
