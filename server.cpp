#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <JHPWMPCA9685.h>
#include <unistd.h>

#include "crow.h"
#include "hello.h"

// #define CROW_ENFORCE_WS_SPEC

#define STEERING_CHANNEL 0
#define ESC_CHANNEL 1

#define STEERING_RIGHT 630
#define STEERING_NEUTRAL 490
#define STEERING_LEFT 350

#define THROTTLE_REVERSE 460 
#define THROTTLE_NEUTRAL 490
#define THROTTLE_FORWARD 520


int main()
{
    Hello hiThere;
    crow::SimpleApp app;

    PCA9685 *pca9685 = new PCA9685();
    int err = pca9685->openPCA9685();
    
    if (err < 0){
        printf("Error: %d", pca9685->error);
	exit(1);
    }

    printf("PCA9685 Device Address: 0x%02X\n",pca9685->kI2CAddress);
    pca9685->setAllPWM(0,0);
    pca9685->reset();
    pca9685->setPWMFrequency(75);

    CROW_ROUTE(app, "/")([](){
        auto page = crow::mustache::load_text("index.html");
        return page;
    });

    CROW_WEBSOCKET_ROUTE(app, "/ws")
        .onopen([&](crow::websocket::connection& conn){
            std::cout << "Connected!" << std::endl;
        })
        .onclose([&](crow::websocket::connection& conn, const std::string& reason){
            std::cout << "Disconnected :(" << std::endl;
	    pca9685->setAllPWM(0,0);
            pca9685->reset();
            pca9685->closePCA9685();
        })
        .onmessage([&](crow::websocket::connection& /*conn*/, const std::string& data, bool is_binary){
                if (data.substr(2, 7) == "control") {
                    // data is motor control for RC car
                    int command = std::stoi(data.substr(12, 2));
                    std::string status = "";
                    if (command >= 8) {
                        status.append("MOVING FORWARD");
			pca9685->setPWM(ESC_CHANNEL, 0, THROTTLE_FORWARD);
                        if (command == 10){
                            // left
                            status.append(" LEFT");
			    pca9685->setPWM(STEERING_CHANNEL, 0, STEERING_LEFT);
                        } else if (command == 9) {
                            // right
                            status.append(" RIGHT");
			    pca9685->setPWM(STEERING_CHANNEL, 0, STEERING_RIGHT);
                        } else {
                            // just go forward
			    pca9685->setPWM(STEERING_CHANNEL, 0, STEERING_NEUTRAL);
                        }
                    } else if (command >= 4) {
                       // backward
                        status.append("MOVING BACKWARD");
			pca9685->setPWM(ESC_CHANNEL, 0, THROTTLE_REVERSE);
                        if (command == 6) {
                            // left
                            status.append(" LEFT");
			    pca9685->setPWM(STEERING_CHANNEL, 0, STEERING_LEFT);
                        } else if (command == 5) {
                            // right
                            status.append(" RIGHT");
			    pca9685->setPWM(STEERING_CHANNEL, 0, STEERING_RIGHT);
                        } else {
                            // just reverse
			    pca9685->setPWM(STEERING_CHANNEL, 0, STEERING_NEUTRAL);
                        }
                    } else if (command == 2) {
                        // left
                        status.append("TURNING LEFT");
			pca9685->setPWM(ESC_CHANNEL, 0, THROTTLE_NEUTRAL);
			pca9685->setPWM(STEERING_CHANNEL, 0, STEERING_LEFT);
                    } else if (command == 1) {
                        // right
                        status.append("TURNING RIGHT");
			pca9685->setPWM(ESC_CHANNEL, 0, THROTTLE_NEUTRAL);
			pca9685->setPWM(STEERING_CHANNEL, 0, STEERING_RIGHT);
                    } else {
                        status.append("STOPPING");
			pca9685->setPWM(ESC_CHANNEL, 0, THROTTLE_NEUTRAL);
			pca9685->setPWM(STEERING_CHANNEL, 0, STEERING_NEUTRAL);
                    }
                    std::cout << status << std::endl;
                } else {
                    pca9685->setPWM(ESC_CHANNEL, 0, THROTTLE_NEUTRAL);
                    std::cout << data << std::endl;
                }
            });

    app.loglevel(crow::LogLevel::Debug);

    hiThere.printHello();

    app.port(18080).multithreaded().run();
}
