# PARAMTERS

# release or debug build
BUILD ?= release

# build dir
BUILD_DIR ?= $(shell pwd)/build

override VERSION := $(shell git rev-parse --short HEAD)
override TAG := github.com/robien/acharn.git

override DOCKER_ARGS := --tty --privileged --hostname $(shell hostname --short)
override DOCKER_ARGS := ${DOCKER_ARGS} --volume $(shell pwd):/source:ro
override DOCKER_ARGS := ${DOCKER_ARGS} --volume ${BUILD_DIR}:/build:rw
override DOCKER_ARGS := ${DOCKER_ARGS} --env BUILD="${BUILD}"
override DOCKER_ARGS := ${DOCKER_ARGS} --env VERSION="${VERSION}"
override DOCKER_ARGS := ${DOCKER_ARGS} --network host
override DOCKER_ARGS := ${DOCKER_ARGS} --user $(shell id -u):$(shell id -g) 

override DOCKER_BUILD_ARGS := --build-arg USER_ID=$(shell id -u) --build-arg USER_NAME=$(shell whoami) --build-arg GROUP_ID=$(shell id -g)

.PHONY: all
all: build

.PHONY: prepare
prepare: docker
	@git submodule update --recursive --init; \
	mkdir -p ${BUILD_DIR}; \
	chown $(shell whoami) ${BUILD_DIR}

.PHONY: build
build: prepare
	@docker run ${DOCKER_ARGS} --entrypoint=make ${TAG} -C /source/docker

.PHONY: shell
shell: prepare
	@docker run ${DOCKER_ARGS} --interactive --entrypoint=bash ${TAG}

.PHONY: docker
docker:
	@docker build ${DOCKER_BUILD_ARGS} -t ${TAG} docker

.PHONY: run
run: prepare
	@docker run ${DOCKER_ARGS} --interactive --entrypoint=/build/out/acharn ${TAG} 

.PHONY: listen
listen: prepare
	@docker run ${DOCKER_ARGS} --interactive -t --entrypoint=/build/server/serveur ${TAG} 10000
