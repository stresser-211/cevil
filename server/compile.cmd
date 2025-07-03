@echo off
call tsc --target es2022 --module es2022 --noImplicitAny --noImplicitOverride --noImplicitReturns --noUnusedLocals --strictFunctionTypes --strictNullChecks --strictPropertyInitialization entry.ts
call ./autorun