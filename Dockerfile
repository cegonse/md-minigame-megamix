FROM registry.gitlab.com/doragasu/docker-sgdk:v1.70

COPY --chown=m68k:m68k . /m68k
RUN ls -la
