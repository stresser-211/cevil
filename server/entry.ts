import { encrypt } from "./server.js"
const main = (args: void) => {
	const x: string = "Lorem ipsum dolor sit amet.";
	console.log(x);
	const y: string = encrypt.base64.encode(x);
	console.log(y);
	const z: string = encrypt.base64.decode(y);
	console.log(z);
}
main();