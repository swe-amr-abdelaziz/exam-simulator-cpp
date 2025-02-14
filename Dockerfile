FROM node:16-bullseye-slim

WORKDIR /app

COPY dependencies.txt .

# Install dependencies
RUN \
  apt-get update && \
  xargs apt-get install -y < dependencies.txt

# Set the default C++ compiler
RUN export CXX=/usr/bin/g++-10

CMD ["bash"]
