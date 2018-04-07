#ifndef ANY_H
#define ANY_H

#include <algorithm>
#include <typeinfo>

class Any
{
private:
    class DataBase {
    public:
        virtual ~DataBase(){ }

        virtual DataBase* clone() const = 0;
    };

    template <typename ValueType>
    class Data : public DataBase {
    public:
        Data(const ValueType& t_value) {
            value=t_value;
        }

        virtual DataBase* clone() const override {
            return new Data(value);
        }

        ValueType value;
    };

public:
    Any()
        :mData(nullptr)
    { }

    template <typename ValueType>
    Any(const ValueType& value) {
        mData=new Data<ValueType>(value);
    }

    Any(std::nullptr_t)
        :mData(nullptr)
    { }

    Any(const Any& other)
        :mData(other.mData != nullptr ? other.mData->clone() : nullptr)
    { }

    ~Any() {
        if (mData != nullptr)
            delete(mData);
    }

    Any& swap(Any& rhs) {
        std::swap(mData, rhs.mData);
        return *this;
    }

    template <typename ValueType>
    Any& operator= (const ValueType& rhs) {
        Any(rhs).swap(*this);
        return *this;
    }

    Any& operator= (const Any& rhs) {
        Any(rhs).swap(*this);
        return *this;
    }

    bool empty() const {
        return mData == nullptr;
    }

private:
    template <typename ValueType>
    friend ValueType* any_cast(Any*);

    template <typename ValueType>
    friend ValueType* any_cast_unsafe(Any*);

    DataBase* mData;
};

template <typename ValueType>
ValueType* any_cast(Any* operand) {
    if (operand != nullptr)
        return &static_cast<Any::Data<ValueType>*>(operand->mData)->value;
    else
        return nullptr;
}

template <typename ValueType>
const ValueType* any_cast(const Any* operand) {
    return any_cast<ValueType>(const_cast<Any*>(operand));
}

template <typename ValueType>
ValueType any_cast(const Any& operand) {
    return *any_cast<ValueType>(const_cast<Any*>(&operand));
}

template <typename ValueType>
ValueType any_cast(Any& operand) {
    return *any_cast<ValueType>(&operand);
}

template <typename ValueType>
const ValueType& any_cast_ref(const Any & operand) {
    return *any_cast<ValueType>(const_cast<Any*>(&operand));
}

template <typename ValueType>
ValueType& any_cast_ref(Any& operand) {
    return *any_cast<ValueType>(&operand);
}

template <typename ValueType>
ValueType* any_cast_unsafe(Any* operand) {
    return &static_cast<Any::Data<ValueType>*>(operand->mData)->value;
}

template <typename ValueType>
const ValueType* any_cast_unsafe(const Any* operand) {
    return any_cast_unsafe<ValueType>(const_cast<Any*>(operand));
}

#endif // ANY_H
