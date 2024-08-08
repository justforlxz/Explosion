//
// Created by johnk on 2023/12/4.
//

#pragma once

#include <vector>
#include <unordered_set>
#include <algorithm>
#include <array>

#include <Common/Debug.h>

namespace Common {
    class VectorUtils {
    public:
        template <typename T>
        static typename std::vector<T>::iterator SwapWithLastAndDelete(std::vector<T>& vector, const typename std::vector<T>::iterator& iterator);

        template <typename T>
        static size_t SwapWithLastAndDelete(std::vector<T>& vector, size_t index);

        template <typename T>
        static std::vector<T> GetIntersection(const std::vector<T>& lhs, const std::vector<T>& rhs);
    };

    class SetUtils {
    public:
        template <typename T>
        static std::unordered_set<T> GetIntersection(const std::unordered_set<T>& lhs, const std::unordered_set<T>& rhs);

        template <typename T>
        static std::unordered_set<T> GetUnion(const std::unordered_set<T>& lhs, const std::unordered_set<T>& rhs);

        template <typename T>
        static void GetUnionInline(std::unordered_set<T>& lhs, const std::unordered_set<T>& rhs);
    };

    template <typename T>
    class InplaceVectorIter;

    template <typename I, typename T>
    concept ValidInplaceVectorIter = std::is_same_v<I, InplaceVectorIter<T>> || std::is_same_v<I, InplaceVectorIter<const T>>;

    template <typename T>
    class InplaceVectorIter {
    public:
        using Offset = int64_t;

        template <ValidInplaceVectorIter<T> T2>
        Offset operator-(const T2& inOther) const;

        template <ValidInplaceVectorIter<T> T2>
        bool operator==(const T2& inOther) const;

        template <ValidInplaceVectorIter<T> T2>
        bool operator!=(const T2& inOther) const;

        template <ValidInplaceVectorIter<T> T2>
        bool operator>(const T2& inOther) const;

        template <ValidInplaceVectorIter<T> T2>
        bool operator>=(const T2& inOther) const;

        template <ValidInplaceVectorIter<T> T2>
        bool operator<(const T2& inOther) const;

        template <ValidInplaceVectorIter<T> T2>
        bool operator<=(const T2& inOther) const;

        explicit InplaceVectorIter(T* inPtr);
        T& operator*() const;
        T* operator->() const;
        InplaceVectorIter operator+(Offset inOffset) const;
        InplaceVectorIter operator-(Offset inOffset) const;
        InplaceVectorIter& operator+=(Offset inOffset);
        InplaceVectorIter& operator-=(Offset inOffset);
        InplaceVectorIter& operator++();
        InplaceVectorIter& operator--();
        InplaceVectorIter operator++(int);
        InplaceVectorIter operator--(int);
        T* Ptr() const;

    private:
        T* ptr;
    };

    // vector with fixed capacity, this container allocate the stack memory internal, so memory access is efficient
    template <typename T, size_t N>
    class InplaceVector {
    public:
        using Iter = InplaceVectorIter<T>;
        using ConstIter = InplaceVectorIter<const T>;

        static constexpr size_t Capacity();

        InplaceVector();
        explicit InplaceVector(size_t inSize, T inDefault = {});
        ~InplaceVector();

        InplaceVector(const InplaceVector& inOther);
        InplaceVector(InplaceVector&& inOther) noexcept;
        InplaceVector& operator=(const InplaceVector& inOther);
        InplaceVector& operator=(InplaceVector&& inOther) noexcept;

        template <typename... Args>
        T& EmplaceBack(Args&&... inArgs);

        T& PushBack(T&& inElement);
        T& PushBack(const T& inElement);
        T& Insert(size_t inIndex, const T& inElement);
        T& Insert(size_t inIndex, T&& inElement);
        T& Insert(const InplaceVectorIter<T>& inIter, const T& inElement);
        T& Insert(const InplaceVectorIter<T>& inIter, T&& inElement);
        T& Insert(const InplaceVectorIter<const T>& inIter, const T& inElement);
        T& Insert(const InplaceVectorIter<const T>& inIter, T&& inElement);
        void PopBack();
        void Erase(size_t inIndex);
        void Erase(const InplaceVectorIter<T>& inIter);
        void Erase(const InplaceVectorIter<const T>& inIter);
        void EraseSwapLast(size_t inIndex);
        void EraseSwapLast(const InplaceVectorIter<T>& inIter);
        void EraseSwapLast(const InplaceVectorIter<const T>& inIter);
        T& At(size_t inIndex);
        const T& At(size_t inIndex) const;
        T& Back();
        const T& Back() const;
        bool Empty() const;
        void Resize(size_t inSize, T inDefault = {});
        size_t Size() const;
        size_t MemorySize() const;
        T* Data();
        const T* Data() const;
        T& operator[](size_t inIndex);
        const T& operator[](size_t inIndex) const;
        explicit operator bool() const;
        Iter Begin();
        ConstIter Begin() const;
        Iter End();
        ConstIter End() const;
        Iter begin();
        ConstIter begin() const;
        Iter end();
        ConstIter end() const;

    private:
        static constexpr size_t elementSize = sizeof(T);
        static constexpr size_t memorySize = elementSize * N;

        template <ValidInplaceVectorIter<T> I>
        void CheckIterValid(const I& inIter) const;

        template <typename... Args>
        void EmplaceConstruct(size_t inIndex, Args&&... inArgs);

        template <ValidInplaceVectorIter<T> I, typename... Args>
        void EmplaceConstruct(const I& inIter, Args&&... inArgs);

        template <ValidInplaceVectorIter<T> I>
        void EmplaceDestruct(const I& inIter);

        template <typename T2>
        T& InsertInternal(size_t inIndex, T2&& inElement);

        template <ValidInplaceVectorIter<T> I, typename T2>
        T& InsertInternal(const I& inIter, T2&& inElement);

        template <ValidInplaceVectorIter<T> I>
        void EraseInternal(const I& inIter);

        template <ValidInplaceVectorIter<T> I>
        void EraseSwapLastInternal(const I& inIter);

        void EmplaceDestruct(size_t inIndex);
        T& TypedMemory(size_t inIndex);
        const T& TypedMemory(size_t inIndex) const;
        void CheckIndexValid(size_t inIndex) const;
        void CheckInsertible(size_t inNum = 1) const;

        size_t size;
        std::array<uint8_t, memorySize> memory;
    };
}

namespace Common {
    template <typename T>
    typename std::vector<T>::iterator VectorUtils::SwapWithLastAndDelete(std::vector<T>& vector, const typename std::vector<T>::iterator& iterator)
    {
        std::iter_swap(iterator, vector.end() - 1);
        vector.pop_back();
        return iterator;
    }

    template <typename T>
    size_t VectorUtils::SwapWithLastAndDelete(std::vector<T>& vector, size_t index)
    {
        std::swap(vector[index], vector[vector.size() - 1]);
        vector.pop_back();
        return index;
    }

    template <typename T>
    std::vector<T> VectorUtils::GetIntersection(const std::vector<T>& lhs, const std::vector<T>& rhs)
    {
        std::vector<T> result;
        std::set_intersection(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::back_inserter(result));
        return result;
    }

    template <typename T>
    std::unordered_set<T> SetUtils::GetIntersection(const std::unordered_set<T>& lhs, const std::unordered_set<T>& rhs)
    {
        std::unordered_set<T> result;
        result.reserve(lhs.size());
        for (const auto& elementLhs : lhs) {
            for (const auto& elementRhs : rhs) {
                if (elementLhs == elementRhs) {
                    result.emplace(elementLhs);
                }
            }
        }
        return result;
    }

    template <typename T>
    std::unordered_set<T> SetUtils::GetUnion(const std::unordered_set<T>& lhs, const std::unordered_set<T>& rhs)
    {
        std::unordered_set<T> result;
        result.reserve(lhs.size() + rhs.size());
        for (const auto& element : lhs) {
            result.emplace(element);
        }
        for (const auto& element : rhs) {
            result.emplace(element);
        }
        return result;
    }

    template <typename T>
    void SetUtils::GetUnionInline(std::unordered_set<T>& lhs, const std::unordered_set<T>& rhs)
    {
        lhs.reserve(lhs.size() + rhs.size());
        for (const auto& element : rhs) {
            lhs.emplace(element);
        }
    }

    template <typename T>
    template <ValidInplaceVectorIter<T> T2>
    typename InplaceVectorIter<T>::Offset InplaceVectorIter<T>::operator-(const T2& inOther) const
    {
        return ptr - inOther.Ptr();
    }

    template <typename T>
    template <ValidInplaceVectorIter<T> T2>
    bool InplaceVectorIter<T>::operator==(const T2& inOther) const
    {
        return ptr == inOther.Ptr();
    }

    template <typename T>
    template <ValidInplaceVectorIter<T> T2>
    bool InplaceVectorIter<T>::operator!=(const T2& inOther) const
    {
        return !this->operator==(inOther);
    }

    template <typename T>
    template <ValidInplaceVectorIter<T> T2>
    bool InplaceVectorIter<T>::operator>(const T2& inOther) const
    {
        return ptr > inOther.Ptr();
    }

    template <typename T>
    template <ValidInplaceVectorIter<T> T2>
    bool InplaceVectorIter<T>::operator>=(const T2& inOther) const
    {
        return ptr >= inOther.Ptr();
    }

    template <typename T>
    template <ValidInplaceVectorIter<T> T2>
    bool InplaceVectorIter<T>::operator<(const T2& inOther) const
    {
        return ptr < inOther.Ptr();
    }

    template <typename T>
    template <ValidInplaceVectorIter<T> T2>
    bool InplaceVectorIter<T>::operator<=(const T2& inOther) const
    {
        return ptr <= inOther.Ptr();
    }

    template <typename T>
    InplaceVectorIter<T>::InplaceVectorIter(T* inPtr)
        : ptr(inPtr)
    {
    }

    template <typename T>
    T& InplaceVectorIter<T>::operator*() const
    {
        return *ptr;
    }

    template <typename T>
    T* InplaceVectorIter<T>::operator->() const
    {
        return ptr;
    }

    template <typename T>
    InplaceVectorIter<T> InplaceVectorIter<T>::operator+(Offset inOffset) const
    {
        return InplaceVectorIter(ptr + inOffset);
    }

    template <typename T>
    InplaceVectorIter<T> InplaceVectorIter<T>::operator-(Offset inOffset) const
    {
        return InplaceVectorIter(ptr - inOffset);
    }

    template <typename T>
    InplaceVectorIter<T>& InplaceVectorIter<T>::operator+=(Offset inOffset)
    {
        ptr += inOffset;
        return *this;
    }

    template <typename T>
    InplaceVectorIter<T>& InplaceVectorIter<T>::operator-=(Offset inOffset)
    {
        ptr -= inOffset;
        return *this;
    }

    template <typename T>
    InplaceVectorIter<T>& InplaceVectorIter<T>::operator++()
    {
        ptr += 1;
        return *this;
    }

    template <typename T>
    InplaceVectorIter<T>& InplaceVectorIter<T>::operator--()
    {
        ptr -= 1;
        return *this;
    }

    template <typename T>
    InplaceVectorIter<T> InplaceVectorIter<T>::operator++(int)
    {
        InplaceVectorIter result = *this;
        ptr += 1;
        return result;
    }

    template <typename T>
    InplaceVectorIter<T> InplaceVectorIter<T>::operator--(int)
    {
        InplaceVectorIter result = *this;
        ptr -= 1;
        return result;
    }

    template <typename T>
    T* InplaceVectorIter<T>::Ptr() const
    {
        return ptr;
    }

    template <typename T, size_t N>
    constexpr size_t InplaceVector<T, N>::Capacity()
    {
        return N;
    }

    template <typename T, size_t N>
    InplaceVector<T, N>::InplaceVector()
        : size(0)
        , memory()
    {
    }

    template <typename T, size_t N>
    InplaceVector<T, N>::InplaceVector(size_t inSize, T inDefault)
        : size(inSize)
    {
        for (auto i = 0; i < size; i++) {
            EmplaceConstruct(i, inDefault);
        }
    }

    template <typename T, size_t N>
    InplaceVector<T, N>::~InplaceVector()
    {
        for (auto i = 0; i < size; i++) {
            EmplaceDestruct(i);
        }
    }

    template <typename T, size_t N>
    InplaceVector<T, N>::InplaceVector(const InplaceVector& inOther)
        : size(inOther.size)
    {
        static_assert(std::is_copy_constructible_v<T>);
        for (auto i = 0; i < size; i++) {
            EmplaceConstruct(i, inOther.TypedMemory(i));
        }
    }

    template <typename T, size_t N>
    InplaceVector<T, N>::InplaceVector(InplaceVector&& inOther) noexcept
        : size(inOther.size)
    {
        static_assert(std::is_move_constructible_v<T>);
        for (auto i = 0; i < size; i++) {
            EmplaceConstruct(i, std::move(inOther.TypedMemory(i)));
        }
    }

    template <typename T, size_t N>
    InplaceVector<T, N>& InplaceVector<T, N>::operator=(const InplaceVector& inOther)
    {
        static_assert(std::is_copy_constructible_v<T> && std::is_copy_assignable_v<T>);
        const auto oldSize = size;
        size = inOther.size;
        for (auto i = size; i < oldSize; i++) {
            EmplaceDestruct(i);
        }

        for (auto i = 0; i < size; i++) {
            if (i < oldSize) {
                TypedMemory(i) = inOther.TypedMemory(i);
            } else {
                EmplaceConstruct(i, inOther.TypedMemory(i));
            }
        }
        return *this;
    }

    template <typename T, size_t N>
    InplaceVector<T, N>& InplaceVector<T, N>::operator=(InplaceVector&& inOther) noexcept
    {
        static_assert(std::is_move_constructible_v<T> && std::is_move_assignable_v<T>);
        const auto oldSize = size;
        size = inOther.size;
        for (auto i = size; i < oldSize; i++) {
            EmplaceDestruct(i);
        }

        for (auto i = 0; i < size; i++) {
            if (i < oldSize) {
                TypedMemory(i) = std::move(inOther.TypedMemory(i));
            } else {
                EmplaceConstruct(i, std::move(inOther.TypedMemory(i)));
            }
        }
        return *this;
    }

    template <typename T, size_t N>
    template <typename ... Args>
    T& InplaceVector<T, N>::EmplaceBack(Args&&... inArgs)
    {
        CheckInsertible();
        auto lastIndex = size++;
        EmplaceConstruct(lastIndex, std::forward<Args>(inArgs)...);
        return TypedMemory(lastIndex);
    }

    template <typename T, size_t N>
    T& InplaceVector<T, N>::PushBack(T&& inElement)
    {
        return EmplaceBack(std::move(inElement));
    }

    template <typename T, size_t N>
    T& InplaceVector<T, N>::PushBack(const T& inElement)
    {
        return EmplaceBack(inElement);
    }

    template <typename T, size_t N>
    T& InplaceVector<T, N>::Insert(size_t inIndex, const T& inElement)
    {
        return InsertInternal(inIndex, inElement);
    }

    template <typename T, size_t N>
    T& InplaceVector<T, N>::Insert(size_t inIndex, T&& inElement)
    {
        return InsertInternal(inIndex, std::move(inElement));
    }

    template <typename T, size_t N>
    T& InplaceVector<T, N>::Insert(const InplaceVectorIter<T>& inIter, const T& inElement)
    {
        return InsertInternal(inIter, inElement);
    }

    template <typename T, size_t N>
    T& InplaceVector<T, N>::Insert(const InplaceVectorIter<T>& inIter, T&& inElement)
    {
        return InsertInternal(inIter, std::move(inElement));
    }

    template <typename T, size_t N>
    T& InplaceVector<T, N>::Insert(const InplaceVectorIter<const T>& inIter, const T& inElement)
    {
        return InsertInternal(inIter, inElement);
    }

    template <typename T, size_t N>
    T& InplaceVector<T, N>::Insert(const InplaceVectorIter<const T>& inIter, T&& inElement)
    {
        return InsertInternal(inIter, std::move(inElement));
    }

    template <typename T, size_t N>
    void InplaceVector<T, N>::PopBack()
    {
        EmplaceDestruct(size - 1);
        size--;
    }

    template <typename T, size_t N>
    void InplaceVector<T, N>::Erase(size_t inIndex)
    {
        static_assert(std::is_move_assignable_v<T> || std::is_move_assignable_v<T>);
        CheckIndexValid(inIndex);

        for (auto i = inIndex; i < size - 1; i++) {
            if constexpr (std::is_move_assignable_v<T>) {
                TypedMemory(i) = std::move(TypedMemory(i + 1));
            } else if constexpr (std::is_copy_assignable_v<T>) {
                TypedMemory(i) = TypedMemory(i + 1);
            } else {
                Assert(false);
            }
        }
        EmplaceDestruct(size - 1);
        size--;
    }

    template <typename T, size_t N>
    void InplaceVector<T, N>::Erase(const InplaceVectorIter<T>& inIter)
    {
        return EraseInternal(inIter);
    }

    template <typename T, size_t N>
    void InplaceVector<T, N>::Erase(const InplaceVectorIter<const T>& inIter)
    {
        return EraseInternal(inIter);
    }

    template <typename T, size_t N>
    void InplaceVector<T, N>::EraseSwapLast(size_t inIndex)
    {
        static_assert(std::is_move_assignable_v<T> || std::is_move_assignable_v<T>);
        CheckIndexValid(inIndex);

        if constexpr (std::is_move_assignable_v<T>) {
            TypedMemory(inIndex) = std::move(TypedMemory(size - 1));
        } else if constexpr (std::is_copy_assignable_v<T>) {
            TypedMemory(inIndex) = TypedMemory(size - 1);
        } else {
            Assert(false);
        }
        EmplaceDestruct(size - 1);
        size--;
    }

    template <typename T, size_t N>
    void InplaceVector<T, N>::EraseSwapLast(const InplaceVectorIter<T>& inIter)
    {
        EraseSwapLastInternal(inIter);
    }

    template <typename T, size_t N>
    void InplaceVector<T, N>::EraseSwapLast(const InplaceVectorIter<const T>& inIter)
    {
        EraseSwapLastInternal(inIter);
    }

    template <typename T, size_t N>
    T& InplaceVector<T, N>::At(size_t inIndex)
    {
        return TypedMemory(inIndex);
    }

    template <typename T, size_t N>
    const T& InplaceVector<T, N>::At(size_t inIndex) const
    {
        return TypedMemory(inIndex);
    }

    template <typename T, size_t N>
    T& InplaceVector<T, N>::Back()
    {
        return TypedMemory(size - 1);
    }

    template <typename T, size_t N>
    const T& InplaceVector<T, N>::Back() const
    {
        return TypedMemory(size - 1);
    }

    template <typename T, size_t N>
    bool InplaceVector<T, N>::Empty() const
    {
        return size == 0;
    }

    template <typename T, size_t N>
    void InplaceVector<T, N>::Resize(size_t inSize, T inDefault)
    {
        const auto oldSize = size;
        size = inSize;
        for (auto i = size; i < oldSize; i++) {
            EmplaceDestruct(i);
        }

        for (auto i = 0; i < size; i++) {
            if (i < oldSize) {
                TypedMemory(i) = inDefault;
            } else {
                EmplaceConstruct(i, inDefault);
            }
        }
    }

    template <typename T, size_t N>
    size_t InplaceVector<T, N>::Size() const
    {
        return size;
    }

    template <typename T, size_t N>
    size_t InplaceVector<T, N>::MemorySize() const
    {
        return elementSize * size;
    }

    template <typename T, size_t N>
    T* InplaceVector<T, N>::Data()
    {
        return memory.data();
    }

    template <typename T, size_t N>
    const T* InplaceVector<T, N>::Data() const
    {
        return memory.data();
    }

    template <typename T, size_t N>
    T& InplaceVector<T, N>::operator[](size_t inIndex)
    {
        return TypedMemory(inIndex);
    }

    template <typename T, size_t N>
    const T& InplaceVector<T, N>::operator[](size_t inIndex) const
    {
        return TypedMemory(inIndex);
    }

    template <typename T, size_t N>
    InplaceVector<T, N>::operator bool() const
    {
        return !Empty();
    }

    template <typename T, size_t N>
    typename InplaceVector<T, N>::Iter InplaceVector<T, N>::Begin()
    {
        return Iter(reinterpret_cast<T*>(memory.data()));
    }

    template <typename T, size_t N>
    typename InplaceVector<T, N>::ConstIter InplaceVector<T, N>::Begin() const
    {
        return ConstIter(reinterpret_cast<const T*>(memory.data()));
    }

    template <typename T, size_t N>
    typename InplaceVector<T, N>::Iter InplaceVector<T, N>::End()
    {
        return Iter(reinterpret_cast<T*>(memory.data()) + size);
    }

    template <typename T, size_t N>
    typename InplaceVector<T, N>::ConstIter InplaceVector<T, N>::End() const
    {
        return ConstIter(reinterpret_cast<const T*>(memory.data()) + size);
    }

    template <typename T, size_t N>
    typename InplaceVector<T, N>::Iter InplaceVector<T, N>::begin()
    {
        return Begin();
    }

    template <typename T, size_t N>
    typename InplaceVector<T, N>::ConstIter InplaceVector<T, N>::begin() const
    {
        return Begin();
    }

    template <typename T, size_t N>
    typename InplaceVector<T, N>::Iter InplaceVector<T, N>::end()
    {
        return End();
    }

    template <typename T, size_t N>
    typename InplaceVector<T, N>::ConstIter InplaceVector<T, N>::end() const
    {
        return End();
    }

    template <typename T, size_t N>
    template <ValidInplaceVectorIter<T> I>
    void InplaceVector<T, N>::CheckIterValid(const I& inIter) const
    {
        Assert(inIter >= Begin() || inIter < End());
    }

    template <typename T, size_t N>
    template <typename... Args>
    void InplaceVector<T, N>::EmplaceConstruct(size_t inIndex, Args&&... inArgs)
    {
        CheckIndexValid(inIndex);
        new(reinterpret_cast<T*>(memory.data()) + inIndex) T(std::forward<Args>(inArgs)...);
    }

    template <typename T, size_t N>
    template <ValidInplaceVectorIter<T> I, typename ... Args>
    void InplaceVector<T, N>::EmplaceConstruct(const I& inIter, Args&&... inArgs)
    {
        CheckIterValid(inIter);
        new(&*inIter) T(std::forward<Args>(inArgs)...);
    }

    template <typename T, size_t N>
    template <ValidInplaceVectorIter<T> I>
    void InplaceVector<T, N>::EmplaceDestruct(const I& inIter)
    {
        CheckIterValid(inIter);
        inIter->~T();
    }

    template <typename T, size_t N>
    template <typename T2>
    T& InplaceVector<T, N>::InsertInternal(size_t inIndex, T2&& inElement)
    {
        static_assert(std::is_move_constructible_v<T> || std::is_copy_constructible_v<T>);
        static_assert(std::is_move_assignable_v<T> || std::is_move_assignable_v<T>);

        CheckInsertible();
        Assert(inIndex <= size);
        if (inIndex == size) {
            return EmplaceBack(std::forward<T2>(inElement));
        }

        size++;
        for (auto i = size - 1; i > inIndex; i--) {
            if (i == size - 1) {
                if constexpr (std::is_move_constructible_v<T>) {
                    EmplaceConstruct(i, std::move(TypedMemory(i - 1)));
                } else if constexpr (std::is_copy_constructible_v<T>) {
                    EmplaceConstruct(i, TypedMemory(i - 1));
                } else {
                    Assert(false);
                }
            } else {
                if constexpr (std::is_move_assignable_v<T>) {
                    TypedMemory(i) = std::move(TypedMemory(i - 1));
                } else if constexpr (std::is_copy_assignable_v<T>) {
                    TypedMemory(i) = TypedMemory(i - 1);
                } else {
                    Assert(false);
                }
            }
        }

        TypedMemory(inIndex) = std::forward<T2>(inElement);
        return TypedMemory(inIndex);
    }

    template <typename T, size_t N>
    template <ValidInplaceVectorIter<T> I, typename T2>
    T& InplaceVector<T, N>::InsertInternal(const I& inIter, T2&& inElement)
    {
        static_assert(std::is_move_constructible_v<T> || std::is_copy_constructible_v<T>);
        static_assert(std::is_move_assignable_v<T> || std::is_move_assignable_v<T>);

        CheckInsertible();
        Assert(inIter >= Begin() && inIter <= End());
        if (inIter == End()) {
            return EmplaceBack(std::forward<T2>(inElement));
        }

        size++;
        for (auto iter = End() - 1; iter > inIter; --iter) {
            if (iter == End() - 1) {
                if constexpr (std::is_move_constructible_v<T>) {
                    EmplaceConstruct(iter, std::move(*(iter - 1)));
                } else if constexpr (std::is_copy_constructible_v<T>) {
                    EmplaceConstruct(iter, TypedMemory(*(iter - 1)));
                } else {
                    Assert(false);
                }
            } else {
                if constexpr (std::is_move_assignable_v<T>) {
                    *iter = std::move(*(iter - 1));
                } else if constexpr (std::is_copy_assignable_v<T>) {
                    *iter = *(iter - 1);
                } else {
                    Assert(false);
                }
            }
        }

        *inIter = std::forward<T2>(inElement);
        return *inIter;
    }

    template <typename T, size_t N>
    template <ValidInplaceVectorIter<T> I>
    void InplaceVector<T, N>::EraseInternal(const I& inIter)
    {
        static_assert(std::is_move_assignable_v<T> || std::is_move_assignable_v<T>);
        CheckIterValid(inIter);

        for (auto iter = inIter; iter < End() - 1; ++iter) {
            if constexpr (std::is_move_assignable_v<T>) {
                *iter = std::move(*(iter + 1));
            } else if constexpr (std::is_copy_assignable_v<T>) {
                *iter = *(iter + 1);
            } else {
                Assert(false);
            }
        }
        EmplaceDestruct(End() - 1);
        size--;
    }

    template <typename T, size_t N>
    template <ValidInplaceVectorIter<T> I>
    void InplaceVector<T, N>::EraseSwapLastInternal(const I& inIter)
    {
        static_assert(std::is_move_assignable_v<T> || std::is_move_assignable_v<T>);
        CheckIterValid(inIter);

        if constexpr (std::is_move_assignable_v<T>) {
            *inIter = std::move(*(End() - 1));
        } else if constexpr (std::is_copy_assignable_v<T>) {
            *inIter = *(End() - 1);
        } else {
            Assert(false);
        }
        EmplaceDestruct(End() - 1);
        size--;
    }

    template <typename T, size_t N>
    void InplaceVector<T, N>::EmplaceDestruct(size_t inIndex)
    {
        CheckIndexValid(inIndex);
        TypedMemory(inIndex).~T();
    }

    template <typename T, size_t N>
    T& InplaceVector<T, N>::TypedMemory(size_t inIndex)
    {
        CheckIndexValid(inIndex);
        return *(reinterpret_cast<T*>(memory.data()) + inIndex);
    }

    template <typename T, size_t N>
    const T& InplaceVector<T, N>::TypedMemory(size_t inIndex) const
    {
        CheckIndexValid(inIndex);
        return *(reinterpret_cast<const T*>(memory.data()) + inIndex);
    }

    template <typename T, size_t N>
    void InplaceVector<T, N>::CheckIndexValid(size_t inIndex) const
    {
        Assert(inIndex < size);
    }

    template <typename T, size_t N>
    void InplaceVector<T, N>::CheckInsertible(size_t inNum) const
    {
        Assert(size + inNum <= N);
    }
}
