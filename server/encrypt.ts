/* Workspace: UTF-32BE */
export namespace base64 {
	const charset: string = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	export const encode = (input: string): string => {
		let buffer: string = "", pad: string = "";
		for (let char of input) {
			let charraw: string = char.codePointAt(0)!.toString(2).padStart(32, "0");
			buffer += charraw;
		}
		while (buffer.length % 6 != 0) {
			buffer += "00";
			pad += "=";
		}
		const buffer_length: number = buffer.length;
		input = "";
		for (let index: number = 0; index < buffer_length; index += 6) {
			let charcode: number = parseInt(buffer.slice(index, index + 6), 2);
			input += charset.charAt(charcode);
		}
		return input + pad;
	}
	export const decode = (input: string): string => {
		while (input.endsWith("=")) {
			input = input.slice(0, -1);
		}
		let buffer: string = "";
		for (let char of input) {
			let charraw: string = charset.indexOf(char).toString(2).padStart(6, "0");
			buffer += charraw;
		}
		const buffer_length: number = buffer.length;
		input = "";
		for (let index: number = 0; index < buffer_length; index += 32) {
			let charcode: number = parseInt(buffer.slice(index, index + 32), 2);
			input += String.fromCodePoint(charcode);
		}
		return input;
	}
}