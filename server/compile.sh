#!/bin/sh
options=(
	--target es2022
	--module es2022
	--noImplicitAny
	--noImplicitOverride
	--noImplicitReturns
	--noUnusedLocals
	--strictFunctionTypes
	--strictNullChecks
	--strictPropertyInitialization
	--removeComments
	--noEmitOnError
	--newLine crlf
	--noErrorTruncation
)
tsc "${options[@]}" --outDir ./include ./module/type_traits.ts
tsc "${options[@]}" entry.ts
./autorun