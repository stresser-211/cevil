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
	constexpr BaseInt(void) noexcept : self(0) {};
	constexpr BaseInt(signed_t auto x) noexcept requires signed_t<INT_N> : self(x) {};
	constexpr BaseInt(unsigned_t auto x) noexcept requires unsigned_t<INT_N> : self(x) {};
	constexpr ~BaseInt(void) noexcept = default;
	/* --- Assignment --- */
	/* to */
	template <typename T> operator T(void) = delete;
	template <numeral_t T> inline constexpr operator T(void) noexcept {
		return static_cast<T>(self);
	}
	/* from */
	template <typename T> inline constexpr void operator=(T x) noexcept {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		self = static_cast<INT_N>(x);
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
		self = static_cast<INT_N>(std::round(x));
	}
	inline constexpr void operator=(fraction_t auto x) noexcept requires unsigned_t<INT_N> {
		self = static_cast<INT_N>(std::abs(std::round(x)));
	}
	/* --- Unary --- */
	/* minus */
	auto operator-(void) = delete;
	inline constexpr INT_N operator-(void) noexcept requires signed_t<INT_N> {
		return static_cast<INT_N>(-self);
	}
	/* plus */
	auto operator+(void) = delete;
	inline constexpr INT_N operator+(void) noexcept requires signed_t<INT_N> {
		return static_cast<INT_N>(std::abs(self));
	}
	/* --- Binary --- */
	/* addition */
	template <typename T> inline constexpr friend INT_N operator+(integer_t auto i, T x) {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return static_cast<INT_N>(i + static_cast<INT_N>(x));
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	template <typename T> inline constexpr friend INT_N operator+(fraction_t auto i, T x) {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return static_cast<INT_N>(std::round(i + static_cast<INT_N>(x)));
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	template <typename T> inline constexpr INT_N operator+(T x) {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return static_cast<INT_N>(self + static_cast<INT_N>(x));
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	inline constexpr INT_N operator+(integer_t auto x) {
		return static_cast<INT_N>(self + x);
	}
	inline constexpr INT_N operator+(fraction_t auto x) {
		return static_cast<INT_N>(std::round(self + x));
	}
	/* subtraction */
	template <typename T> inline constexpr friend INT_N operator-(integer_t auto i, T x) {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return static_cast<INT_N>(i - static_cast<INT_N>(x));
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	template <typename T> inline constexpr friend INT_N operator-(fraction_t auto i, T x) {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return static_cast<INT_N>(std::round(i - static_cast<INT_N>(x)));
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	template <typename T> inline constexpr INT_N operator-(T x) {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return static_cast<INT_N>(self - static_cast<INT_N>(x));
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	inline constexpr INT_N operator-(integer_t auto x) {
		return static_cast<INT_N>(self - x);
	}
	inline constexpr INT_N operator-(fraction_t auto x) {
		return static_cast<INT_N>(std::round(self - x));
	}
	/* multiplication */
	template <typename T> inline constexpr friend INT_N operator*(integer_t auto i, T x) {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return static_cast<INT_N>(i * static_cast<INT_N>(x));
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	template <typename T> inline constexpr friend INT_N operator*(fraction_t auto i, T x) {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return static_cast<INT_N>(std::round(i * static_cast<INT_N>(x)));
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	template <typename T> inline constexpr INT_N operator*(T x) {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return static_cast<INT_N>(self * static_cast<INT_N>(x));
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	inline constexpr INT_N operator*(integer_t auto x) {
		return static_cast<INT_N>(self * x);
	}
	inline constexpr INT_N operator*(fraction_t auto x) {
		return static_cast<INT_N>(std::round(self * x));
	}
	/* division */
	template <typename T> inline constexpr friend INT_N operator/(integer_t auto i, T x) {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return static_cast<INT_N>(i / static_cast<INT_N>(x));
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	template <typename T> inline constexpr friend INT_N operator/(fraction_t auto i, T x) {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return static_cast<INT_N>(std::round(i / static_cast<INT_N>(x)));
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	template <typename T> inline constexpr INT_N operator/(T x) {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return static_cast<INT_N>(self / static_cast<INT_N>(x));
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	inline constexpr INT_N operator/(integer_t auto x) {
		return static_cast<INT_N>(self / x);
	}
	inline constexpr INT_N operator/(fraction_t auto x) {
		return static_cast<INT_N>(std::round(self / x));
	}
	/* exponentiation */
	template <typename T> inline constexpr friend INT_N operator^(integer_t auto i, T x) {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return static_cast<INT_N>(std::pow(i, static_cast<INT_N>(x)));
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	template <typename T> inline constexpr friend INT_N operator^(fraction_t auto i, T x) {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return static_cast<INT_N>(std::round(std::pow(i, static_cast<INT_N>(x))));
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	template <typename T> inline constexpr INT_N operator^(T x) {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return static_cast<INT_N>(std::pow(self, static_cast<INT_N>(x)));
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	inline constexpr INT_N operator^(integer_t auto x) {
		return static_cast<INT_N>(std::pow(self, x));
	}
	inline constexpr INT_N operator^(fraction_t auto x) {
		return static_cast<INT_N>(std::round(std::pow(self, x)));
	}
	/* --- Comparison --- */
	/* equal */
	template <typename T> inline constexpr friend INT_N operator==(integer_t auto i, T x) noexcept {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return i == static_cast<INT_N>(x);
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	template <typename T> inline constexpr friend INT_N operator==(fraction_t auto i, T x) noexcept {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return i == static_cast<double>(x);
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	template <typename T> inline constexpr INT_N operator==(T x) noexcept {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return self == static_cast<INT_N>(x);
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	inline constexpr bool operator==(numeral_t auto x) noexcept {
		return self == static_cast<INT_N>(x);
	}
	/* not equal */
	template <typename T> inline constexpr friend INT_N operator!=(integer_t auto i, T x) noexcept {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return i != static_cast<INT_N>(x);
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	template <typename T> inline constexpr friend INT_N operator!=(fraction_t auto i, T x) noexcept {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return i != static_cast<double>(x);
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	template <typename T> inline constexpr INT_N operator!=(T x) noexcept {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return self != static_cast<INT_N>(x);
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
	}
	inline constexpr bool operator!=(numeral_t auto x) noexcept {
		return self != static_cast<INT_N>(x);
	}
	/* spaceship */
	template <typename T> inline constexpr auto operator<=>(T x) noexcept {
		const bool related = related_to<BaseInt<decltype(T::typeof())>, T>;
		return self <=> static_cast<INT_N>(x);
		static_assert(std::is_class<T>::value, "Type mismatch.");
		static_assert(related, "Operands are not related.");
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