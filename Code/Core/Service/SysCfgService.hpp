#pragma once

#include "Base.hpp"
#include "Service.hpp"

namespace LaughCrab {
    class SysCfgService : public Service {
    public:
        /// mem pool config
        typedef struct MemPoolConfig {
            static const Integer POOLS_NUM = 18;
            Integer blockBytes[POOLS_NUM];
            Integer blockNum[POOLS_NUM];
        } MemPoolConfig;

        typedef struct MemStackConfig {
            Size bytes;
        } MemStackConfig;

    public:
        explicit SysCfgService(const Char *config);

        ~SysCfgService() override;

        void Start() override;

        void Stop() override;

        void Restart() override;

        Boolean Init() override;

        void Update() override;

        void DeInit() override;


        const Integer GetAlign() const;

        const MemPoolConfig &GetMemPoolConfig() const;

        const MemStackConfig &GetMemStackConfig() const;

    private:
        // mem pool config
        MemPoolConfig m_memPoolConfig;
        // mem stack config
        MemStackConfig m_memStackConfig;

    };

    extern SysCfgService *g_sysCfgService;
}
