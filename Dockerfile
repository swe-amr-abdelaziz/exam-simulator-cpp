FROM node:16-buster-slim

WORKDIR /app

COPY dependencies.txt .

# Install dependencies
RUN \
  apt-get update && \
  xargs apt-get install -y < dependencies.txt

# Compile googletest
RUN \
  cd /usr/src/googletest/googletest && \
  mkdir build && \
  cd build && \
  cmake .. && \
  make && \
  cp libgtest* /usr/lib/ && \
  cd .. && \
  rm -rf build && \
  mkdir /usr/local/lib/googletest && \
  ln -s /usr/lib/libgtest.a /usr/local/lib/googletest/libgtest.a && \
  ln -s /usr/lib/libgtest_main.a /usr/local/lib/googletest/libgtest_main.a

CMD ["bash"]
