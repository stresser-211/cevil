export {};
declare global {
	const is_undefined: (x: unknown) => x is undefined;
	const is_null: (x: unknown) => x is null;
	const is_void: (x: unknown) => x is void;
	const is_integral: (x: number) => x is number;
	const is_floating_point: (x: number) => x is number;
	const is_function: (x: unknown) => x is (x: unknown) => unknown;
	const is_generator: (x: unknown) => x is Function;
	const is_object: (x: unknown) => x is object;
	const is_iterable: (x: unknown) => x is object;
	const is_base_of: (x: unknown, y: unknown) => boolean;
	const is_instance_of: (x: unknown, y: unknown) => boolean;
	const is_same: (x: unknown, y: unknown) => boolean;

	const invoke_result: (x: unknown) => unknown;
}