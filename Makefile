# Makefile for BoringRobot
#
# Copyright (C) 2020 Evgeny Sinelnikov <sin@altlinux.org>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

ARDUINO := $(shell command -v arduino 2>/dev/null)
ARDUINO_BUILDER := $(shell command -v arduino-builder 2>/dev/null)
PICOCOM := $(shell command -v picocom 2>/dev/null)

ifndef ARDUINO
    $(warning "arduino is not available.")
endif

ifndef ARDUINO_BUILDER
    $(warning "arduino-builder is not available.")
endif

ifndef PICOCOM
    $(warning "picocom is not available.")
endif

ARDUINO_PATH := $(ARDUINO)
ifneq ($(OS),Windows_NT)
    ARDUINO_PATH := $(shell readlink -f $(ARDUINO))
endif
ARDUINO_DIR := $(abspath $(dir $(ARDUINO_PATH)))
ARDUINO_HARDWARE_DIR := $(ARDUINO_DIR)/hardware
ARDUINO_TOOLS_DIR := $(ARDUINO_DIR)/hardware/tools
LIBRARIES_DIR := $(CURDIR)/libraries
BUILD_DIR := $(CURDIR)/build

TOPDIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
SKETCH_FILE ?= sketch.cpp
SKETCH := $(abspath $(SKETCH_FILE))
#BOARD ?= arduino:avr:mega:cpu=atmega2560
BOARD ?= arduino:avr:uno
PORT ?= /dev/ttyACM0

PROJECT_FILE := BoringRobot.ino

LIBRARIES = IoAbstraction TaskManagerIO
ifeq ($(filter install_libraries,$(MAKECMDGOALS)),install_libraries)
    SKETCH_PATH := $(shell $(ARDUINO) --get-pref sketchbook.path 2>/dev/null)
endif

.PHONY: all upload verify monitor compile install_libraries

all: verify; @:

install_libraries:
	@mkdir -p "$(SKETCH_PATH)/libraries"
	@for l in $(LIBRARIES); do \
		test -L "$(SKETCH_PATH)/libraries/$$l" && \
			rm -f "$(SKETCH_PATH)/libraries/$$l"; \
		test -d "$(SKETCH_PATH)/libraries/$$l" || \
			ln -s "$(LIBRARIES_DIR)/$$l" "$(SKETCH_PATH)/libraries/"; \
	done

compile: $(PROJECT_FILE)
	@rm -rf "$(BUILD_DIR)"
	@mkdir -p "$(BUILD_DIR)"
	$(ARDUINO_BUILDER) -hardware "$(ARDUINO_HARDWARE_DIR)" -tools "$(ARDUINO_TOOLS_DIR)" -tools "$(ARDUINO_DIR)/tools-builder/" -libraries "$(LIBRARIES_DIR)" -build-path "$(BUILD_DIR)" -fqbn "$(BOARD)" -verbose $<

verify:
	arduino --pref sketchbook.path=$(CURDIR) --verify --board "$(BOARD)" "$(SKETCH)"

upload:
	arduino --pref sketchbook.path=$(CURDIR) --upload --port "$(PORT)" --board "$(BOARD)" "$(SKETCH)"

monitor:
	picocom -b 115200 "$(PORT)"
