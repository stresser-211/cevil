import * as __xutils from "./xutility.js"
export const is_undefined = (x: unknown): x is undefined => {
	return x === undefined;
}
export const is_null = (x: unknown): x is null => {
	return x === null;
}
export const is_void = (x: unknown): x is void => {
	return is_null(x) || is_undefined(x);
}
export const is_integral = (x: unknown): x is number => {
	return Number.isInteger(x);
}
export const is_floating_point = (x: unknown): x is number => {
	return !Number.isInteger(x);
}
export const is_function = (x: unknown): x is (x: unknown) => unknown => {
	return is_void(x) ? false : (x as any).constructor === Function;
}
export const is_generator = (x: unknown): x is Function => {
	return is_void(x) ? false : is_function((x as any).next);
}
export const is_object = (x: unknown): x is object => {
	return is_void(x) ? false : (x as any).constructor === Object;
}
export const is_iterable = (x: unknown): x is object => {
	return is_void(x) ? false : is_generator((x as any)[Symbol.iterator]());
}
export const is_base_of = (x: unknown, y: unknown): boolean => {
	return is_void(y) && !(is_object(x) || is_function(x)) ? false : y instanceof (x as any);
}
export const is_instance_of = (x: unknown, y: unknown): boolean => {
	return is_void(x) && !(is_object(y) || is_function(y)) ? false : x instanceof (y as any);
}
const __typeof = (x: unknown): unknown => {
	return is_void(x) ? x : (x as any).constructor;
}
export const is_same = (x: unknown, y: unknown): boolean => {
	return __typeof(x) === __typeof(y);
}
export const invoke_result = <T>(x: unknown): any/*x is (x: unknown ) => T*/ => {
	return __typeof(x) + "			" + x;
}