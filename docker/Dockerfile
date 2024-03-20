FROM debian:bookworm-slim

RUN \
    apt-get update && \
    apt-get install -y \
        automake \
        bc \
        binutils \
        bison \
        build-essential \
        cmake \
        curl \
        ethtool \
        flex \
        g++ \
        g++-multilib \
        gcc \
        gcc-multilib \
        gdisk \
        git \
        libssl-dev \
        libtool \
        m4 \
        make \
        mtools \
        rsync \
        sudo \
        texinfo \
        util-linux \
libirrlicht-dev \
libsndfile1-dev \
libopenal-dev \
libboost-system-dev \
libboost-filesystem-dev \
libboost-thread-dev \
libasio-dev \
strace \
    && \
    rm -rf /var/lib/apt/lists/*

ARG USER_ID
ARG GROUP_ID
ARG USER_NAME

RUN addgroup --gid $GROUP_ID $USER_NAME && \
        adduser --disabled-password --gecos '' --uid $USER_ID --gid $GROUP_ID $USER_NAME && \
        echo "$USER_NAME ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers

