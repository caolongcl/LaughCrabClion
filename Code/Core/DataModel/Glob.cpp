//
// Created by Restart on 7/16/2018.
//

#include "Glob.hpp"
#include "MemoryService.hpp"

using namespace LaughCrab;

Glob::Glob(GlobType type, Integer size)
        : m_type(type),
          m_size(size)
{
    m_data = MemHelper::Allocate(size);
}

Glob::~Glob()
{
    MemHelper::Deallocate(m_data);
}