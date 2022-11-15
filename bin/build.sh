#!/bin/bash
docker run --rm -v $(pwd):/m68k -t registry.gitlab.com/doragasu/docker-sgdk:v1.70 clean release
