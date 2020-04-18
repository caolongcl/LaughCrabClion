//
// Created by Restart on 7/13/2018.
//

#include "Service.hpp"
#include "Ref.hpp"
#include "DataModel/Glob.hpp"

#include <string>
#include <unordered_map>

namespace LaughCrab
{
    class ResourceService : public Service
    {
    public:
        ResourceService();

        ~ResourceService() override;

        void Start() override;

        void Stop() override;

        void Restart() override;

        Boolean Init() override;

        void Update() override;

        void DeInit() override;

    private:
        std::unordered_map<std::string, std::string> m_resPaths;
        std::unordered_map<std::string, Ref<Glob>> m_resGlobs;
    };

    extern ResourceService *g_resourceService;
}
