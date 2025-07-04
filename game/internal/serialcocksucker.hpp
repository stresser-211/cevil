#ifndef IHADSEXWITHYOURMOTHERIMPLICITLY_H
#define IHADSEXWITHYOURMOTHERIMPLICITLY_H
#include "preprocessor.hpp"
#include "global.hpp"
#define  __Uses(T) \
	using T::operator=; \
	using T::operator+; \
	using T::operator-; \
	using T::operator*; \
	using T::operator/; \
	using T::operator^; \
	using T::operator++; \
	using T::operator--; \
	using T::operator==; \
	using T::operator!=; \
	using T::operator<=>; \
	using T::T;
template <typename T, typename U> concept related_to = std::is_base_of<T, U>::value or std::same_as<T, U>;
template <typename T> concept numeral_t = std::is_arithmetic<T>::value && !std::same_as<T, bool>;
template <typename T> concept integer_t = std::is_integral<T>::value && !std::same_as<T, bool>;
template <typename T> concept fraction_t = std::is_floating_point<T>::value;
template <typename T> concept signed_t = integer_t<T> && std::is_signed<T>::value;
template <typename T> concept unsigned_t = integer_t<T> && std::is_unsigned<T>::value;
template <integer_t INT_N> struct BaseInt {
	/* --- Construction --- */
	template <typename... T> BaseInt(T...) = delete;
	template <class T> BaseInt(T x) noexcept requires std::is_class<T>::value : self(static_cast<INT_N>(x)) {
		static_assert(related_to<BaseInt<decltype(T::typeof())>, T>, "Operands are not related.");
	}
	constexpr BaseInt(void) noexcept : self(0) {};
	constexpr BaseInt(signed_t auto x) noexcept requires signed_t<INT_N> : self(static_cast<INT_N>(x)) {};
	constexpr BaseInt(unsigned_t auto x) noexcept requires unsigned_t<INT_N> : self(static_cast<INT_N>(x)) {};
	constexpr ~BaseInt(void) noexcept = default;
	/* --- Assignment --- */
	template <typename T> operator T(void) = delete;
	template <class T> inline constexpr operator T(void) noexcept requires std::is_class<T>::value {
		static_assert(related_to<BaseInt<decltype(T::typeof())>, T>, "Operands are not related.");
		return self;
	}
	template <numeral_t T> inline constexpr operator T(void) noexcept {
		return static_cast<T>(self);
	}
	template <typename... T> auto operator=(T...) = delete;
	template <class T> inline constexpr void operator=(T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		static_assert(!outtarange(static_cast<xtype>(x)), "Attempt to assign a value results in an overflow.");
		self = static_cast<INT_N>(x);
	}
	inline constexpr void operator=(signed_t auto x) noexcept requires signed_t<INT_N> {
		static_assert(!outtarange(x), "Attempt to assign a value results in an overflow.");
		self = static_cast<INT_N>(x);
	}
	inline constexpr void operator=(unsigned_t auto x) noexcept requires unsigned_t<INT_N> {
		static_assert(!outtarange(x), "Attempt to assign a value results in an overflow.");
		self = static_cast<INT_N>(x);
	}
	inline constexpr void operator=(fraction_t auto x) noexcept requires signed_t<INT_N> {
		static_assert(!outtarange(x), "Attempt to assign a value results in an overflow.");
		self = static_cast<INT_N>(std::round(x));
	}
	inline constexpr void operator=(fraction_t auto x) noexcept requires unsigned_t<INT_N> {
		static_assert(!outtarange(x), "Attempt to assign a value results in an overflow.");
		self = static_cast<INT_N>(std::abs(std::round(x)));
	}
	/* --- Unary --- */
	auto operator-(void) = delete;
	inline constexpr INT_N operator-(void) noexcept requires signed_t<INT_N> {
		return static_cast<INT_N>(-self);
	}
	auto operator+(void) = delete;
	inline constexpr INT_N operator+(void) noexcept requires signed_t<INT_N> {
		return static_cast<INT_N>(std::abs(self));
	}
	/* --- Addition --- */
	template <typename T> auto operator+(T) = delete;
	template <class T> inline constexpr friend INT_N operator+(integer_t auto i, T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		return static_cast<INT_N>(i + static_cast<xtype>(x));
	}
	template <class T> inline constexpr friend INT_N operator+(fraction_t auto i, T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		return static_cast<INT_N>(std::round(i + static_cast<xtype>(x)));
	}
	template <class T> inline constexpr INT_N operator+(T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		return static_cast<INT_N>(self + static_cast<xtype>(x));
	}
	inline constexpr INT_N operator+(integer_t auto x) noexcept {
		return static_cast<INT_N>(self + x);
	}
	inline constexpr INT_N operator+(fraction_t auto x) noexcept {
		return static_cast<INT_N>(std::round(self + x));
	}
	/* --- Subtraction --- */
	template <typename T> auto operator-(T) = delete;
	template <class T> inline constexpr friend INT_N operator-(integer_t auto i, T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		return static_cast<INT_N>(i - static_cast<xtype>(x));
	}
	template <class T> inline constexpr friend INT_N operator-(fraction_t auto i, T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		return static_cast<INT_N>(std::round(i - static_cast<xtype>(x)));
	}
	template <class T> inline constexpr INT_N operator-(T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		return static_cast<INT_N>(self - static_cast<xtype>(x));
	}
	inline constexpr INT_N operator-(integer_t auto x) noexcept {
		return static_cast<INT_N>(self - x);
	}
	inline constexpr INT_N operator-(fraction_t auto x) noexcept {
		return static_cast<INT_N>(std::round(self - x));
	}
	/* --- Multiplication --- */
	template <typename T> auto operator*(T) = delete;
	template <class T> inline constexpr friend INT_N operator*(integer_t auto i, T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		return static_cast<INT_N>(i * static_cast<xtype>(x));
	}
	template <class T> inline constexpr friend INT_N operator*(fraction_t auto i, T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		return static_cast<INT_N>(std::round(i * static_cast<xtype>(x)));
	}
	template <class T> inline constexpr INT_N operator*(T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		return static_cast<INT_N>(self * static_cast<xtype>(x));
	}
	inline constexpr INT_N operator*(integer_t auto x) noexcept {
		return static_cast<INT_N>(self * x);
	}
	inline constexpr INT_N operator*(fraction_t auto x) noexcept {
		return static_cast<INT_N>(std::round(self * x));
	}
	/* --- Division --- */
	template <typename T> auto operator/(T) = delete;
	template <class T> inline constexpr friend INT_N operator/(integer_t auto i, T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		static_assert(static_cast<xtype>(x) != 0, "Division by zero is undefined.");
		return static_cast<INT_N>(i / static_cast<xtype>(x));
	}
	template <class T> inline constexpr friend INT_N operator/(fraction_t auto i, T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		static_assert(static_cast<xtype>(x) != 0, "Division by zero is undefined.");
		return static_cast<INT_N>(std::round(i / static_cast<xtype>(x)));
	}
	template <class T> inline constexpr INT_N operator/(T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		static_assert(static_cast<xtype>(x) != 0, "Division by zero is undefined.");
		return static_cast<INT_N>(self / static_cast<xtype>(x));
	}
	inline constexpr INT_N operator/(integer_t auto x) noexcept {
		static_assert(x != 0, "Division by zero is undefined.");
		return static_cast<INT_N>(self / x);
	}
	inline constexpr INT_N operator/(fraction_t auto x) noexcept {
		static_assert(x != 0, "Division by zero is undefined.");
		return static_cast<INT_N>(std::round(self / x));
	}
	/* --- Exponentiation --- */
	template <typename T> auto operator^(T) = delete;
	template <class T> inline constexpr friend INT_N operator^(integer_t auto i, T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		return static_cast<INT_N>(std::pow(i, static_cast<xtype>(x)));
	}
	template <class T> inline constexpr friend INT_N operator^(fraction_t auto i, T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		return static_cast<INT_N>(std::round(std::pow(i, static_cast<xtype>(x))));
	}
	template <class T> inline constexpr INT_N operator^(T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		return static_cast<INT_N>(std::pow(self, static_cast<xtype>(x)));
	}
	inline constexpr INT_N operator^(integer_t auto x) noexcept {
		return static_cast<INT_N>(std::pow(self, x));
	}
	inline constexpr INT_N operator^(fraction_t auto x) noexcept {
		return static_cast<INT_N>(std::round(std::pow(self, x)));
	}
	/* --- Pre-increment/decrement --- */
	inline constexpr INT_N operator++(void) noexcept {
		static_assert(!outtarange(self + 1), "Attempt to assign a value results in an overflow.");
		return ++self;
	}
	inline constexpr INT_N operator--(void) noexcept {
		static_assert(!outtarange(self - 1), "Attempt to assign a value results in an overflow.");
		return --self;
	}
	/* --- Post-increment/decrement --- */
	inline constexpr INT_N operator++(auto) noexcept {
		static_assert(!outtarange(self + 1), "Attempt to assign a value results in an overflow.");
		return self++;
	}
	inline constexpr INT_N operator--(auto) noexcept {
		static_assert(!outtarange(self - 1), "Attempt to assign a value results in an overflow.");
		return self--;
	}
	/* --- Comparison --- */
	template <typename T> auto operator==(T) = delete;
	template <class T> inline constexpr friend INT_N operator==(integer_t auto i, T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		return i == static_cast<xtype>(x);
	}
	template <class T> inline constexpr friend INT_N operator==(fraction_t auto i, T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		return i == static_cast<xtype>(x);
	}
	template <class T> inline constexpr INT_N operator==(T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		return self == static_cast<xtype>(x);
	}
	inline constexpr bool operator==(numeral_t auto x) noexcept {
		return self == static_cast<INT_N>(x);
	}
	template <typename T> auto operator!=(T) = delete;
	template <class T> inline constexpr friend INT_N operator!=(integer_t auto i, T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		return i != static_cast<xtype>(x);
	}
	template <class T> inline constexpr friend INT_N operator!=(fraction_t auto i, T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		return i != static_cast<xtype>(x);
	}
	template <class T> inline constexpr INT_N operator!=(T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		return self != static_cast<xtype>(x);
	}
	inline constexpr bool operator!=(numeral_t auto x) noexcept {
		return self != static_cast<INT_N>(x);
	}
	/* --- Spaceship --- */
	template <typename T> auto operator<=>(T) = delete;
	template <class T> inline constexpr auto operator<=>(T x) noexcept requires std::is_class<T>::value {
		typedef decltype(T::typeof()) xtype;
		static_assert(related_to<BaseInt<xtype>, T>, "Operands are not related.");
		return self <=> static_cast<xtype>(x);
	}
	inline constexpr auto operator<=>(numeral_t auto x) noexcept {
		return self <=> static_cast<INT_N>(x);
	}
	/* --- Internal use only --- */
	static INT_N typeof(void) {
		static_assert(false, "Direct call to typeof() is not allowed.");
	}
private:
	INT_N self;
	forceinline constexpr auto maxval(void) noexcept {
		INT_N x = 0;
		auto p = std::exp2(sizeof(x) * 8);
		return ((decltype(x))(x - 1) == p - 1) ? p - 1 : p/2 - 1;
	}
	inline constexpr bool outtarange(unsigned_t auto x) noexcept {
		return (x > maxval()) ? true : false;
	}
	inline constexpr bool outtarange(signed_t auto x) noexcept {
		return (std::abs(x) > maxval()) ? true : false;
		/* capacity reduced by one from -x axis, i know that */
	}
};
struct Int8T final: public BaseInt<int8_t> { __Uses(BaseInt); };
struct Int16T final: public BaseInt<int16_t> { __Uses(BaseInt); };
struct Int32T final: public BaseInt<int32_t> { __Uses(BaseInt); };
struct Int64T final: public BaseInt<int64_t> { __Uses(BaseInt); };
struct Uint8T final: public BaseInt<uint8_t> { __Uses(BaseInt); };
struct Uint16T final: public BaseInt<uint16_t> { __Uses(BaseInt); };
struct Uint32T final: public BaseInt<uint32_t> { __Uses(BaseInt); };
struct Uint64T final: public BaseInt<uint64_t> { __Uses(BaseInt); };
#undef __Uses
#endif /* IHADSEXWITHYOURMOTHERIMPLICITLY_H */