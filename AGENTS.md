# AGENTS.md

C++ data-structures & algorithms practice repo following 《代码随想录》(programmercarl). Content and comments are in Chinese.

## Build system
- Built with **xmake**, not CMake/Make. Commands: `xmake` to build, `xmake run` to run, `xmake f -m release` for release mode.
- Only `src/main.cpp` is compiled (target `main`, defined in `xmake.lua`). The `test` target in `xmake.lua` is commented out.
- `src/main.cpp` is a single active scratch file that gets **replaced per-problem**. It is committed and may be mid-edit.

## Topic solution files
- The numbered dirs (`01数组`, `02链表`, ..., `dp`, `单调栈`, `图论`, `贪心`, `题目`, `05双指针`) contain **standalone, complete** `.cpp` programs (each has `main()` and uses `<bits/stdc++.h>`). They are NOT part of the xmake build.
- To test a topic file, compile it directly, e.g. `g++ "05双指针/01-移除元素.cpp" && ./a.out`.
- If you add a new topic file, either compile it standalone with `g++` or wire it into `xmake.lua` — do not assume xmake picks it up.

## Shared code
- `include/core.h` bundles common STL includes (`iostream`, `vector`, `algorithm`, etc.) — a convenience precompiled-style header.
- `libs/mystruct` (shared lib, `mytree.*`) and `libs/utils` (header-only, `myclass.h`) are linked into the `main` target via `add_deps`.

## Reference material
- Official problem explanations (PDFs/HTML) live in `题目/`, one PDF per topic. Consult these for problem intent before editing a solution.

## Comment conventions
- Comments are in **Chinese**, matching the repo's 《代码随想录》 style.
- Use a `// -- 思路:` (or `// -- 思路N:`) header block at the top of a solution function to explain the approach, then follow with plain-language reasoning. See `05双指针/05-反转链表.cpp` and `05双指针/08-环形链表.cpp` for examples.
- Prefer concrete walk-through examples over abstract description (e.g. "原来是12345，处理一次变成21345…"). When a proof is involved (e.g. Floyd 判圈), spell out the variable setup (a/b/c distances) and the derived equation.
- Keep short inline comments on non-obvious lines (e.g. why a pointer is reset, what a null check means), as in the existing topic files.
- Do NOT add code comments unless the user asks; the style above is the established convention when they do.
