/*
 * robot.cpp - BoringRobot basic class implementation
 *
 * Copyright (C) 2020 Evgeny Sinelnikov <sin@altlinux.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "util.h"
#include "robot.h"

Robot::Robot(): name("UnknownRobot") {};

void Robot::init(const char* robotName) {
  name = robotName;
}

void Robot::status(const char *newStatus) {
  log(name, newStatus);
}

void Robot::poll() {
  status("Poll");
}
