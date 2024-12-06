FROM gcc:latest
COPY . /app
RUN mkdir /app/build
WORKDIR /app/build
RUN apt-get update && \
	apt-get -y install cmake
RUN cmake -DCMAKE_BUILD_TYPE=Release .. && \
	cmake --build . --parallel $(nproc)
CMD ["./randomsim"]

