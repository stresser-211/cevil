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

:: --- Set your own path --- ::
set path=../../server-nodejs-v20.17.0/server

call tsc %options% --outDir %path% ./encrypt.ts ./server.ts ./entry.ts