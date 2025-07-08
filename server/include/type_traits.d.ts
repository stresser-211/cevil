export {};
declare global {
	const is_null: (x: null) => boolean;
	const is_void: (x: null) => boolean;
	const is_integral: (x: null) => boolean;
	const is_floating_point: (x: null) => boolean;
	const is_function: (x: null) => boolean;
	const is_generator: (x: null) => boolean;
	const is_fundamental: (x: null) => boolean;
	const is_arithmetic: (x: null) => boolean;
	const is_same: (x: null) => boolean;
	const is_union: (x: null) => boolean;
	const is_object: (x: null) => boolean;
	const is_class: (x: null) => boolean;
	const is_abstract_class: (x: null) => boolean;
	const is_interface: (x: null) => boolean;
	const is_base_of: (x: null) => boolean;
	const is_instance_of: (x: null) => boolean;
	const is_convertible: (x: null) => boolean;
	const invoke_result: (x: null) => boolean;
}