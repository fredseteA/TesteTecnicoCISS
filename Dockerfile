FROM gcc:13

WORKDIR /app

COPY libs/ ./libs/
COPY src/api.cpp ./src/
COPY src/simian.cpp ./src/
COPY src/simian.h ./src/

RUN g++ src/api.cpp src/simian.cpp -o api -I libs -lpthread

EXPOSE 8080

CMD ["./api"]