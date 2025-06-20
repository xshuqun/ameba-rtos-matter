# Use the latest Ubuntu LTS version for stability
FROM ubuntu:24.04

# Install common dependencies and clean up to reduce image size
RUN set -x \
    && find /etc/apt/ -name '*.list' -exec sed -i 's|http://archive.ubuntu.com/ubuntu|http://mirrors.aliyun.com/ubuntu|g' {} + \
    && find /etc/apt/ -name '*.list' -exec sed -i 's|http://security.ubuntu.com/ubuntu|http://mirrors.aliyun.com/ubuntu|g' {} + \
    && for i in 1 2 3; do apt-get update && break || sleep 5; done \
    && DEBIAN_FRONTEND=noninteractive apt-get install -fy --no-install-recommends \
    git \
    gcc \
    g++ \
    python3-venv \
    python3-dev \
    python3-pip \
    wget \
    bzip2 \
    libgirepository1.0-dev \
    libcairo2-dev \
    libreadline-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Define build arguments for repositories
ARG CHIP_REPO=https://github.com/project-chip/connectedhomeip.git
ARG CHIP_REF=master
ARG AMEBA_DIR=/opt/ameba

# Create the necessary directory, clone the connectedhomeip repo
RUN mkdir -p ${AMEBA_DIR} \
    && cd ${AMEBA_DIR} \
    && git clone --depth 1 --branch ${CHIP_REF} --single-branch ${CHIP_REPO} connectedhomeip \
    && cd connectedhomeip \
    && git submodule update --init --recursive --depth 1

# Set the working directory for the rest of the Dockerfile to work
WORKDIR ${AMEBA_DIR}

# Set default command to bash for interaction
CMD ["/bin/bash"]

