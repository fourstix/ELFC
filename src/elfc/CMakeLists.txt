cmake_minimum_required(VERSION 3.10)
project(elfc C)

add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

add_executable(elfc cgelf.c
                    decl.c
                    error.c
                    expr.c
                    gen.c
                    main.c
                    misc.c
                    modpath.c
                    prep.c
                    opt.c
                    scan.c
                    stmt.c
                    sym.c
                    tree.c)
