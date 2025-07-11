import * as typetraits from "./include/type_traits.js"
Object.assign(globalThis, typetraits);

function fv(x: void): void {
	return
}
function fu(x: void): undefined {
	return
}
function fn(x: void): null {
	return null
}
function fb(x: void): boolean {
	return true
}
function fnv(x: void): never {
	throw Error("ae")
}
function ffv(x: void): Function {
	return ():void => {return}
}
function ffb(x: void): Function {
	return ():boolean => {return false}
}
function fff(x: void): Function {
	return ():Function => {return ():void=>{return}};
}
function foe(x: void): object {
	class c {};
	return new c;
}
function fo(x: void): object {
	class c {
		self: number;
		constructor(x: number) {
			this.self = x;
		}
	};
	return new c(4);
}
function foo(x: void): object {
	return {
		self: {} as number,
		constructor(x: number) {
			this.self = x;
		}
	};
}
function fan(x: void): Array<number> {
	return [2,4,6,8,10]
}
function fau(x: void): Array<unknown> {
	return ["str", 90, null, {self:9, foo:"boo"}]
}
function fao(x: void): object {
	return [2,2,8]
}
function faau(x: void): unknown {
	return 7859n
}
function faao(x: void): any {
	return ["1e", "ij3", "vevle", "90"]
}
function counter(x: void): number {
	let y: number = 0;
	return function(x: void) {
		return ++y;
	}();
}

const main = (args: void) => {
	console.log("1 | ", invoke_result(counter));
	console.log("2 | ", invoke_result(counter));
	console.log("should be '1' | ", counter(), "\n");
	console.log("void | ", invoke_result(fv));
	console.log("undefined | ", invoke_result(fu));
	console.log("null | ", invoke_result(fn));
	console.log("bool | ", invoke_result(fb));
	console.log("never | ", invoke_result(fnv));
	console.log("function -> void | ", invoke_result(ffv));
	console.log("function -> bool | ", invoke_result(ffb));
	console.log("function -> function -> void | ", invoke_result(fff));
	console.log("object (empty) | ", invoke_result(foe));
	console.log("object | ", invoke_result(fo));
	console.log("anonymous object | ", invoke_result(foo));
	console.log("Array<Number> | ", invoke_result(fan));
	console.log("Array<unknown> | ", invoke_result(fau));
	console.log("object -> Array<Number> | ", invoke_result(fao));
	console.log("unknown -> bigint | ", invoke_result(faau));
	console.log("any -> Array<string> | ", invoke_result(faao));
}
main();