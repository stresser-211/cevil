#pragma once
#include "preprocessor.hpp"
#include "global.hpp"
#include "utility.hpp"
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
template <integer_t INT_N> struct BaseInt {
	/* --- Construction --- */
	template <typename... T> BaseInt(T...) = delete;
	template <class T> BaseInt(T x) noexcept requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> : self(static_cast<INT_N>(x)) {}
	constexpr BaseInt(void) noexcept : self(0) {};
	constexpr BaseInt(signed_t auto x) noexcept requires signed_t<INT_N> : self(static_cast<INT_N>(x)) {};
	constexpr BaseInt(unsigned_t auto x) noexcept requires unsigned_t<INT_N> : self(static_cast<INT_N>(x)) {};
	constexpr ~BaseInt(void) noexcept = default;
	/* --- Assignment --- */
	template <typename T> operator T(void) = delete;
	template <class T> inline constexpr operator T(void) noexcept requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		return self;
	}
	template <numeral_t T> inline constexpr operator T(void) noexcept {
		return static_cast<T>(self);
	}
	template <typename... T> auto operator=(T...) = delete;
	template <class T> inline constexpr void operator=(T x) requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		if (outtarange(static_cast<decltype(T::typeof())>(x))) throw ERROR::OVERFLOW;
		self = static_cast<INT_N>(x);
	}
	inline constexpr void operator=(signed_t auto x) requires signed_t<INT_N> {
		if (outtarange(x)) throw ERROR::OVERFLOW;
		self = static_cast<INT_N>(x);
	}
	inline constexpr void operator=(unsigned_t auto x) requires unsigned_t<INT_N> {
		if (outtarange(x)) throw ERROR::OVERFLOW;
		self = static_cast<INT_N>(x);
	}
	inline constexpr void operator=(fraction_t auto x) requires signed_t<INT_N> {
		if (outtarange(x)) throw ERROR::OVERFLOW;
		self = static_cast<INT_N>(std::round(x));
	}
	inline constexpr void operator=(fraction_t auto x) requires unsigned_t<INT_N> {
		if (outtarange(x)) throw ERROR::OVERFLOW;
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
	template <typename... T> auto operator+(T...) = delete;
	template <class T> inline constexpr friend INT_N operator+(integer_t auto i, T x) noexcept requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		return static_cast<INT_N>(i + static_cast<decltype(T::typeof())>(x));
	}
	template <class T> inline constexpr friend INT_N operator+(fraction_t auto i, T x) noexcept requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		return static_cast<INT_N>(std::round(i + static_cast<decltype(T::typeof())>(x)));
	}
	template <class T> inline constexpr INT_N operator+(T x) noexcept requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		return static_cast<INT_N>(self + static_cast<decltype(T::typeof())>(x));
	}
	inline constexpr INT_N operator+(integer_t auto x) noexcept {
		return static_cast<INT_N>(self + x);
	}
	inline constexpr INT_N operator+(fraction_t auto x) noexcept {
		return static_cast<INT_N>(std::round(self + x));
	}
	/* --- Subtraction --- */
	template <typename... T> auto operator-(T...) = delete;
	template <class T> inline constexpr friend INT_N operator-(integer_t auto i, T x) noexcept requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		return static_cast<INT_N>(i - static_cast<decltype(T::typeof())>(x));
	}
	template <class T> inline constexpr friend INT_N operator-(fraction_t auto i, T x) noexcept requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		return static_cast<INT_N>(std::round(i - static_cast<decltype(T::typeof())>(x)));
	}
	template <class T> inline constexpr INT_N operator-(T x) noexcept requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		return static_cast<INT_N>(self - static_cast<decltype(T::typeof())>(x));
	}
	inline constexpr INT_N operator-(integer_t auto x) noexcept {
		return static_cast<INT_N>(self - x);
	}
	inline constexpr INT_N operator-(fraction_t auto x) noexcept {
		return static_cast<INT_N>(std::round(self - x));
	}
	/* --- Multiplication --- */
	template <typename... T> auto operator*(T...) = delete;
	template <class T> inline constexpr friend INT_N operator*(integer_t auto i, T x) noexcept requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		return static_cast<INT_N>(i * static_cast<decltype(T::typeof())>(x));
	}
	template <class T> inline constexpr friend INT_N operator*(fraction_t auto i, T x) noexcept requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		return static_cast<INT_N>(std::round(i * static_cast<decltype(T::typeof())>(x)));
	}
	template <class T> inline constexpr INT_N operator*(T x) noexcept requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		return static_cast<INT_N>(self * static_cast<decltype(T::typeof())>(x));
	}
	inline constexpr INT_N operator*(integer_t auto x) noexcept {
		return static_cast<INT_N>(self * x);
	}
	inline constexpr INT_N operator*(fraction_t auto x) noexcept {
		return static_cast<INT_N>(std::round(self * x));
	}
	/* --- Division --- */
	template <typename... T> auto operator/(T...) = delete;
	template <class T> inline constexpr friend INT_N operator/(integer_t auto i, T x) requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		if (static_cast<decltype(T::typeof())>(x) == 0) throw ERROR::DIVISION_BY_ZERO;
		return static_cast<INT_N>(i / static_cast<decltype(T::typeof())>(x));
	}
	template <class T> inline constexpr friend INT_N operator/(fraction_t auto i, T x) requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		if (static_cast<decltype(T::typeof())>(x) == 0) throw ERROR::DIVISION_BY_ZERO;
		return static_cast<INT_N>(std::round(i / static_cast<decltype(T::typeof())>(x)));
	}
	template <class T> inline constexpr INT_N operator/(T x) requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		if (static_cast<decltype(T::typeof())>(x) == 0) throw ERROR::DIVISION_BY_ZERO;
		return static_cast<INT_N>(self / static_cast<decltype(T::typeof())>(x));
	}
	inline constexpr INT_N operator/(integer_t auto x) {
		if (x == 0) throw ERROR::DIVISION_BY_ZERO;
		return static_cast<INT_N>(self / x);
	}
	inline constexpr INT_N operator/(fraction_t auto x) {
		if (x == 0) throw ERROR::DIVISION_BY_ZERO;
		return static_cast<INT_N>(std::round(self / x));
	}
	/* --- Exponentiation --- */
	template <typename... T> auto operator^(T...) = delete;
	template <class T> inline constexpr friend INT_N operator^(integer_t auto i, T x) noexcept requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		return static_cast<INT_N>(std::pow(i, static_cast<decltype(T::typeof())>(x)));
	}
	template <class T> inline constexpr friend INT_N operator^(fraction_t auto i, T x) noexcept requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		return static_cast<INT_N>(std::round(std::pow(i, static_cast<decltype(T::typeof())>(x))));
	}
	template <class T> inline constexpr INT_N operator^(T x) noexcept requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		return static_cast<INT_N>(std::pow(self, static_cast<decltype(T::typeof())>(x)));
	}
	inline constexpr INT_N operator^(integer_t auto x) noexcept {
		return static_cast<INT_N>(std::pow(self, x));
	}
	inline constexpr INT_N operator^(fraction_t auto x) noexcept {
		return static_cast<INT_N>(std::round(std::pow(self, x)));
	}
	/* --- Pre-increment/decrement --- */
	inline constexpr INT_N operator++(void) {
		if (outtarange(self + 1)) throw ERROR::OVERFLOW;
		return ++self;
	}
	inline constexpr INT_N operator--(void) {
		if (outtarange(self - 1)) throw ERROR::OVERFLOW;
		return --self;
	}
	/* --- Post-increment/decrement --- */
	inline constexpr INT_N operator++(auto) {
		if (outtarange(self + 1)) throw ERROR::OVERFLOW;
		return self++;
	}
	inline constexpr INT_N operator--(auto) {
		if (outtarange(self - 1)) throw ERROR::OVERFLOW;
		return self--;
	}
	/* --- Comparison --- */
	template <typename... T> auto operator==(T...) = delete;
	template <class T> inline constexpr friend INT_N operator==(integer_t auto i, T x) noexcept requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		return i == static_cast<decltype(T::typeof())>(x);
	}
	template <class T> inline constexpr friend INT_N operator==(fraction_t auto i, T x) noexcept requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		return i == static_cast<decltype(T::typeof())>(x);
	}
	template <class T> inline constexpr INT_N operator==(T x) noexcept requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		return self == static_cast<decltype(T::typeof())>(x);
	}
	inline constexpr bool operator==(numeral_t auto x) noexcept {
		return self == static_cast<INT_N>(x);
	}
	template <typename... T> auto operator!=(T...) = delete;
	template <class T> inline constexpr friend INT_N operator!=(integer_t auto i, T x) noexcept requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		return i != static_cast<decltype(T::typeof())>(x);
	}
	template <class T> inline constexpr friend INT_N operator!=(fraction_t auto i, T x) noexcept requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		return i != static_cast<decltype(T::typeof())>(x);
	}
	template <class T> inline constexpr INT_N operator!=(T x) noexcept requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		return self != static_cast<decltype(T::typeof())>(x);
	}
	inline constexpr bool operator!=(numeral_t auto x) noexcept {
		return self != static_cast<INT_N>(x);
	}
	/* --- Spaceship --- */
	template <typename... T> auto operator<=>(T...) = delete;
	template <class T> inline constexpr auto operator<=>(T x) noexcept requires std::is_class<T>::value && related_to<BaseInt<decltype(T::typeof())>, T> {
		return self <=> static_cast<decltype(T::typeof())>(x);
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
	inline constexpr auto maxval(void) noexcept {
		auto p = std::exp2(sizeof(self) * 8);
		return (static_cast<INT_N>(-1) == p - 1) ? p - 1 : p/2 - 1;
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