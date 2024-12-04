FROM gcc:12.2.0
COPY . /app
RUN mkdir /app/build
WORKDIR /app/build
RUN apt-get update && apt-get -y install cmake
RUN cmake -DCMAKE_BUILD_TYPE=Release .. && \
	cmake --build . --parallel $(nproc)
CMD ["./randgen"]

