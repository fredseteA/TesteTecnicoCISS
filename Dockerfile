FROM gcc:13 AS builder

WORKDIR /app

RUN apt-get update && apt-get install -y libsqlite3-dev

COPY libs/ ./libs/
COPY src/api.cpp ./src/
COPY src/simian.cpp ./src/
COPY src/simian.h ./src/
COPY src/database.cpp ./src/
COPY src/database.h ./src/

RUN g++ src/api.cpp src/simian.cpp src/database.cpp -o api -I libs -std=c++17 -O2 -lsqlite3 -static-libstdc++ -static-libgcc

FROM debian:bookworm-slim

WORKDIR /app

RUN apt-get update && apt-get install -y libsqlite3-0 && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /data

COPY --from=builder /app/api .

EXPOSE 8080

CMD ["./api"]