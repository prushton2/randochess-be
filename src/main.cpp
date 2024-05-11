#include <iostream>
#include "httplib.h"

using namespace httplib;

int main(void)
{



        Server svr;

        svr.Get(R"(/numbers/(\d+))", [&](const Request &req, Response &res)
                {
                auto numbers = req.matches[1];
                res.set_content(numbers, "text/plain");
            });

        svr.Get("/stop", [&](const Request &req, Response &res)
                { svr.stop(); });

        svr.listen("localhost", 6000);
}
