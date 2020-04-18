//
// Created by Restart on 7/15/2018.
//

#pragma once

#include "EncryptMd5.hpp"

#include <string>

namespace LaughCrab
{
    class ResHelper
    {
    public:
        static std::string &&MakeResId(const std::string &path)
        {
            if (ValidPath(path))
            {
                return path + ":" + MD5Digest(path);
            }
            return std::string();
        }

        static std::string &&GetResPath(const std::string &resId)
        {
            auto index = resId.find(':');
            if (index != std::string::npos)
            {
                return resId.substr(0, index);
            }

            return std::string();
        }

        static std::string &&GetResDigest(const std::string &resId)
        {
            auto index = resId.find(':');
            if (index != std::string::npos && index + 1 != std::string::npos)
            {
                return resId.substr(index + 1, index);
            }

            return std::string();
        }

    private:
        static Boolean ValidDigest(const std::string &str)
        {
            return str.size() == 32;
        }

        static Boolean ValidPath(const std::string &str)
        {
            return !str.empty();
        }

        static Boolean IdenticalRes(const std::string &l, const std::string &r)
        {
            return GetResDigest(l) == GetResDigest(r);
        }

    };
}
