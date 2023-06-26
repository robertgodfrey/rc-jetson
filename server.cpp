#include <iostream>
#include <string.h>
#include "crow.h"
#include "hello.h"

// #define CROW_ENFORCE_WS_SPEC

int main()
{
    Hello hiThere;
    crow::SimpleApp app;

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
        })
        .onmessage([&](crow::websocket::connection& /*conn*/, const std::string& data, bool is_binary){
                if (data.substr(2, 7) == "control") {
                    // data is motor control for RC car
                    int command = std::stoi(data.substr(12, 2));
                    std::string status = "";
                    if (command >= 8) {
                        status.append("MOVING FORWARD");
                        if (command == 10){
                            // left
                            status.append(" LEFT");
                        } else if (command == 9) {
                            // right
                            status.append(" RIGHT");
                        } else {
                            // just go forward
                        }
                    } else if (command >= 4) {
                       // backward
                        status.append("MOVING BACKWARD");
                        if (command == 6) {
                            // left
                            status.append(" LEFT");
                        } else if (command == 5) {
                            // right
                            status.append(" RIGHT");
                        } else {
                            // just reverse
                        }
                    } else if (command == 2) {
                        // left
                        status.append("TURNING LEFT");
                    } else if (command == 1) {
                        // right
                        status.append("TURNING RIGHT");
                    } else {
                        status.append("STOPPING");
                    }
                    std::cout << status << std::endl;
                } else {
                    std::cout << data << std::endl;
                }
            });

    app.loglevel(crow::LogLevel::Debug);

    hiThere.printHello();

    app.port(18080).multithreaded().run();
}
