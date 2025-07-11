@echo off
set options=^
	--target es2022^
	--module es2022^
	--noImplicitAny^
	--noImplicitOverride^
	--noImplicitReturns^
	--noUnusedLocals^
	--strictFunctionTypes^
	--strictNullChecks^
	--strictPropertyInitialization^
	--removeComments^
	--noEmitOnError^
	--newLine crlf^
	--noErrorTruncation
call tsc %options% --outDir ./include ./module/type_traits.ts
call tsc %options% entry.ts
call ./autorun