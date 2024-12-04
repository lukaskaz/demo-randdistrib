FROM gcc:12.2.0
COPY . /app
RUN mkdir /app/build
WORKDIR /app/build
RUN g++ -std=c++20 -o randgen ../src/main.cpp
CMD ["./randgen"]

