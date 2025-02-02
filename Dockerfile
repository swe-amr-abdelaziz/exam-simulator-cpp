FROM node:16-buster-slim

WORKDIR /app

COPY dependencies.txt .

# Install dependencies
RUN \
  apt-get update && \
  xargs apt-get install -y < dependencies.txt

CMD ["bash"]
