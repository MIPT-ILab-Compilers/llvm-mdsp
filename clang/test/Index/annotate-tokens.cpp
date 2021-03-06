struct bonk { };
void test(bonk X) {
    X = X;
    __is_base_of(bonk, bonk);
}

// RUN: c-index-test -test-annotate-tokens=%s:1:1:6:5 %s | FileCheck %s
// CHECK: Keyword: "struct" [1:1 - 1:7] StructDecl=bonk:1:8 (Definition)
// CHECK: Identifier: "bonk" [1:8 - 1:12] StructDecl=bonk:1:8 (Definition)
// CHECK: Punctuation: "{" [1:13 - 1:14] StructDecl=bonk:1:8 (Definition)
// CHECK: Punctuation: "}" [1:15 - 1:16] StructDecl=bonk:1:8 (Definition)
// CHECK: Punctuation: ";" [1:16 - 1:17]
// CHECK: Keyword: "void" [2:1 - 2:5] FunctionDecl=test:2:6 (Definition)
// CHECK: Identifier: "test" [2:6 - 2:10] FunctionDecl=test:2:6 (Definition)
// CHECK: Punctuation: "(" [2:10 - 2:11] FunctionDecl=test:2:6 (Definition)
// CHECK: Identifier: "bonk" [2:11 - 2:15] TypeRef=struct bonk:1:8
// CHECK: Identifier: "X" [2:16 - 2:17] ParmDecl=X:2:16 (Definition)
// CHECK: Punctuation: ")" [2:17 - 2:18] FunctionDecl=test:2:6 (Definition)
// CHECK: Punctuation: "{" [2:19 - 2:20] UnexposedStmt=
// CHECK: Identifier: "X" [3:5 - 3:6] DeclRefExpr=X:2:16
// CHECK: Punctuation: "=" [3:7 - 3:8] CallExpr=operator=:1:8
// CHECK: Identifier: "X" [3:9 - 3:10] DeclRefExpr=X:2:16
// CHECK: Punctuation: ";" [3:10 - 3:11] UnexposedStmt=
// CHECK: Keyword: "__is_base_of" [4:5 - 4:17] UnexposedExpr=
// CHECK: Punctuation: "(" [4:17 - 4:18] UnexposedExpr=
// CHECK: Identifier: "bonk" [4:18 - 4:22] TypeRef=struct bonk:1:8
// CHECK: Punctuation: "," [4:22 - 4:23] UnexposedExpr=
// CHECK: Identifier: "bonk" [4:24 - 4:28] TypeRef=struct bonk:1:8
// CHECK: Punctuation: ")" [4:28 - 4:29] UnexposedExpr=
// CHECK: Punctuation: ";" [4:29 - 4:30] UnexposedStmt=
// CHECK: Punctuation: "}" [5:1 - 5:2] UnexposedStmt=
