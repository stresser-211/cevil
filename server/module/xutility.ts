export const static_assert = <T extends true>(condition: T, message?: string): never => {
	condition.valueOf();
	return <never>null;
}

let y: any = true;
y = false
let x: boolean = false;
let z = ():boolean=> {
	return true;
}

static_assert(y)
static_assert(x) //Argument of type 'false' is not assignable to parameter of type 'true'.ts(2345)
static_assert(z()) //Argument of type 'boolean' is not assignable to parameter of type 'true'.ts(2345)