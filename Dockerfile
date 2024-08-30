# Use the official GCC image
FROM gcc:12

# Install CMake, Ninja, and Git
RUN apt-get update && apt-get install -y \
    cmake \
    ninja-build \
    git \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /parser

# Copy the current directory contents into the container at /parser
COPY . /parser

# Clean up any existing CMake cache or build directories
RUN rm -rf CMakeCache.txt CMakeFiles/

# Run the build process
RUN cmake . -G Ninja
RUN cmake --build .
