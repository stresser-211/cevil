import * as net from "node:net";
const server = net.createServer((args: void) => { console.log("placeholder"); });
const port: number = 12701;
export const listen = (args: void) => {
	server.listen(port, (args: void) => { console.log("Server started."); });
}