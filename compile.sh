gcc -g3 -fsanitize=address -fsanitize=undefined -std=gnu89 -pedantic-errors -Wall -Wextra src/execute.c src/interfaces.c src/print.c src/read.c src/vm.c -o VM
