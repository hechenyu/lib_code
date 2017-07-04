#ifndef __any_h
#define __any_h

#include <typeinfo>

class any {
public: // structors
    any() noexcept: content(0)
    {
    }

    template <typename ValueType>
    any(const ValueType &value)
      : content(new holder<typename std::remove_cv<typename std::decay<const ValueType>::type>::type>(value))
    {
    }

    any(const any &other)
      : content(other.content ? other.content->clone() : 0)
    {
    }

    ~any() noexcept
    {
        delete content;
    }

public: // modifiers
    any &swap(any &rhs) noexcept
    {
        std::swap(content, rhs.content);
        return *this;
    }

    template <typename ValueType>
    any &operator =(const ValueType &rhs)
    {
        any(rhs).swap(*this);
        return *this;
    }

    any &operator =(any rhs)
    {
        any(rhs).swap(*this);
        return *this;
    }

public: // queries
    bool empty() const noexcept
    {
        return !content;
    }

    void clear() noexcept
    {
        any().swap(*this);
    }

    const std::type_info &type() const noexcept
    {
        return content ? content->type() : typeid(void);
    }

private: // types
    class placeholder {
    public: // structors
        virtual ~placeholder()
        {
        }

    public: // queries
        virtual const std::type_info &type() const noexcept = 0;

        virtual placeholder *clone() const = 0;
    };

    template <typename ValueType>
    class holder : public placeholder {
    public: // structors
        holder(const ValueType  &value)
          : held(value)
        {
        }

    public: // queries
        virtual const std::type_info &type() const noexcept
        {
            return typeid(ValueType);
        }

        virtual placeholder *clone() const
        {
            return new holder(held);
        }

    public: // representation
        ValueType held;

    private: // intentionally left unimplemented
        holder &operator =(const holder &) = delete;
    };

private: // representation
    template <typename ValueType>
    friend ValueType *any_cast(any *) noexcept;

    template <typename ValueType>
    friend ValueType *unsafe_any_cast(any *) noexcept;

    placeholder *content;
};

inline void swap(any &lhs, any &rhs) noexcept
{
    lhs.swap(rhs);
}

class bad_any_cast: public std::bad_cast {
public:
    virtual const char *what() const noexcept
    {
        return "bad_any_cast: failed conversion using any_cast";
    }
};

template <typename ValueType>
ValueType *any_cast(any *operand) noexcept
{
    return operand && operand->type() == typeid(ValueType)
        ? &static_cast<any::holder<typename std::remove_cv<ValueType>::type> *>(operand->content)->held
        : 0;
}

template <typename ValueType>
inline const ValueType *any_cast(const any *operand) noexcept
{
    return any_cast<ValueType>(const_cast<any *>(operand));
}

template <typename ValueType>
ValueType any_cast(any &operand)
{
    typedef typename std::remove_reference<ValueType>::type nonref;

    nonref *result = any_cast<nonref>(&operand);
    if(!result)
        throw bad_any_cast();

    // Attempt to avoid construction of a temporary object in cases when 
    // `ValueType` is not a reference. Example:
    // `static_cast<std::string>(*result);` 
    // which is equal to `std::string(*result);`
    typedef typename std::conditional<
        std::is_reference<ValueType>::value,
        ValueType,
        ValueType &
    >::type ref_type;

    return static_cast<ref_type>(*result);
}

template <typename ValueType>
inline ValueType any_cast(const any &operand)
{
    typedef typename std::remove_reference<ValueType>::type nonref;
    return any_cast<const nonref &>(const_cast<any &>(operand));
}

// Note: The "unsafe" versions of any_cast are not part of the
// public interface and may be removed at any time. They are
// required where we know what type is stored in the any and can't
// use typeid() comparison, e.g., when our types may travel across
// different shared libraries.
template <typename ValueType>
inline ValueType *unsafe_any_cast(any *operand) noexcept
{
    return &static_cast<any::holder<ValueType> *>(operand->content)->held;
}

template <typename ValueType>
inline const ValueType *unsafe_any_cast(const any *operand) noexcept
{
    return unsafe_any_cast<ValueType>(const_cast<any *>(operand));
}

#endif
