server: hello.o server.o
	g++ -o application server.o hello.o -lpthread

server.o: server.cpp hello.h
	g++ -ansi -pedantic-errors -Wall -c -I ../Crow/include -std=c++11 server.cpp 

hello.o: hello.cpp hello.h
	g++ -ansi -pedantic-errors -Wall -c hello.cpp

clean:
	rm *.o

cam: 
	g++ -std=c++11 camera.cpp -I/usr/include/opencv4 -lopencv_gapi -lopencv_highgui -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_video -lopencv_calib3d -lopencv_features2d -lopencv_dnn -lopencv_flann -lopencv_videoio -lopencv_imgcodecs -lopencv_imgproc -lopencv_core 
