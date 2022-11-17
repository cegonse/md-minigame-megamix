#!/bin/bash
docker image rm sgdk-build
docker build . -t sgdk-build
docker run --rm -t sgdk-build clean release
