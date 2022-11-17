current_dir = $(notdir $(shell pwd))

all: build start

build:
	./bin/build.sh

ci:
	./bin/ci.sh

start:
	./bin/start.sh

.PHONY: all build start ci
