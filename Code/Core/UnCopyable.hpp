#pragma once

namespace LaughCrab {
    class UnCopyable {
    protected:
        UnCopyable() = default;

        virtual ~UnCopyable() = default;

    public:
        UnCopyable(const UnCopyable &) = delete;

        UnCopyable &operator=(const UnCopyable &)= delete;
    };

    class UnMovable {
    protected:
        UnMovable() = default;

        virtual ~UnMovable() = default;

    public:
        UnMovable(UnMovable &&) = delete;

        UnMovable &operator=(UnMovable &&) = delete;
    };
}