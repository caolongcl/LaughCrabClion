#include "SysCfgService.hpp"

using namespace LaughCrab;

SysCfgService::SysCfgService(const char *config) {
    if (config == nullptr) {
        // parse default config
        Integer bbytes[MemPoolConfig::POOLS_NUM] = {8, 16, 32, 48, 64, 128, 192, 256, 384, 512, 768,
                                                    1024, 8 * 1024, 16 * 1024, 24 * 1024, 32 * 1024, 48 * 1024,
                                                    64 * 1024};
        Integer bnum[MemPoolConfig::POOLS_NUM] = {256, 1024, 256, 256, 1024, 256, 256, 256, 256, 256, 256, 256, 256,
                                                  256, 256, 256, 256, 256};
        for (Integer i = 0; i < MemPoolConfig::POOLS_NUM; ++i) {
            m_memPoolConfig.blockBytes[i] = bbytes[i];
            m_memPoolConfig.blockNum[i] = bnum[i];
        }

        m_memStackConfig.bytes = 1024;
    } else {

    }
}

SysCfgService::~SysCfgService() {

}

void SysCfgService::Start() {

}

void SysCfgService::Stop() {}

void SysCfgService::Restart() {}

Boolean SysCfgService::Init() {
    return true;
}

void SysCfgService::Update() {}

void SysCfgService::DeInit() {}

const Integer SysCfgService::GetAlign() const {
    return LAUGH_CRAB_ALIGN;
}

const SysCfgService::MemPoolConfig &SysCfgService::GetMemPoolConfig() const {
    return m_memPoolConfig;
}

const SysCfgService::MemStackConfig &SysCfgService::GetMemStackConfig() const {
    return m_memStackConfig;
}