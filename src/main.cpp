#include "app.h"

int main(int argc, char** argv) {
    App::GetInstance().Init(argc, argv);
    App::GetInstance().Run();
    return 0;
}