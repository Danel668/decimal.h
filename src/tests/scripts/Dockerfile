FROM quay.io/school21/alpine:3.16

RUN apk --no-cache --upgrade add \
	vim \
    git \
    git-lfs \
    curl \
    jq \
    bash \
    build-base \
    python3 \
    valgrind \
    cppcheck \
    alpine-sdk \
    pcre-dev \
    clang-extra-tools \
	coreutils \
	perl \
	grep

COPY tests/scripts /test

RUN /bin/bash /test/install_checklib.sh

COPY . /project

WORKDIR "/project"

#ENTRYPOINT ["/bin/bash", "/test/start_test.sh"]
