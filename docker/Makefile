# This is the Makefile inside docker container build environment

.ONESHELL:
.SHELLFLAGS += -e
.SUFFIXES:
SHELL := /bin/bash

# git version
VERSION ?= dev

# release or debug build
BUILD ?= release

override RSYNC := rsync -rlptD
override SOURCE_DIR := /source
override BUILD_DIR := /build

override USER_NAME := $(shell whoami)


.PHONY: all
all: build

.PHONY: build
build: acharn server

.PHONY:
acharn:
	mkdir -p ${BUILD_DIR}/build
	pushd ${BUILD_DIR}/build
	cmake /source
	make
	popd
	rm -rf ${BUILD_DIR}/out
	mkdir -p ${BUILD_DIR}/out
	${RSYNC} ${SOURCE_DIR}/mdl ${BUILD_DIR}/out
	${RSYNC} ${SOURCE_DIR}/tex ${BUILD_DIR}/out
	${RSYNC} ${SOURCE_DIR}/model ${BUILD_DIR}/out
	${RSYNC} ${SOURCE_DIR}/data ${BUILD_DIR}/out
	${RSYNC} ${BUILD_DIR}/build/acharn ${BUILD_DIR}/out



.PHONY:
server:
	mkdir -p ${BUILD_DIR}/server
	pushd ${BUILD_DIR}/server
	cmake /source/serveurfin
	make
	popd
	${RSYNC} ${SOURCE_DIR}/serveurfin/sauvegarde.dadu ${BUILD_DIR}/server/



	

