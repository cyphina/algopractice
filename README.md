# z.nam.ky.ha-algopractice

## Organization

- Problems with console IO (executable targets) in `src/problems`
- Some problem code used in the test target hanging out in `src`. Typically solving problems from the [algorithmic thinking](https://nostarch.com/algorithmic-thinking-2nd-edition) book.
- Some C++ examples in `src/examples`. Trying to utilize C++23.
- `test` is a target run to test various solutions in Catch2.
- `practice` folder just has some programming test practice code - nothing seriously engineered and limited to C++20 usage.
  - It's not actually built cause each problem is an executable target and that floods Visual Studio's solution explorer. It's more for me storing solutions in this form cause I need to remind myself how to solve some problems when I can't use the data structures I built in `src/core`.