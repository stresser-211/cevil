#ifndef IHADSEXWITHYOURMOTHERIMPLICITLY_H
#define IHADSEXWITHYOURMOTHERIMPLICITLY_H
#include "preprocessor.hpp"
#include "global.hpp"
extern void stacktrace(const char* component, std::string_view msg);
#define  __Uses(T) \
	using T::operator=; \
	using T::operator+; \
	using T::operator-; \
	using T::operator*; \
	using T::operator/; \
	using T::operator^; \
	using T::operator<=>; \
	using T::T;
template <typename T, typename U> concept related_to = std::is_base_of<T, U>::value or std::same_as<T, U>;
template <typename T> concept numeral_t = std::is_arithmetic<T>::value && !std::same_as<T, bool>;
template <typename T> concept integer_t = std::is_integral<T>::value && !std::same_as<T, bool>;
template <typename T> concept fraction_t = std::is_floating_point<T>::value;
template <typename T> concept signed_t = integer_t<T> && std::is_signed<T>::value;
template <typename T> concept unsigned_t = integer_t<T> && std::is_unsigned<T>::value;
template <integer_t INT_N> struct BaseInt {
	/* Constructor */
	template <typename T> BaseInt(T) = delete;
	constexpr BaseInt(void) noexcept : self(0) {};
	constexpr BaseInt(signed_t auto x) noexcept requires signed_t<INT_N> : self(x) {};
	constexpr BaseInt(unsigned_t auto x) noexcept requires unsigned_t<INT_N> : self(x) {};
	/* Assignment to */
	template <typename T> operator T(void) = delete;
	template <numeral_t T> inline constexpr operator T(void) noexcept {
		return static_cast<T>(self);
	}
	/* Assignment from */
	template <typename T> inline constexpr void operator=(T x) noexcept {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		this->self = x;
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	inline constexpr void operator=(signed_t auto x) noexcept requires signed_t<INT_N> {
		self = static_cast<INT_N>(x);
	}
	inline constexpr void operator=(unsigned_t auto x) noexcept requires unsigned_t<INT_N> {
		self = static_cast<INT_N>(x);
	}
	inline constexpr void operator=(fraction_t auto x) noexcept requires signed_t<INT_N> {
		self = std::round(static_cast<INT_N>(x));
	}
	inline constexpr void operator=(fraction_t auto x) noexcept requires unsigned_t<INT_N> {
		self = std::abs(std::round(static_cast<INT_N>(x)));
	}
	/* Unary */
	auto operator-(void) = delete;
	inline constexpr INT_N operator-(void) noexcept requires signed_t<INT_N> {
		return -self;
	}
	auto operator+(void) = delete;
	inline constexpr INT_N operator+(void) noexcept requires signed_t<INT_N> {
		return std::abs(self);
	}
	/* Binary */
	template <typename T> inline constexpr INT_N operator+(T x) {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return self + static_cast<INT_N>(x);
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	template <typename T> inline constexpr INT_N operator-(T x) {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return self - static_cast<INT_N>(x);
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	template <typename T> inline constexpr INT_N operator*(T x) {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return self * static_cast<INT_N>(x);
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	template <typename T> inline constexpr INT_N operator/(T x) {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return self / static_cast<INT_N>(x);
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	template <typename T> inline constexpr INT_N operator^(T x) {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return std::pow(self, static_cast<INT_N>(x));
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	inline constexpr INT_N operator+(integer_t auto x) {
		return self + static_cast<INT_N>(x);
	}
	inline constexpr INT_N operator-(integer_t auto x) {
		return self - static_cast<INT_N>(x);
	}
	inline constexpr INT_N operator*(integer_t auto x) {
		return self * static_cast<INT_N>(x);
	}
	inline constexpr INT_N operator/(integer_t auto x) {
		return self / static_cast<INT_N>(x);
	}
	inline constexpr INT_N operator^(integer_t auto x) {
		return std::pow(self, static_cast<INT_N>(x));
	}
	inline constexpr INT_N operator+(fraction_t auto x) {
		return self + std::round(static_cast<INT_N>(x));
	}
	inline constexpr INT_N operator-(fraction_t auto x) {
		return self - std::round(static_cast<INT_N>(x));
	}
	inline constexpr INT_N operator*(fraction_t auto x) {
		return self * std::round(static_cast<INT_N>(x));
	}
	inline constexpr INT_N operator/(fraction_t auto x) {
		return std::round(self / static_cast<INT_N>(x));
	}
	inline constexpr INT_N operator^(fraction_t auto x) {
		return std::round(std::pow(self, static_cast<INT_N>(x)));
	}
	/* Comparison */
	template <typename T> auto operator<=>(T) = delete;
	inline constexpr auto operator<=>(numeral_t auto x) noexcept {
		return self <=> static_cast<INT_N>(x);
	}
	inline constexpr INT_N operator==(numeral_t auto x) noexcept {
		return self == static_cast<INT_N>(x);
	}
	inline constexpr INT_N operator!=(numeral_t auto x) noexcept {
		return self != static_cast<INT_N>(x);
	}
	/* Internal use only */
	static INT_N typeof(void) {
		static_assert(false, "Direct call to typeof() is not allowed.");
	}
private:
	INT_N self;
};
struct Int8t final: public BaseInt<int8_t> { __Uses(BaseInt); };
struct Int16t final: public BaseInt<int16_t> { __Uses(BaseInt); };
struct Int32t final: public BaseInt<int32_t> { __Uses(BaseInt); };
struct Int64t final: public BaseInt<int64_t> { __Uses(BaseInt); };
struct Uint8t final: public BaseInt<uint8_t> { __Uses(BaseInt); };
struct Uint16t final: public BaseInt<uint16_t> { __Uses(BaseInt); };
struct Uint32t final: public BaseInt<uint32_t> { __Uses(BaseInt); };
struct Uint64t final: public BaseInt<uint64_t> { __Uses(BaseInt); };

void f(void) { /* test, please ignore */
	Uint32t u = 3u;
	Int8t q = 3;
	Uint32t p = (unsigned)((7 + u) + (7 - u) + (7 * u) + (7 / u) + (7 ^ u));
	q < 7;
	7 < q;
	q == 7;
	7 == q;
	bool xx = q < 7 ? true : false;
	bool b1 = related_to<BaseInt<decltype(Int8t::typeof())>, Int8t>;
	bool b2 = related_to<BaseInt<decltype(Uint32t::typeof())>, Uint32t>;
}
#undef __Uses
#endif /* IHADSEXWITHYOURMOTHERIMPLICITLY_H */