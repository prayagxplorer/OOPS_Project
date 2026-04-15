# We use an official Ubuntu image as a parent image
FROM ubuntu:22.04

# Set non-interactive mode for apt-get to avoid timezone prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install g++ and make
RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    make \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

# Make sure we clean out any cached object files from the local machine 
# and build a fresh inventory_system binary for Linux
RUN make clean && make

# Make port 8080 available to the world outside this container
EXPOSE 8080

# Run the executable
CMD ["./inventory_system"]
