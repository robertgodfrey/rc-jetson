#include "crow.h"
#include "hello.h"

int main()
{
    Hello hiThere;
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        auto page = crow::mustache::load_text("index.html");
        return page;
    });

    CROW_ROUTE(app, "/welcome/<string>")([](std::string name) {
        auto page = crow::mustache::load("name.html");
        crow::mustache::context ctx ({{"person", name}});
        return page.render(ctx);
    });

    app.loglevel(crow::LogLevel::Debug);

    hiThere.printHello();

    app.port(18080).multithreaded().run();
}
