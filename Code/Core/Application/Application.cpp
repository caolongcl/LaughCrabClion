#include "Application.hpp"
#include "MemoryService.hpp"

using namespace LaughCrab;

Application::Application() {

}

Application::Application(void *) {

}

Application::~Application() {

}

Integer Application::Run(Char **cmd) {
    m_life.Go();
    return 0;
}