#!/bin/bash
docker run --rm --mount source=$(pwd),destination=/m68k,readonly -t registry.gitlab.com/doragasu/docker-sgdk:v1.70 clean release
