Here's the updated README.md for your pipex project based on the new file structure:

# pipex - 1337 Project  

[![1337 Badge](https://img.shields.io/badge/1337-Project-blue)](https://www.42network.org/)  

## 📜 Project Overview  

**pipex** is a Unix pipeline simulation project from **1337** (part of the **42 Network**). The project replicates shell pipe functionality (`cmd1 | cmd2`) with file redirections, implementing both mandatory and bonus features including multiple pipes and here_doc functionality.

---

## 🚀 Features  

### Mandatory Part  
- Simulates shell pipes: `< file1 cmd1 | cmd2 > file2`  
- Handles file input/output redirection  
- Robust error handling for files and commands  

### Bonus Part  
- Supports multiple pipes: `cmd1 | cmd2 | cmd3 | ... | cmdn`  
- Implements here_doc (`<< delimiter`) functionality  
- Handles file appending (`>>`)  
- Includes custom utility functions (GNL, string operations)  

---

## 📂 Repository Structure  

```plaintext
📦 pipex
├── 📂 bonus
│   ├── 📂 gnl
│   │   ├── get_next_line_bonus.c
│   │   ├── get_next_line_bonus.h
│   │   ├── get_next_line_utils_bonus.c
│   ├── 📂 utils
│   │   ├── ft_putstr_bonus.c
│   │   ├── ft_split_bonus.c
│   │   ├── ft_strcmp_bonus.c
│   │   ├── ft_strjoin_bonus.c
│   │   ├── ft_strrchr_bonus.c
│   │   ├── ft_strstr_bonus.c
│   ├── child_process_bonus.c
│   ├── error_handlers_bonus.c
│   ├── here_doc_bonus.c
│   ├── pipex_utils_bonus.c
│   ├── pipex_bonus.c
│   ├── pipex_bonus.h
│
├── 📂 mandatory
│   ├── 📂 utils
│   │   ├── ft_putstr.c
│   │   ├── ft_split.c
│   │   ├── ft_strdup.c
│   │   ├── ft_strjoin.c
│   │   ├── ft_strlen.c
│   │   ├── ft_strrchr.c
│   │   ├── ft_strstr.c
│   ├── child_process.c
│   ├── error_handlers.c
│   ├── pipex_utils.c
│   ├── pipex.c
│   ├── pipex.h
│
└── 📜 Makefile
```

---

## 🛠️ Compilation  

### Mandatory  
```bash
make
```
Produces `pipex` executable  

### Bonus  
```bash
make bonus
```
Produces `pipex_bonus` executable  

### Cleanup  
```bash
make clean      # Remove object files
make fclean     # Remove executables and objects
make re         # Full recompile
```

---

## 📖 Usage Examples  

### Basic Pipe  
```bash
./pipex infile "ls -l" "wc -l" outfile
```
Equivalent to:  
```bash
< infile ls -l | wc -l > outfile
```

### Multiple Pipes (Bonus)  
```bash
./pipex_bonus infile "grep foo" "sort" "uniq" outfile
```

### here_doc (Bonus)  
```bash
./pipex_bonus here_doc EOF "cat" "wc -w" outfile
```
Then type input ending with EOF

---

## 🛡️ Error Handling  
- Invalid file permissions  
- Non-existent commands  
- Memory leak protection  
- Argument validation  

---

## 🌟 Key Functions  
- `fork()`/`execve()` process management  
- `pipe()`/`dup2()` file descriptor handling  
- Custom string utilities (GNL, splitting, joining)  
- Comprehensive error checking  

---

## 📋 Norm Compliance  
- Follows 42 School coding standards  
- No memory leaks  
- Clean Makefile structure

For complete requirements, see ![en.subject.pdf](subject/en.subject.pdf)
For complete requirements, see [en.subject.pdf](./en.subject.pdf).
